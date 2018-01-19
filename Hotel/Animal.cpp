#include "Animal.h"
#include "Food.h"
#include <vector>
#include <algorithm>

ostream& operator<<(ostream& os, const Animal& animal) {
	os << "name: " << animal.name << "\nage: " << animal.age << "\nwill be staying between: " << animal.dates <<
		  "\nroom number: " << animal.room_number << "\nhappiness: " << animal.happiness_level <<
		  "\nill: " << (animal.is_ill ? "yes" : "no") << "\nis_tired: " << (animal.is_tired ? "yes" : "no") << "\n";
	return os;
}

void Animal::increase_happiness() {
	happiness_level += happiness_level < 5 ? 1 : 0;
}

void Animal::decrease_happiness() {
	happiness_level -= happiness_level > 0 ? 1 : 0;
}

Animal::Animal(const Animal& animal) {
	*this = animal;
}

string Animal::get_coming_date() const {
	if(dates.compare("") == 0)
		return "Coming date cannot be found.";

	string to_return;
	for (int i = 0; i < 10; ++i) {
		to_return += dates[i];
	}

	return to_return;
}

string Animal::get_leaving_date() {
	if(dates.compare("") == 0)
		return "Leaving date cannot be found.";

	bool append = false;
	string to_return;
	for(unsigned i = 0; i < dates.size(); ++i) {
		if(dates[i] == '-') append = true;
		if(append) to_return += dates[i];
	}

	return to_return;
}

bool Animal::feed(Food& food) {
	if(food.is_applicable_to(name)) {
		increase_happiness();
		cout << "Animal " << name << " has been fed by food " << food.get_name() << "." << endl;
		return true;
	}
	return false;
}

void Animal::do_exercise() {
	if(happiness_level <= 2) {
		cout << "Cannot make exercise. Animal " << name << " is unhappy." << endl;
		return;
	}

	if(is_tired) {
		cout << "Animal " << name << " cannot make exercise. Animal is tired." << endl;
		return;
	}
	cout << "Animal " << name << " has been exercising." << endl;
	is_tired = true;
	decrease_happiness();
}

void Animal::rest() {
	if(is_tired) {
		cout << "Animal " << name << " has been rested." << endl;
		is_tired = false;
		increase_happiness();
		return;
	}
	cout << "Animal " << name << " cannot be rested. Animal is not tired." << endl;
}

void Animal::modify(const int age, const int h_level, const int r_number) {
	this->age = age;
	this->happiness_level = h_level;
	this->room_number = r_number;
}

bool Animal::operator==(const Animal& animal) const {
	return animal.get_name().compare(animal.get_name()) == 0 && age == animal.get_age();
}

Animal& Animal::operator=(const Animal& animal) {
	if(this != &animal) {
		name = animal.get_name();
		dates = animal.get_dates();
		age = animal.get_age();
		room_number = animal.get_room_number();
		happiness_level = animal.get_happiness_level();
		is_ill = animal.isIll();
		is_tired = animal.isTired();
	}

	return *this;
}
