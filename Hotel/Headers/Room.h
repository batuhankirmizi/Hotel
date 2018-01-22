#pragma once
#ifndef __ROOM_H__
#define __ROOM_H__

#include "Hotel.h"
#include <ostream>

class Room {
	// pointer to the animals that can live in the room
	vector<Animal*> *animals;

	// number of animals that can live in the room
	int capacity;

	// room number
	int number;

	// remove the give animal from the room
	bool remove_animal(Animal*) const;
public:
	explicit Room(int number);
	Room(int number, int capacity);
	explicit Room(vector<Animal*>&, const int number, const int capacity);
	Room(const Room&); // copy constructor

	vector<Animal*>* get_animals() const { return animals; }

	int get_capacity() const { return capacity; }

	int get_number() const { return number; }

	bool contains(string) const; // checks if the given animal lives in the room

	void add_animal(Animal*) const; // add the given animal to the room

	void remove_animal(string) const; // remove the given animal from the room

	int animal_count() const; // return the number of animals who's living in the room

	bool is_empty() const;  // checks if the room is empty or not

	Room& operator=(const Room&); // assignment operator
	void operator--(int) const; // remove the last animal from the room (post-decrement)
	void operator--() const; // remove the last animal from the room (pre-decrement)
	void operator++(int); // increase the capacity by one (post-increment)
	void operator++(); // increase the capacity by one (pre-increment)
	friend ostream& operator<<(ostream&, const Room&); // overloading the operator <<
};

#endif
