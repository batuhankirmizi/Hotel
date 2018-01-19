#include "../Headers/Hotel.h"

void Hotel::clear() const {
	foods->clear();
	animals->clear();
}

void Hotel::register_food(Food* food) const {
	if (!contains(*food))
		foods->push_back(food);
}

void Hotel::add_animal(Animal& animal) const {
	// register the given animal to the hotel
	animals->push_back(&animal);

	// if hotel contains a food which can be applied to the animal already, add animal to the foods vector
	for (vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); iter++) {
		if ((*iter)->is_applicable_to(animal.get_name()))
			(*iter)->add_applicable_animal(&animal);
	}
}


Hotel::Hotel() : capacity(10) {
	animals = new vector<Animal*>;
	foods = new vector<Food*>;
}

Hotel::Hotel(const unsigned int capacity) : capacity(capacity) {
	animals = new vector<Animal*>;
	foods = new vector<Food*>;
}

Hotel::Hotel(vector<Animal*>& anims) : capacity(10) {
	for (vector<Animal*>::iterator iter = anims.begin(); iter != anims.end(); ++iter)
		animals->push_back(*iter);
	foods = new vector<Food*>;
}

Hotel::Hotel(vector<Food*>& f) : capacity(10) {
	for (vector<Food*>::iterator iter = f.begin(); iter != f.end(); ++iter)
		foods->push_back(*iter);
	animals = new vector<Animal*>;
}

Hotel::Hotel(vector<Animal*>& anims, vector<Food*>& f) {
	for (vector<Animal*>::iterator iter = anims.begin(); iter != anims.end(); ++iter)
		animals->push_back(*iter);
	for (vector<Food*>::iterator iter = f.begin(); iter != f.end(); ++iter)
		foods->push_back(*iter);
}

Hotel::Hotel(vector<Animal*>& anims, const uint32_t capacity) : capacity(capacity) {
	for (vector<Animal*>::iterator iter = anims.begin(); iter != anims.end(); ++iter)
		animals->push_back(*iter);
	foods = new vector<Food*>;
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
	Animal* animal = new Animal(name, dates, age, room_number);
	if (name.empty()) {
		cout << "An animal has to have a name. Please enter a proper name." << endl;
		return;
	}

	if (!contains(*animal))
		if (!room_occupied(animal->get_room_number()))
			if (animal_count() < capacity)
				add_animal(*animal);
			else
				cout << "Cannot add animal " << name << " to the hotel. Capacity reached.\n";
		else
			cout << "Cannot add animal " << name << " to the hotel. Room occupied between the given.\n";
	else
		cout << "Cannot add animal " << name << " to the hotel. This hotel already contains this animal\n";
}

void Hotel::add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number,
					   const unsigned happiness_level, const bool is_ill, const bool is_tired) const {
	if (name.empty()) {
		cout << "An animal has to have a name. Please enter a proper name." << endl;
		return;
	}

	Animal* animal = new Animal(name, dates, age, room_number, happiness_level, is_ill, is_tired);
	if (!contains(*animal))
		if (!room_occupied(animal->get_room_number()))
			if (animal_count() < capacity)
				add_animal(*animal);
			else
				cout << "Cannot add animal " << name << " to the hotel. Capacity reached.\n";
		else
			cout << "Cannot add animal " << name << " to the hotel. Room occupied between the given dates.\n";
	else
		cout << "Cannot add animal " << name << " to the hotel. This hotel already contains this animal\n";
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
		if (room_occupied(room_number))
			throw - 1;
		animal.set_room_number(room_number);
		return true;
	} catch (int) {
		cout << "Cannot transfer " << animal.get_name() << ". Room " << room_number << " is occupied." << endl;
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
	if(name.compare("") == 0) return nullptr;

	for(vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if(name.compare((*iter)->get_name()) == 0)
			return *iter;
	return nullptr;
}

Food* Hotel::get_food(string& name) const {
	if(name.compare("") == 0) return nullptr;

	for(vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
		if((*iter)->get_name().compare(name) == 0)
			return *iter;
	return nullptr;
}

Food* Hotel::get_food(const string& name) const {
	if(name.compare("") == 0) return nullptr;

	for(vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
		if((*iter)->get_name().compare(name) == 0)
			return *iter;
	return nullptr;
}

uint32_t Hotel::animal_count() const {
	return animals->size();
}

bool Hotel::is_empty() const {
	return animals->empty();
}

bool Hotel::room_occupied(const int room_number) const {
	if(room_number < 0) {
		cout << "You entered negative room number." << endl;
		return false;
	}

	for (unsigned i = 0; i < animals->size(); ++i)
		if (animals->at(i)->get_room_number() == room_number)
			return true;
	return false;
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
	if(!contains_animal(animal.get_name())) return false;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (*iter == &animal) {
			delete *iter;
			animals->erase(iter);
			return true;
		}
	return false;
}

bool Hotel::contains(Animal& animal) const {
	if(animal.get_name().compare("") == 0) return false;

	for (vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); ++iter)
		if (animal.get_name().compare((*iter)->get_name()) == 0)
			return true;
	return false;
}

bool Hotel::contains(Food& food) const {
	if(food.get_name().compare("") == 0) return false;

	for(vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); ++iter)
		if(food.get_name().compare((*iter)->get_name()) == 0) return true;
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
		if(contains_animal(name))
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
		else cout << "Cannot rest " << name << ". Hotel does not contain such an aniaml." << endl;
	}
}

