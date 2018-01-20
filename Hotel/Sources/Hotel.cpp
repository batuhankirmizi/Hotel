#include "../Headers/Hotel.h"

void Hotel::init() {
	animals = new vector<Animal*>;
	foods = new vector<Food*>;
}

void Hotel::clear() const {
	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); iter++) delete *iter;
	foods->clear();

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); iter++) delete *iter;
	animals->clear();
}

void Hotel::remove_all_animals() const {
	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); iter++) {
		for (vector<Food*>::iterator it = foods->begin(); it != foods->end(); it++)
			(*it)->remove_applicable_animal(*iter);
		for(vector<Room*>::iterator it = rooms->begin(); it != rooms->end(); it++)
			(*it)->remove_animal((*iter)->get_name());
		delete *iter;
	}
	animals->clear();
}

void Hotel::register_food(Food* food) const {
	if (!contains(*food))
		foods->push_back(food);
}

void Hotel::register_room(Room *room) const {
	if(!room) return;

	rooms->push_back(room);
}

void Hotel::add_animal(Animal& animal) const {
	// register the given animal to the hotel
	animals->push_back(&animal);

	// if hotel contains a food which can be applied to the animal already, add animal to the foods vector
	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); iter++) {
		if ((*iter)->is_applicable_to(animal.get_name()))
			(*iter)->add_applicable_animal(&animal);
	}

	// add animal to the room
	for(vector<Room*>::iterator iter = rooms->begin(); iter != rooms->end(); iter++) {
		if((*iter)->get_number() == animal.get_room_number())
			(*iter)->add_animal(&animal);
	}
}


Hotel::Hotel() : capacity(10) {
	animals = new vector<Animal*>;
	foods = new vector<Food*>;
	rooms = new vector<Room*>;
}

Hotel::Hotel(const unsigned int capacity) : capacity(capacity) {
	animals = new vector<Animal*>;
	foods = new vector<Food*>;
	rooms = new vector<Room*>;
}

Hotel::Hotel(const Hotel& hotel) {
	*this = hotel;
}

Hotel::~Hotel() {
	clear();
	animals = nullptr;
	foods = nullptr;
	capacity = 0;
}

void Hotel::add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number) const {
	if (name.empty()) {
		cout << "An animal has to have a name. Please enter a proper name." << endl;
		return;
	}

	if(!contains_animal(name))
		if(contains_room(room_number))
			if(!room_occupied(room_number))
				if(animal_count() < capacity) {
					Animal* animal = new Animal(name, dates, age, room_number);
					add_animal(*animal);
				} else
					cout << "Cannot add animal " << name << " to the hotel. Capacity reached.\n";
			else
				cout << "Cannot add animal " << name << " to the hotel. Room occupied between the given dates.\n";
		else
			cout << "Cannot add animal to the room with the number " << room_number << ". Please register the room.\n";
	else
		cout << "Cannot add animal " << name << " to the hotel. This hotel already contains this animal.\n";
}

void Hotel::add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number,
					   const unsigned happiness_level, const bool is_ill, const bool is_tired) const {
	if(name.empty()) {
		cout << "An animal has to have a name. Please enter a proper name." << endl;
		return;
	}

	if(!contains_animal(name))
		if(contains_room(room_number))
			if(!room_occupied(room_number))
				if(animal_count() < capacity) {
					Animal* animal = new Animal(name, dates, age, room_number, happiness_level, is_ill, is_tired);
					add_animal(*animal);
				} else
					cout << "Cannot add animal " << name << " to the hotel. Capacity reached.\n";
			else
				cout << "Cannot add animal " << name << " to the hotel. Room occupied between the given dates.\n";
		else
			cout << "Cannot add animal to the room with the number " << room_number << ". Please register the room.\n";
	else
		cout << "Cannot add animal " << name << " to the hotel. This hotel already contains this animal.\n";
}

