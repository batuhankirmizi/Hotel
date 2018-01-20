#include "../Headers/Room.h"

bool Room::remove_animal(Animal *animal) const {
	for(vector<Animal*>::const_iterator iter = animals->begin(); iter != animals->end(); iter++)
		if((*iter)->get_name().compare(animal->get_name()) == 0) {
			animals->erase(iter);
			return true;
		}
	return false;
}

Room::Room(const int number) : number(number) {
	animals = new vector<Animal*>;
	capacity = 1;
}

Room::Room(const int number, const int capacity) : capacity(capacity), number(number) {
	animals = new vector<Animal*>;
}

Room::Room(vector<Animal*>& animals, const int number, const int capacity) : capacity(capacity), number(number) {
	this->animals = new vector<Animal*>;
	for(vector<Animal*>::const_iterator iter = animals.begin(); iter != animals.end(); iter++)
		this->animals->push_back(*iter);
}

Room::Room(const Room &room) {
	*this = room;
}

bool Room::contains(const string animal_name) const {
	if(animal_name.compare("") == 0) return false;

	for(vector<Animal*>::const_iterator iter = animals->begin(); iter != animals->end(); iter++)
		if((*iter)->get_name().compare(animal_name) == 0)
			return true;
	return false;
}

void Room::add_animal(Animal *animal) const {
	if(animals->size() < capacity) {
		animals->push_back(animal);
		animal->set_room_number(number);
	}
}

void Room::remove_animal(const string animal_name) const {
	if(!contains(animal_name)) return;

	for(vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); iter++)
		if((*iter)->get_name().compare(animal_name) == 0) {
			animals->erase(iter);
			return;
		}
}

int Room::animal_count() const {
	return animals->size();
}

bool Room::is_empty() const {
	return animals->empty();
}

Room& Room::operator=(const Room& room) {
	if(this != &room) {
		animals = new vector<Animal*>;
		capacity = room.capacity;
		number = room.number;

		for(vector<Animal*>::iterator iter = room.animals->begin(); iter != room.animals->end(); iter++)
			animals->push_back(*iter);
	}
	return *this;
}

void Room::operator--(int) const {
	if(animal_count() > 0)
		remove_animal(animals->back());
}

void Room::operator--() const {
	if(animal_count() > 0)
		remove_animal(animals->back());
}

void Room::operator++(int) {
	capacity++;
}

void Room::operator++() {
	capacity++;
}

ostream& operator<<(ostream& os, const Room &room) {
	if (room.animals) {
		os << room.number << ": ";
		if(room.is_empty()) os << "empty";
		else {
			for(vector<Animal*>::iterator iter = room.animals->begin(); iter != room.animals->end(); iter++) {
				os << (*iter)->get_name();
				if(iter != room.animals->end() - 1)
					os << ", ";
			}
		}
		os << endl;
	}
	return os;
}
