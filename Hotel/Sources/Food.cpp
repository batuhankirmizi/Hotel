#include "../Headers/Food.h"

void Food::clear() const {
	applicable_animals->clear();
	for(vector<Animal*>::iterator iter = animals->begin(); iter != animals->end(); iter++)
		delete *iter;
	animals->clear();
}

Food::Food(const string name) : name(name) {
	applicable_animals = new vector<string>;
	animals = new vector<Animal*>;
}

Food::Food(const string name, const vector<string>& animals) : name(name) {
	applicable_animals = new vector<string>;
	for (unsigned i = 0; i < animals.size(); ++i)
		applicable_animals->push_back(animals.at(i));
	this->animals = new vector<Animal*>;
}

Food::~Food() {
	clear();
	animals = nullptr;
}

bool Food::is_applicable_to(const string& animal_name) const {
	for(unsigned int i = 0; i < applicable_animals->size(); ++i)
		if(applicable_animals->at(i).compare(animal_name) == 0) return true;
	return false;
}

bool Food::is_applicable_to(Animal* animal) const {
	for(vector<Animal*>::iterator it = animals->begin(); it != animals->end(); ++it)
		if(*it == animal)
			return true;
	return false;
}

void Food::add_applicable_animal(const string& animal_name) const {
	if(!is_applicable_to(animal_name))
		applicable_animals->push_back(animal_name);
}

void Food::add_applicable_animal(Animal * animal) const {
	if(!is_applicable_to(animal))
		animals->push_back(animal);
}

bool Food::operator==(const Food& food) const {
	return name.compare(food.get_name()) == 0;
}

ostream& operator<<(ostream& os, const Food& food) {
	os << food.get_name() << ": ";
	for(unsigned i = 0; i < food.applicable_animals->size(); ++i) {
		os << food.applicable_animals->at(i);
		if(i != food.applicable_animals->size() - 1)
			os << ", ";
	}
	os << endl;
	return os;
}