bool Hotel::contains_animal(const string& name) const {
	return get_animal(name) ? contains(*get_animal(name)) : false;
}

bool Hotel::contains_food(string& name) const {
	return get_food(name) ? contains(*get_food(name)) : false;
}

bool Hotel::contains_food(const string& name) const {
	return get_food(name) ? contains(*get_food(name)) : false;

}

bool Hotel::contains_room(const int room_number) const {
	if(room_number < 0) return false;

	for(vector<Room*>::const_iterator iter = rooms->begin(); iter != rooms->end(); iter++)
		if((*iter)->get_number() == room_number) return true;
	return false;
}

bool Hotel::contains_food_for_animal(const string& animal_name) const {
	for (vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
		if ((*iter)->is_applicable_to(animal_name))
			return true;
	return false;
}

bool Hotel::remove_food(Food& food) const {
	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); ++iter)
		if (*iter == &food) {
			foods->erase(iter);
			return true;
		}
	return false;
}

bool Hotel::transfer_animal(Animal& animal, const int room_number) const {
	try {
		if(!contains_room(room_number))
			throw - 2;
		if(room_occupied(room_number))
			throw -1;

		Room *old_room = get_room(animal.get_room_number());
		Room *new_room = get_room(room_number);
		if(new_room->get_capacity() == new_room->animal_count())
			throw -3;
		new_room->add_animal(get_animal(animal.get_name()));
		old_room->remove_animal(animal.get_name());
		animal.set_room_number(room_number);

		cout << animal.get_name() << " has been successfully transferred to the room " << room_number << "." << endl;

		return true;
	} catch (int i) {
		if(i == -1)
			cout << "Cannot transfer " << animal.get_name() << ". Room " << room_number << " is occupied." << endl;
		else if(i == -2)
			cout << "Cannot transfer " << animal.get_name() << ". Room " << room_number << " does not exist in the hotel." << endl;
		else
			cout << "Cannot transfer " << animal.get_name() << ". Room " << room_number << " is full." << endl;
		return false;
	}
}

Animal* Hotel::get_animal(string& name) const {
	if (name.compare("") == 0) return nullptr;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (name.compare((*iter)->get_name()) == 0)
			return *iter;
	return nullptr;
}

Animal* Hotel::get_animal(const string& name) const {
	if (name.compare("") == 0) return nullptr;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (name.compare((*iter)->get_name()) == 0)
			return *iter;
	return nullptr;
}

Food* Hotel::get_food(string& name) const {
	if (name.compare("") == 0) return nullptr;

	for (vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
		if ((*iter)->get_name().compare(name) == 0)
			return *iter;
	return nullptr;
}

Food* Hotel::get_food(const string& name) const {
	if (name.compare("") == 0) return nullptr;

	for (vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
		if ((*iter)->get_name().compare(name) == 0)
			return *iter;
	return nullptr;
}

Room* Hotel::get_room(int number) const {
	if(!contains_room(number)) return nullptr;

	for(vector<Room*>::const_iterator iter = rooms->begin(); iter != rooms->end(); iter++)
		if((*iter)->get_number() == number)
			return *iter;
	return nullptr;
	
}

uint32_t Hotel::animal_count() const {
	return animals->size();
}

bool Hotel::is_empty() const {
	if(!animals || !foods || !rooms) return true;
	return animals->empty();
}

bool Hotel::room_occupied(const int room_number) const {
	if (room_number < 0) {
		cout << "You entered negative room number." << endl;
		return false;
	}

	return get_room(room_number)->get_capacity() == get_room(room_number)->animal_count();
}

void Hotel::remove_animal(string name) const {
	if (is_empty()) {
		cout << "Cannot remove any animals from the hotel. Hotel is empty" << endl;
		return;
	}

	if (!contains_animal(name)) {
		cout << "Cannot remove the animal " << name << ". Hotel does not contain this animal.\n";
		return;
	}

	if (remove_animal(*get_animal(name))) {
		cout << "Animal " << name << " removed successfully." << endl;
		return;
	}
	cout << "Animal " << name << " could not be removed." << endl;
}

bool Hotel::remove_animal(Animal& animal) const {
	if (!contains_animal(animal.get_name())) return false;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (*iter == &animal) {
			// remove animal from the foods vector also if foods has a food that can be applied to this animal
			if (contains_food_for_animal(animal.get_name())) {
				for (vector<Food*>::iterator it = foods->begin(); it != foods->end(); ++it)
					if ((*it)->is_applicable_to(animal.get_name()))
						(*it)->remove_applicable_animal(*iter);
			}
			// remove animal from the rooms vector as well
			for(vector<Room*>::iterator it = rooms->begin(); it != rooms->end(); ++it)
				if((*it)->get_number() == animal.get_room_number())
					(*it)->remove_animal(animal.get_name());

			delete *iter;
			animals->erase(iter);
			return true;
		}
	return false;
}

bool Hotel::contains(Animal& animal) const {
	if (animal.get_name().compare("") == 0) return false;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (animal.get_name().compare((*iter)->get_name()) == 0)
			return true;
	return false;
}

bool Hotel::contains(Food& food) const {
	if (food.get_name().compare("") == 0) return false;

	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); ++iter)
		if (food.get_name().compare((*iter)->get_name()) == 0) return true;
	return false;
}

