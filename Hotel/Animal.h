#pragma once
#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include <iostream>
#include <string>
#include <ostream>

class Food;
using namespace std;

class Animal {
	string name;
	string dates;
	unsigned int age;
	unsigned int room_number;
	unsigned int happiness_level;
	bool is_ill;
	bool is_tired;

	void increase_happiness(); // increase the happiness of the animal if happiness is not more than 4

	void decrease_happiness(); // decrease the happiness of the animal if happiness is not less than 1
public:
	Animal(const string& name, const string& dates, const unsigned age, const unsigned room_number)
		: name(name),
		  dates(dates),
		  room_number(room_number) {
		this->age = age < 150 ? age : 5;
		happiness_level = 3;
		is_ill = false;
		is_tired = false;
	}

	Animal(const string& name, const string& dates, const unsigned age, const unsigned room_number,
	       const unsigned happiness_level,
	       const bool is_ill, const bool is_tired)
		: name(name),
		  dates(dates),
		  room_number(room_number),
		  is_ill(is_ill),
		  is_tired(is_tired) {
		this->age = age < 150 ? age : 5;
		this->happiness_level = happiness_level <= 5 ? happiness_level : 3;
	}

	Animal(const Animal& animal); // copy constructor

	/**** GETTERS ****/
	string get_name() const { return name; }
	string get_dates() const { return dates; }
	unsigned get_age() const { return age; }
	unsigned get_room_number() const { return room_number; }
	unsigned get_happiness_level() const { return happiness_level; }
	bool isIll() const { return is_ill; }
	bool isTired() const { return is_tired; }

	/**** SETTERS ****/
	void set_name(const string& name) { this->name = name; }
	void set_dates(const string& dates) { this->dates = dates; }

	void set_age(const unsigned age) {
		this->age = age < 150 ? age : 5;
	}

	void set_room_number(const unsigned room_number) { this->room_number = room_number; }
	void set_happiness_level(const unsigned happiness_level) { this->happiness_level = happiness_level; }
	void set_is_ill(const bool is_ill) { this->is_ill = is_ill; }
	void set_is_tired(const bool is_tired) { this->is_tired = is_tired; }

	string get_coming_date() const; // return the first day of settlement of this animal
	string get_leaving_date(); // return the last day of settlement of this animal

	bool feed(Food& food); // feed the animal by given food

	void do_exercise(); // train the animal

	void rest(); // rest the animal

	void modify(int, int, int); // change the animal's age, happiness level and room number

	bool operator==(const Animal& animal) const; // overloading the operator ==

	Animal& operator=(const Animal& animal); // assignment operator

	friend ostream& operator<<(ostream&, const Animal&); // overloading the operator <<
};

#endif
