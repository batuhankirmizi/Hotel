#include "../Headers/Food.h"

void Food::clear() const {
	animals->clear();
}

Food::Food(const string name) : name(name) {
	animals = new vector<Animal*>;
	applicable_animals = new vector<string>;
}

Food::Food(const string name, vector<Animal*> animals) : name(name) {
	this->animals = &animals;
	applicable_animals = new vector<string>;
}

Food::Food(const Food& food) {
	*this = food;
}

Food::~Food() {
	clear();
	animals = nullptr;
}

bool Food::is_applicable_to(const string& animal_name) const {
	for(vector<string>::const_iterator iter = applicable_animals->begin(); iter != applicable_animals->end(); iter++)
		if((*iter).compare(animal_name) == 0) return true;
	return false;
}

bool Food::is_applicable_to(Animal* animal) const {
	for(vector<Animal*>::iterator it = animals->begin(); it != animals->end(); ++it)
		if(*it == animal)
			return true;
	return false;
}

void Food::add_applicable_animal(const string animal_name) const {
	applicable_animals->push_back(animal_name);
}

void Food::add_applicable_animal(Animal *animal) const {
	if(!is_applicable_to(animal))
		animals->push_back(animal);
}

void Food::remove_applicable_animal(Animal *animal) const {
	for(vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); iter++)
		if(*iter == animal) {
			animals->erase(iter);
			return;
		}
}

Food& Food::operator=(const Food& food) {
	animals = new vector<Animal*>;
	applicable_animals = new vector<string>;

	if(this != &food) {
		if(!animals->empty()) clear();

		name = food.name;
		for(vector<Animal*>::const_iterator iter = food.animals->begin(); iter != food.animals->end(); iter++)
			animals->push_back(new Animal(**iter));
		for(vector<string>::const_iterator iter = food.applicable_animals->begin(); iter != food.applicable_animals->end(); iter++)
			applicable_animals->push_back(*iter);
	}
	return *this;
}

bool Food::operator==(const Food& food) const {
	return name.compare(food.get_name()) == 0;
}

void Food::operator delete(void*) { }

ostream& operator<<(ostream& os, const Food& food) {
	os << food.get_name() << ": ";
	for(vector<Animal*>::const_iterator iter = food.animals->begin(); iter != food.animals->end(); iter++) {
		os << (*iter)->get_name();
		if(iter != food.animals->end() - 1)
			os << ", ";
	}
	os << endl;
	return os;
}
