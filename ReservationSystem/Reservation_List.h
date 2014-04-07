#pragma once

#include "Passenger.h"

class Reservation_List
{
public:
	Reservation_List();
	~Reservation_List();

	void insert_passenger(int, int, std::string, std::string, int, int);
	bool delete_reservation(int);
	void p_list();
	bool seatTaken(int);
	void p_passenger(int);

	void run();
private:
	Passenger* head = NULL;
	int reservation_counter = 0;
	int number_of_digits(int);
	void clear_screen();
	template<typename T> void printElement(T, const int&);
};

