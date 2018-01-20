#pragma once
#ifndef __ROOM_H__
#define __ROOM_H__

#include "Headers/Hotel.h"

class Room {
	// pointer to the animals that can live in the room
	vector<Animal*> *animals;

	// number of animals that can live in the room
	int capacity;

	// room number
	int number;
public:
	Room(int number);
	Room(int number, int capacity);
	Room(const Room&); // copy constructor

	int get_capacity() const { return capacity; }
	int get_number() const { return number; }

	bool contains(string); // checks if the given animal lives in the room

	void remove_animal(string); // remove the given animal from the room

	Room& operator=(const Room&); // assignment operator
	void operator--(int); // remove the last animal from the room (post-decrement)
	void operator--(); // remove the last animal from the room (pre-decrement)
	void operator++(int); // increase the capacity by one (post-increment)
	void operator++(); // increase the capacity by one (pre-increment)
	friend ostream operator<<(ostream&, const Room&); // overloading the operator <<
};

#endif