bool Hotel::contains(Room &room) const {
	for(vector<Room*>::iterator iter = rooms->begin(); iter != rooms->end(); ++iter)
		if(*iter == &room) return true;
	return false;
}

void Hotel::train_all() const {
	if (is_empty()) {
		cout << "Hotel is empty. Cannot train any animal." << endl;
		return;
	}

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		(*iter)->do_exercise();
}

void Hotel::train(string name) const {
	if (is_empty())
		cout << "Hotel is empty. Cannot train any animal." << endl;
	else {
		if (contains_animal(name))
			get_animal(name)->do_exercise();
		else cout << "Cannot rest " << name << ". Hotel does not contain such an aniaml." << endl;
	}
}

void Hotel::rest_all() const {
	if (is_empty()) {
		cout << "Hotel is empty. Cannot rest any animal." << endl;
		return;
	}

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		(*iter)->rest();
}

void Hotel::rest(string name) const {
	if (is_empty())
		cout << "Hotel is empty. Cannot rest any animal." << endl;
	else {
		if (contains_animal(name)) get_animal(name)->rest();
		else cout << "Cannot rest " << name << ". Hotel does not contain such an animal." << endl;
	}
}

void Hotel::register_food(string name, string applicable_animals) const {
	Food* f = contains_food(name) ? get_food(name) : new Food(name);

	string to_add = "";
	applicable_animals += " ";
	for (unsigned i = 0; i < applicable_animals.length(); ++i) {
		if (applicable_animals.at(i) == ' ') {
			if (!f->is_applicable_to(to_add)) f->add_applicable_animal(to_add);
			if (contains_animal(to_add)) f->add_applicable_animal(get_animal(to_add));
			to_add = "";
			continue;
		}
		to_add += applicable_animals.at(i);
	}

	register_food(f);
}

void Hotel::register_room(const int room_number) const {
	if(!contains_room(room_number)) {
		Room *room = new Room(room_number);
		register_room(room);
	}
}
void Hotel::register_room(const int room_number, const int capacity) const {
	if(!contains_room(room_number)) {
		Room *room = new Room(room_number, capacity);
		register_room(room);
	}
}

void Hotel::remove_food(const string name) const {
	if (!contains_food(name)) {
		cout << name << " could not removed. Hotel does not contain such food.";
		return;
	}

	cout << name << " has " << (remove_food(*get_food(name)) ? "" : "not") << " been removed from the hotel." << endl;
}

