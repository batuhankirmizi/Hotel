#pragma once
#ifndef __HOTEL_H__
#define __HOTEL_H__

#include "Animal.h"
#include "Food.h"
#include "Room.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Room;
using namespace std;

class Hotel {
	// vector which contains animals
	vector<Animal*> *animals;

	// vector which contains all the foods inside the hotel
	vector<Food*> *foods;

	// vector which contains all the rooms inside the hotel
	vector<Room*> *rooms;

	// animal capacity of this hotel
	unsigned int capacity;

	// initialize animals and foods vectors
	void init();

	// clear all the elements
	void clear() const;

	// remove all the animals from the hotel
	void remove_all_animals() const;

	// register food to the hotel
	void register_food(Food*) const;

	// register food to the hotel
	void register_room(Room*) const;

	// add new animal
	void add_animal(Animal&) const;

	// removes an animal from the hotel
	bool remove_animal(Animal&) const;

	// checks if the hotel contains the animal or not
	bool contains(Animal&) const;

	// checks if the hotel contains the food or not
	bool contains(Food&) const;

	// checks if the hotel contains the room or not
	bool contains(Room&) const;

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

	// Return pointer to the room which has the given number
	Room* get_room(int number) const;
public:
	Hotel(); // default constructor
	explicit Hotel(unsigned int); // constructor with only capacity
	Hotel(const Hotel&); // copy constructor
	~Hotel(); // destructor

	// add animal to the hotel
	void add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number) const;
	void add_animal(const string& name, const string& dates, const unsigned age, const unsigned room_number, const unsigned happiness_level,
					const bool is_ill, const bool is_tired) const;

	bool contains_animal(const string& name) const; // check if the hotel contains such an animal or not

	bool contains_food(string&) const; // checks if the hotel contains such food or not

	bool contains_food(const string&) const; // checks if the hotel contains such food or not

	bool contains_room(int) const; // checks if the hotel contains such food or not

	bool contains_food_for_animal(const string& animal_name) const; // checks if the hotel contains food for the given animal

	uint32_t animal_count() const; // returns the count of animals in the hotel

	bool is_empty() const; // checks if the hotel is empty or not

	bool room_occupied(int) const; // checks if the such room with room number is occupied or not

	void remove_animal(string) const; // removes the given animal from hotel

	void train(string) const; // train the given animal

	void train_all() const; // train all the animals inside the hotel

	void rest(string) const; // rest the given animal

	void rest_all() const; // rest all the animals inside the hotel

	bool feed_all() const; // feed all the animals inside the hotel

	bool feed_animal(string) const; // feed an animal
	
	bool feed_animal(string name, const string food_name) const; // feed an animal with the given food name

	void register_food(string name, string applicable_animals) const; // register a new food to the hotel

	void register_room(int) const; // register a new room to the hotel

	void register_room(int, int) const; // register a new room to the hotel

	void remove_food(string name) const; // removes the food from hotel

	void set_capacity(unsigned capacity); // setter to variable capacity

	void display_info(string animal_name) const; // displays the info about the given animal
	
	void display_info(int) const; // displays the info about animals(0), foods(1) or rooms(2)

	void transfer_animal(string name, int room_number) const; // transfer the animal into another room

	void modify(string name, uint8_t age) const; // change the age of the animal

	void modify(string name, bool is_ill, bool is_tired) const; // change the illness and tiredness of the animal

	void print_animal_memory_addresses() const;
	void print_food_memory_addresses() const;

		         /**** OPERATOR OVERLOADING ****/
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
