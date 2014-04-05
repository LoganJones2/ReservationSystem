#pragma once

#include <string>

class Passenger
{
public:
	Passenger(int, int, std::string, std::string, int, int);
	~Passenger();
private:
	int seat_number;
	int reservation_number;
	std::string first_name;
	std::string last_name;
	int phone_number;
	int menu_preference;

	Passenger *next_passanger;
};

