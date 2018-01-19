#pragma once
#ifndef __FOOD_H__
#define __FOOD_H__

#include <iostream>
#include <vector>
#include <string>
#include "Animal.h"

using namespace std;

class Food {
	vector<string>* applicable_animals; // vector of animals which this food can be applied
	vector<Animal*>* animals; // vector of pointer to animals which this food can be applied 
	string name; // name of the food

	// clear
	void clear() const;
public:
	explicit Food(string); // constructor with the only name initializer
	Food(string, const vector<string>&); // constructor with name and vector of animals initializer
	~Food(); // destructor

	bool is_applicable_to(const string& animal_name) const; // returns true if this food is applicable to the given animal
	bool is_applicable_to(Animal* animal) const; // returns true if this food is applicable to the given animal pointer

	void add_applicable_animal(const string& animal_name) const; // add a new animal that this food can be applied

	void add_applicable_animal(Animal* animal) const; // add a new animal pointer that this food can be applied

	string get_name() const { return name; } // return the name of the food

	bool operator==(const Food& food) const; // overloading the operator ==
	friend ostream& operator<<(ostream& os, const Food& food);
};

#endif
