#pragma once
#ifndef __FOOD_H__
#define __FOOD_H__

#include <iostream>
#include <vector>
#include <string>
#include "Animal.h"

using namespace std;

class Food {
	// vector of animals which this food can be applied
	vector<string> *applicable_animals;

	// vector of pointer to animals which this food can be applied
	vector<Animal*> *animals;

	// name of the food
	string name;

	// clear
	void clear() const;
public:
	explicit Food(string); // constructor with the only name initializer
	Food(string, vector<Animal*>); // constructor with name and vector of animals initializer
	Food(const Food&); // copy constructor
	~Food(); // destructor

	bool is_applicable_to(const string& animal_name) const; // returns true if this food is applicable to the given animal

	bool is_applicable_to(Animal* animal) const; // returns true if this food is applicable to the given animal pointer

	void add_applicable_animal(string) const; // add a new animal pointer that this food can be applied

	void add_applicable_animal(Animal*) const; // add a new animal pointer that this food can be applied

	void remove_applicable_animal(Animal*) const; // add a new animal pointer that this food can be applied

	string get_name() const { return name; } // return the name of the food

	Food& operator=(const Food&);
	bool operator==(const Food&) const; // overloading the operator ==
	void operator delete(void*);
	friend ostream& operator<<(ostream& os, const Food& food);
};

#endif
