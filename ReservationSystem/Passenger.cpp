#include "Passenger.h"


Passenger::Passenger(int new_reservation_number, 
	int new_seat_number, 
	std::string new_first_name, 
	std::string new_last_name, 
	int new_menu_preference, 
	int new_phone_number)
{
	seat_number = new_seat_number;
	first_name = new_first_name;
	last_name = new_last_name;
	menu_preference = new_menu_preference;
	phone_number = new_phone_number;
}


Passenger::~Passenger()
{
}