void Hotel::set_capacity(const unsigned capacity) {
	if (capacity < animal_count()) {
		cout << "Cannot set capacity to " << capacity << ". Please enter a bigger value." << endl;
		return;
	}

	this->capacity = capacity;
}

void Hotel::display_info(string name) const {
	if (contains_animal(name))
		cout << *get_animal(name) << endl;
}

void Hotel::transfer_animal(string name, const int room_number) const {
	if (room_number < 0) {
		cout << "Cannot transfer animal " << name << ". Room number cannot be negative." << endl;
		return;
	}

	if (contains_animal(name))
		transfer_animal(*get_animal(name), room_number);
	else
		cout << "Cannot transfer animal " << name << ". Hotel does not contain animal." << endl;
}

void Hotel::modify(string name, const uint8_t age) const {
	if(contains_animal(name)) {
		get_animal(name)->set_age(age);
		return;
	}
	cout << "Unable to modify age of " << name << ". Hotel does not contain such an animal." << endl;
}

void Hotel::modify(string name, const bool is_ill, const bool is_tired) const {
	if (contains_animal(name)) {
		get_animal(name)->set_is_ill(is_ill);
		get_animal(name)->set_is_tired(is_tired);
	} else {
		cout << "Unable to modify animal " << name << ". Hotel does not contain such an animal." << endl;
	}
}

bool Hotel::feed_all() const {
	if (is_empty()) {
		cout << "Hotel is empty. Cannot feed any animals." << endl;
		return false;
	}

	for (auto iter = animals->begin(); iter != animals->end(); ++iter)
		feed_animal((*iter)->get_name());
	return true;
}

bool Hotel::feed_animal(string name) const {
	if (is_empty()) {
		cout << "Hotel is empty. Cannot feed any animals." << endl;
		return false;
	}

	if (!contains_animal(name)) {
		cout << "Cannot feed animal " + name + ". Hotel does not contain such an animal." << endl;
		return false;
	}

	if(!contains_food_for_animal(name)) {
		cout << "Unable to feed " << name << ". Hotel does not contain such food." << endl;
	}

	bool fed = false;
	Animal* animal = get_animal(name);
	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); iter++)
		if (animal->feed(**iter))
			fed = true;
	return fed;
}

bool Hotel::feed_animal(string name, string food_name) const {
	if (contains(*get_animal(name))) {
		if (contains(*get_food(food_name)))
			get_animal(name)->feed(*get_food(food_name));
		cout << "Unable to feed animal " << name << ". Hotel does not contain such food." << endl;
		return false;
	}
	cout << "Unable to feed animal " << name << ". Hotel does not contain such an animal." << endl;
	return false;
}

void Hotel::print_animal_memory_addresses() const {
	if (is_empty()) return;

	cout << "Memory addresses of the animals in the hotel:\n";

	int i = 0;
	for (vector<Animal*>::const_iterator it = animals->begin(); it != animals->end(); ++it) {
		cout << i << " -> " << *it << endl;
		i++;
	}
}

void Hotel::print_food_memory_addresses() const {
	if (is_empty()) return;

	cout << "Memory addresses of the foods in the hotel:\n";

	int i = 0;
	for (vector<Food*>::const_iterator it = foods->begin(); it != foods->end(); ++it) {
		cout << i << " -> " << *it << endl;
		i++;
	}
}

Hotel& Hotel::operator=(const Hotel& hotel) {
	if (this != &hotel && hotel.animals && hotel.foods && hotel.rooms) {
		if (!is_empty()) clear();

		capacity = hotel.capacity;
		animals = new vector<Animal*>;
		foods = new vector<Food*>;
		rooms = new vector<Room*>;
		
		for(vector<Animal*>::const_iterator iter = hotel.animals->begin(); iter != hotel.animals->end(); iter++)
			animals->push_back(new Animal(**iter));
		for(vector<Food*>::const_iterator iter = hotel.foods->begin(); iter != hotel.foods->end(); iter++)
			foods->push_back(new Food(**iter));
		for(vector<Room*>::const_iterator iter = hotel.rooms->begin(); iter != hotel.rooms->end(); iter++) {
			vector<Animal*> *a = new vector<Animal*>;
			for(vector<Animal*>::iterator it = (*iter)->get_animals()->begin(); it != (*iter)->get_animals()->end(); ++it)
				a->push_back(get_animal((*it)->get_name()));

			rooms->push_back(new Room(*a, (*iter)->get_number(), (*iter)->get_capacity()));
		}

	}

	return *this;
}

