#pragma once

#include <string>

class Passenger
{
public:
	Passenger(int, int, std::string, std::string, int, std::string);
	~Passenger();

	std::string last_name();
	int seat_number();
	std::string first_name();
	int reservation_number();
	std::string phone_number();
	int menu_preference();
	void set_seat_number(int);
	void set_menu_preference(int);
	Passenger *next_passanger = NULL;

private:
	int m_seat_number;
	int m_reservation_number;
	std::string m_first_name;
	std::string m_last_name;
	std::string m_phone_number;
	int m_menu_preference;

	
};

