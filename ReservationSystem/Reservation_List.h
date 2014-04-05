#pragma once

#include "Passenger.h"

class Reservation_List
{
public:
	Reservation_List();
	~Reservation_List();

	void insert_reservation(int, int, std::string, std::string, int, int);
	bool delete_reservation(int);
	void print_list();
private:
	Passenger *head;
};