void Hotel::operator--(int) const {
	if (!is_empty())
		remove_animal(*animals->back());
}

void Hotel::operator--() const {
	if (!is_empty())
		remove_animal(*animals->back());
}

void Hotel::operator++(int) {
	capacity += 1;
}

void Hotel::operator++() {
	capacity += 1;
}

void Hotel::operator-=(const unsigned x) const {
	try {
		if (x > animal_count()) {
			string s;
			switch (x) {
			case 1: s = "";
				break;
			default: s = "s";
			}
			throw "Cannot remove " + to_string(x) + " animal" + s + " from hotel. Hotel contains only " +
				to_string(animal_count()) +
				" animals.";
		}

		if (x == animal_count())
			throw animal_count();
	} catch (string str) {
		cout << str << endl;
		return;
	} catch (unsigned int) {
		remove_all_animals();
		cout << "Removed all the animals from hotel." << endl;
		return;
	}

	for (uint_fast16_t i = 0; i < x; ++i)
		operator--();
	cout << "Removed " << x << " animal" << (x == 1 ? "" : "s") << " from hotel." << endl;
}

bool Hotel::operator==(const Hotel& hotel) const {
	return animals == hotel.animals;
}

bool Hotel::operator!=(const Hotel& hotel) const {
	return !(*this == hotel);
}

void Hotel::operator delete(void*) { }

string Hotel::operator[](const uint32_t i) const {
	try {
		if (i + 1 > animal_count()) {
			string s;
			switch (i) {
			case 1: s = "st";
				break;
			case 2: s = "nd";
				break;
			case 3: s = "rd";
				break;
			default:
				s = "th";
			}
			throw "Cannot access to " + to_string(i) + s + " animal in the hotel. Hotel contains only " +
				to_string(animal_count()) + " animals.";
		}
	} catch (string e) {
		cout << e << endl;
		return "";
	}

	vector<Animal*>::const_iterator it = animals->begin();
	for (unsigned j = 0; j < i; ++j) {
		it++;
	}
	return (*it)->get_name();
}

ostream& operator<<(ostream& os, const Hotel& hotel) {
	if (!hotel.animals || !hotel.foods) {
		os << "Unable to find such an hotel to print info about." << endl;
		return os;
	}

	cout << "***********************************************************************************" << endl;
	cout << "\t*********Animals in the hotel*********" << endl;
	if (hotel.is_empty()) {
		cout << "Hotel does not contain any animals." << endl;
	} else {
		for (vector<Animal*>::iterator iter = hotel.animals->begin(); iter != hotel.animals->end(); ++iter)
			os << **iter << endl;
	}
	cout << endl << "\t*********Foods in the hotel*********" << endl;
	if (hotel.foods->empty()) {
		cout << "Hotel does not contain any food." << endl;
	} else {
		for (vector<Food*>::iterator iter = hotel.foods->begin(); iter != hotel.foods->end(); ++iter)
			os << **iter;
	}
	cout << endl << "\t*********Rooms in the hotel*********" << endl;
	if (hotel.rooms->empty()) {
		cout << "Hotel does not have any rooms." << endl;
	} else {
		for (vector<Room*>::iterator iter = hotel.rooms->begin(); iter != hotel.rooms->end(); ++iter)
			os << **iter;
	}

	cout << endl << "***********************************************************************************" << endl;

	return os;
}
