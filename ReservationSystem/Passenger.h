#pragma once

#include <string>

class Passenger
{
public:
	Passenger(int, int, std::string, std::string, int, int);
	~Passenger();

	std::string last_name();
	int seat_number();
	std::string first_name();
	int reservation_number();
	int phone_number();
	int menu_preference();

	Passenger *next_passanger = NULL;

private:
	int m_seat_number;
	int m_reservation_number;
	std::string m_first_name;
	std::string m_last_name;
	int m_phone_number;
	int m_menu_preference;

	
};

