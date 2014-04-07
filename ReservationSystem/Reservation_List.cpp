#include "Reservation_List.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

Reservation_List::Reservation_List()
{
}


Reservation_List::~Reservation_List()
{
}

void Reservation_List::insert_passenger(int reservation_number,
	int seat_number, 
	std::string first_name, 
	std::string last_name, 
	int phone_number, 
	int menu_preference)
{
	//insert first node if list is empty
	if (head == NULL)
	{
		head = new Passenger(
			reservation_number, 
			seat_number, 
			first_name, 
			last_name, 
			phone_number, 
			menu_preference);
		return;
	}

	if (head != NULL)
	{
		Passenger *current = head;
		Passenger *prev = head;
		Passenger *temp = new Passenger(
			reservation_number,
			seat_number,
			first_name,
			last_name,
			phone_number,
			menu_preference);

		if (last_name < head->last_name())
		{
			temp->next_passanger = head;
			head = temp;
			return;
		}

		while (current->next_passanger != NULL)
		{
			prev = current;
			current = current->next_passanger;

			if (last_name < current->last_name())
			{
				prev->next_passanger = temp;
				prev = prev->next_passanger;
				prev->next_passanger = current;
				return;
			}
			
		}
		current->next_passanger = temp;
	}

	
}

void Reservation_List::p_list()
{
	Passenger *temp = head;
	printElement("Name", 30);
	printElement("Phone", 15);
	printElement("Seat", 8);
	printElement("Resrv", 10);
	printElement("Meal", 10);
	std::cout << std::endl;

	while (temp != NULL)
	{
		printElement(temp->last_name() + ", " + temp->first_name(), 30);
		printElement(temp->phone_number(), 15);
		printElement(temp->seat_number(), 8);
		printElement(temp->reservation_number(), 10);
		printElement(temp->menu_preference(), 10);
		std::cout << std::endl;
		temp = temp->next_passanger;
	}
}

template<typename T>
void Reservation_List::printElement(T t, const int& width)
{
	std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

void Reservation_List::run()
{

	while (true)
	{
		const int width = 15;
		std::cout << "Blue-Sky Reservation System" << std::endl;
		std::cout << "-----------------------------------------------------------------------------" << std::endl;
		std::cout << " 1. Add a Reservation" << std::endl
			<< " 2. Cancel a Reservation" << std::endl
			<< " 3. Search" << std::endl
			<< " 4. Modify Reservation" << std::endl
			<< " 5. Print Passenger List" << std::endl
			<< " 6. Exit" << std::endl;

		int option = 0;
		bool o_valid = false;
		while (true)
		{
			std::cout << "Option: ";
			std::cin >> option;

			if (std::cin.good() && option <= 6 && option >= 1)
			{
				o_valid = true;
				int new_reservation_number;
				int new_seat_number;
				std::string new_first_name;
				std::string new_last_name;
				int new_menu_preference;
				int new_telephone_number;

				switch (option)
				{
				case 1:
					
					std::cout << "First Name: ";
					std::cin >> new_first_name;

					std::cout << "Last Name: ";
					std::cin >> new_last_name;

					while (true)
					{
						std::cout << "Phone Number: ";
						std::cin >> new_telephone_number;
						//problem with phone number range
						if (std::cin.good() && number_of_digits(new_telephone_number) == 10)
						{
							break;
						}
						else
						{
							std::cout << number_of_digits(new_telephone_number);
							std::cout << "Invalid Phone Number!" << std::endl;
							std::cin.clear();
							std::cin.ignore(INT_MAX, '\n');
						}
					}

					while (true)
					{
						std::cout << "Seat Number: ";
						std::cin >> new_seat_number;
						if (std::cin.good() && new_seat_number <= 122 && new_seat_number > 0 && !seatTaken(new_seat_number))
						{
							break;
						}
						else
						{
							if (seatTaken(new_seat_number))
							{
								std::cout << "Seat already taken";
							}
							std::cout << "Invalid Phone Number!" << std::endl;
							std::cin.clear();
							std::cin.ignore(INT_MAX, '\n');
						}
					}

					std::cout << "1. Chicken" << std::endl
						<< "2. Beef" << std::endl
						<< "3. Vegan" << std::endl;
					while (true)
					{
						std::cout << "Menu Option: ";
						std::cin >> new_menu_preference;
						if (std::cin.good() && new_menu_preference <= 3 && new_menu_preference > 0)
						{
							break;
						}
						else
						{
							std::cout << "Invalid menu option!" << std::endl;
							std::cin.clear();
							std::cin.ignore(INT_MAX, '\n');
						}
					}

					reservation_counter++;
					new_reservation_number = reservation_counter;
					insert_passenger(new_reservation_number, new_seat_number, new_first_name, new_last_name, new_menu_preference, new_telephone_number);
					clear_screen();
					break;
				case 2:
					break;
				case 3:
					while (true)
					{
						int search_reservation;
						std::cout << "Reservation Number: ";
						std::cin >> search_reservation;
						if (std::cin.good())
						{
							p_passenger(search_reservation);
							std::cout << "Press any ENTER to continue...";
							std::cin.clear();
							std::cin.ignore(INT_MAX, '\n');
							std::getchar();
							break;
						}
						else
						{
							std::cout << "Invalid reservation number!" << std::endl;
							std::cin.clear();
							std::cin.ignore(INT_MAX, '\n');
						}
					}
					break;
				case 4:
					break;
				case 5:
					p_list();
					char c;
					std::cout << "Press any ENTER to continue...";
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					std::getchar();
					break;
				case 6:
					break;
				default:
					break;
				}
			}
			else
			{
				std::cout << "Invalid option!" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			if (o_valid == true)
			{
				break;
			}
		}
	}
}

bool Reservation_List::seatTaken(int seat)
{
	Passenger *current = head;
	while (current != NULL)
	{
		if (current->seat_number() == seat)
		{
			return true;
		}
		current = current->next_passanger;
	}
	return false;
}

int Reservation_List::number_of_digits(int number)
{
	int digits = 0;
	while (number > 0)
	{
		number /= 10;
		digits++;
	}
	std::cout << digits << std::endl;
	return digits;
}

void Reservation_List::clear_screen()
{
	#ifdef WIN32
		std::system("CLS");
	#else
		std::system("CLEAR");
	#endif	

}

void Reservation_List::p_passenger(int reservation_number)
{	
	std::cout << "here";
	if (head != NULL)
	{

		std::cout << "here";
		Passenger *current = head;
		while (current->next_passanger != NULL && current->reservation_number() != reservation_number)
		{
			std::cout << "here";
			current = current->next_passanger;
		}
		
		if (current != NULL && current->reservation_number() == reservation_number)
		{
			printElement(current->last_name() + ", " + current->first_name(), 30);
			printElement(current->phone_number(), 15);
			printElement(current->seat_number(), 8);
			printElement(current->reservation_number(), 10);
			printElement(current->menu_preference(), 10);
			std::cout << std::endl;
			return;
		}
	}
	std::cout << "Reservation not found!";
}