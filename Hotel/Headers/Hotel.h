#pragma once
#ifndef __HOTEL_H__
#define __HOTEL_H__

#include "Animal.h"
#include "Food.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Hotel {
	// vector which contains animals
	vector<Animal*>* animals;

	// vector which contains all the foods inside the hotel
	vector<Food*>* foods;

	// animal capacity of this hotel
	unsigned int capacity;

	// clear all the elements
	void clear() const;

	// register food to the hotel
	void register_food(Food*) const;

	// add new animal
	void add_animal(Animal& animal) const;

	// removes an animal from the hotel
	bool remove_animal(Animal& animal) const;

	// checks if the hotel contains the animal or not
	bool contains(Animal& animal) const;

	// checks if the hotel contains the food or not
	bool contains(Food& food) const;

	// removes the food from hotel
	bool remove_food(Food& food) const;

	// transfers the animal into another room
	bool transfer_animal(Animal& animal, int) const;

	// Return pointer to the animal which has the given name
	Animal* get_animal(string& name) const;

	// Return pointer to the animal which has the given const name
	Animal* get_animal(const string& name) const;

	// Return pointer to the food which has the given name
	Food* get_food(string& name) const;

	// Return pointer to the food which has the given const name
	Food* get_food(const string& name) const;
public:
	Hotel(); // default constructor
	explicit Hotel(unsigned int); // constructor with only capacity
	explicit Hotel(vector<Animal*>&); // constructor with animals
	explicit Hotel(vector<Food*>&); // constructor with foods
	Hotel(vector<Animal*>&, vector<Food*>&); // constructor with animals and foods
	Hotel(vector<Animal*>&, uint32_t); // constructor with both properties
	Hotel(const Hotel&); // copy constructor
	~Hotel(); // destructor

	// add animal to the hotel
	void add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number) const;
	void add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number,
	                const unsigned happiness_level,
	                const bool is_ill, const bool is_tired) const;

	bool contains_animal(const string& name) const; // check if the hotel contains such an animal or not

	bool contains_food(string& name) const; // check if the hotel contains such food or not

	bool contains_food(const string& name) const; // check if the hotel contains such food or not

	uint32_t animal_count() const; // returns the count of animals in the hotel

	bool is_empty() const; // checks if the hotel is empty or not

	bool room_occupied(int room_number) const; // checks if the such room with room number is occupied or not

	void remove_animal(string name) const; // removes the given animal from hotel

	void train(string name) const; // train the given animal

	void train_all() const; // train all the animals inside the hotel

	void rest(string name) const; // rest the given animal

	void rest_all() const; // rest all the animals inside the hotel

	bool feed_all() const; // feed all the animals inside the hotel

	bool feed_animal(string name) const; // feed an animal
	
	bool feed_animal(string name, const string food_name) const; // feed an animal with the given food name

	void register_food(string name, string applicable_animals) const; // register a new food to the hotel

	void remove_food(string name) const; // removes the food from hotel

	void set_capacity(int capacity); // setter to variable capacity

	void transfer_animal(string name, int room_number) const; // transfer the animal into another room

	void modify(string name, uint8_t age) const; // change the age of the animal

	void modify(string name, bool is_ill, bool is_tired) const; // change the illness and tiredness of the animal

	void print_animal_memory_addresses() const;
	void print_food_memory_addresses() const;

	Hotel& operator=(const Hotel&); // assignment operator
	void operator--(int) const; // removes the last animal
	void operator--() const; // removes the last animal
	void operator++(int); // increments the capacity of the hotel by one
	void operator++(); // increments the capacity of the hotel by one
	void operator-=(unsigned) const; // given parameter x, removes last x animals from hotel
	bool operator==(const Hotel&) const; // equality operator
	bool operator!=(const Hotel&) const; // inequality operator
	void operator delete(void*);
	string operator[](const uint32_t i) const; // returns the index of the animal with the given name
	friend ostream& operator<<(ostream&, const Hotel&); // overloading the operator <<
};

#endif