void Hotel::register_food(string name, string applicable_animals) const {
	Food *f = contains_food(name) ? get_food(name) : new Food(name);

	string to_add = "";
	applicable_animals += " ";
	for (unsigned i = 0; i < applicable_animals.length(); ++i) {
		if (applicable_animals.at(i) == ' ') {
			if(!f->is_applicable_to(to_add))
				f->add_applicable_animal(to_add);
			if (!contains_animal(name))
				f->add_applicable_animal(get_animal(to_add));
			to_add = "";
			continue;
		}
		to_add += applicable_animals.at(i);
	}

	register_food(f);
}

void Hotel::remove_food(const string name) const {
	if (!contains_food(name)) {
		cout << name << " could not removed. Hotel does not contain such food.";
		return;
	}

	cout << name << " has " << (remove_food(*get_food(name)) ? "" : "not") << " been removed from the hotel." << endl;
}

void Hotel::set_capacity(const int capacity) {
	this->capacity = capacity;
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
	if(!contains_animal(name)) {
		cout << "Unable to modify age of " << name << ". Hotel does not contain such an animal." << endl;
		return;
	}

	if (!contains_animal(name))
		get_animal(name)->set_age(age);
	else
		cout << "Cannot modify the age of animal " << name << ". Hotel does not contain such an animal." << endl;
}

void Hotel::modify(string name, const bool is_ill, const bool is_tired) const {
	if (contains_animal(name)) {
		get_animal(name)->set_is_ill(is_ill);
		get_animal(name)->set_is_tired(is_tired);
	} else {
		cout << "Cannot modify animal " << name << ". Hotel does not contain such an animal." << endl;
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
		if(is_empty()) {
			cout <<  "Hotel is empty. Cannot feed any animals." << endl;
			return false;
		}

		if(!contains_animal(name)) {
			cout << "Cannot feed animal " + name + ". Hotel does not contain such an animal." << endl;
			return false;
		}

	bool fed = false;
	Animal *animal = get_animal(name);
	for(vector<Food*>::iterator iter = foods->begin(); iter != foods->end(); iter++)
		if(animal->feed(**iter))
			fed = true;
	return fed;
}

bool Hotel::feed_animal(string name, string food_name) const {
	if(contains(*get_animal(name))) {
		if(contains(*get_food(food_name)))
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
	animals = new vector<Animal*>;
	foods = new vector<Food*>;

	if (this != &hotel) {
		if (!is_empty()) clear();

		for (unsigned i = 0, j = 0; i < hotel.animals->size(); ++i, j++) {
			animals->push_back(hotel.animals->at(i));
			if (j < hotel.foods->size())
				foods->push_back(hotel.foods->at(j));
		}
		capacity = hotel.capacity;
	}

	return *this;
}

void Hotel::operator--(int) const {
	if (!is_empty())
		remove_animal(*(animals->back()));
}

void Hotel::operator--() const {
	if (!is_empty())
		remove_animal(*(animals->back()));
}

void Hotel::operator++(int) {
	capacity += 1;
}

void Hotel::operator++() {
	capacity += 1;
}

void Hotel::operator-=(const unsigned x) const {
	try {
		if(x > animal_count()) {
			string s;
			switch(x) {
				case 1: s = "";
					break;
				default: s = "s";
			}
			throw "Cannot remove " + to_string(x) + " animal" + s + " from hotel. Hotel contains only " + to_string(animal_count()) +
				" animals.";
		}

		if (x == animal_count())
			throw animal_count();
	} catch (string str) {
		cout << str << endl;
		return;
	} catch (unsigned int) {
		animals->clear();
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
		for (vector<Food*>::iterator iter = hotel.foods->begin(); iter != hotel.foods->end(); ++iter) {
			os << **iter;
		}
	}

	cout << endl << "***********************************************************************************" << endl;
	cout << endl;

	return os;
}
