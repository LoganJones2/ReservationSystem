#include "Passenger.h"

Passenger::Passenger(int new_reservation_number, 
	int new_seat_number, 
	std::string new_first_name, 
	std::string new_last_name, 
	int new_menu_preference, 
	int new_phone_number)
{
	m_reservation_number = new_reservation_number;
	m_seat_number = new_seat_number;
	m_first_name = new_first_name;
	m_last_name = new_last_name;
	m_menu_preference = new_menu_preference;
	m_phone_number = new_phone_number;
}


Passenger::~Passenger()
{
}

std::string Passenger::last_name()
{
	return m_last_name;
}

int Passenger::seat_number()
{
	return m_seat_number;
}

std::string Passenger::first_name()
{
	return m_first_name;
}

int Passenger::menu_preference()
{
	return m_menu_preference;
}

int Passenger::phone_number()
{
	return m_phone_number;
}

int Passenger::reservation_number()
{
	return m_reservation_number;
}