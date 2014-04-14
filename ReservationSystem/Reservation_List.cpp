/*!
The Reservation List class handles all the searching, sorting, deletion,
modification, and presentation of Passenger reservation data.
*/

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
	std::string phone_number,
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
			menu_preference,
			phone_number);
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
			menu_preference,
			phone_number);

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

bool Reservation_List::is_telephone_valid(std::string telephone)
{
	for (size_t i = 0; i < telephone.length(); i++)
	{
		if (!isdigit(telephone[i]) || telephone.length() != 10)
		{
			return false;
		}
	}

	return true;
}

bool Reservation_List::delete_reservation(int reservation)
{
	std::pair<Passenger*, Passenger*> pointers = p_search(reservation);
	Passenger *current = pointers.second;
	Passenger *previous = pointers.first;

	if (current == NULL)
	{
		return false;
	}

    //cancellation is first passenger in list
	if (current == head)
	{
		//Move head.  Then delete passenger node
        head = head->next_passanger;
		delete current;
        return true;
	}

	//Connect previous passenger node to next.  Then delete.
    previous->next_passanger = current->next_passanger;
	delete current;
	return true;
}

void Reservation_List::empty_buffer()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}

void Reservation_List::wait_for_enter()
{
	std::cout << "Press ENTER to continue...";
	empty_buffer();
	std::getchar();
}

std::pair<Passenger*, Passenger*> Reservation_List::p_search(int reservation)
{
	Passenger *current = head;
	Passenger *prev = head;

	// Check list is not empty.
	if (current == NULL)
	{
		return std::make_pair<Passenger*, Passenger*>(NULL, NULL);
	}

	// Find the passenger in the list.
	while (current != NULL && current->reservation_number() != reservation)
	{
		prev = current;
		current = current->next_passanger;
	}

	// If passenger exists return current and previous pointers.
	if (current != NULL && current->reservation_number() == reservation)
	{
		return std::make_pair<Passenger*, Passenger*>(&(*prev), &(*current));
	}

	// If passenger not found in list, return nulls.
	return std::make_pair<Passenger*, Passenger*>(NULL, NULL);
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
			<< " 6. Print Report" << std::endl
            << " 7. Exit" << std::endl;

		int option = 0;
		bool o_valid = false;
		while (true)
		{
			// Option prompt
			std::cout << "Option: ";
			std::cin >> option;
			std::cout << std::endl;

			if (std::cin.good() && option <= 7 && option >= 1)
			{
				o_valid = true;
				int new_reservation_number;
				int new_seat_number;
				std::string new_first_name;
				std::string new_last_name;
				int new_menu_preference;
				std::string new_telephone_number;

				switch (option)
				{
				case 1:

					std::cout << "First Name: ";
					std::cin >> new_first_name;

					std::cout << "Last Name: ";
					std::cin >> new_last_name;

					// Prompt for phone number
					while (true)
					{
						std::cout << "Phone Number: ";
						std::cin >> new_telephone_number;

						// Check phone number for errors.
						if (is_telephone_valid(new_telephone_number))
						{
							break;
						}
						else
						{
							std::cout << "Invalid Phone Number!" << std::endl;
							empty_buffer();
						}
					}

					// Prompt for seat number.
					while (true)
					{
						std::cout << "Seat Number: ";
						std::cin >> new_seat_number;

						if (std::cin.good() &&
							new_seat_number <= 122 &&
							new_seat_number > 0 &&
							!seatTaken(new_seat_number))
						{
							break;
						}

						// Throw seat errors.
						if (seatTaken(new_seat_number))
						{
							std::cout << "Seat already taken"
								<< std::endl;
							empty_buffer();
						}
						else
						{
							std::cout << "Seat number does not exist for this flight!"
								<< std::endl;
							empty_buffer();
						}
					}

					std::cout << std::endl
						<< " 1. Turkey Sandwich" << std::endl
						<< " 2. Shrimp Pasta" << std::endl
						<< " 3. Steak and Potatoes" << std::endl;
					while (true)
					{
						std::cout << "Menu Option: ";
						std::cin >> new_menu_preference;
						if (std::cin.good() &&
							new_menu_preference <= 3 &&
							new_menu_preference > 0)
						{
							break;
						}
						else
						{
							std::cout << "Invalid menu option!" << std::endl;
							empty_buffer();
						}
					}

					reservation_counter++;
					new_reservation_number = reservation_counter;
					insert_passenger(new_reservation_number,
						new_seat_number,
						new_first_name,
						new_last_name,
						new_telephone_number,
						new_menu_preference);
					std::cout << std::endl << "Passanger added!" << std::endl << std::endl;
					wait_for_enter();
					clear_screen();
					break;
				case 2:
					int delete_reseveration_number;
					std::cout << "Reservation Number: ";
					std::cin >> delete_reseveration_number;

					if (delete_reservation(delete_reseveration_number))
					{
						std::cout << "Delete successful!" << std::endl << std::endl;
					}
					else
					{
						std::cout << "Delete NOT successful!" << std::endl << std::endl;
					}

					wait_for_enter();
					clear_screen();
					break;
				case 3:
					while (true)
					{
						int search_reservation;
						std::cout << "Reservation Number: ";
						std::cin >> search_reservation;
						std::cout << std::endl;
						if (std::cin.good())
						{
							p_passenger(search_reservation);
							wait_for_enter();
							clear_screen();
							break;
						}
						else
						{
							std::cout << "Invalid reservation number!" << std::endl;
							empty_buffer();
						}
					}
					break;
				case 4:
					int modify_reservation_number;
					while (true)
					{
						int modify_reservation_number;
						std::cout << "Reservation Number: ";
						std::cin >> modify_reservation_number;
						std::cout << std::endl;
						if (std::cin.good())
						{
							modify_passenger(modify_reservation_number);
							wait_for_enter();
							clear_screen();
							break;
						}
						else
						{
							std::cout << "Invalid reservation number!" << std::endl;
							empty_buffer();
						}
					}



					break;
				case 5:
					p_list();
					std::cout << std::endl;
					wait_for_enter();
					clear_screen();
					break;
				case 6:
					print_report();
					wait_for_enter();
					clear_screen();
                    break;
                case 7:
					break;
				default:
					break;
				}
			}
			else
			{
				std::cout << "Invalid option!" << std::endl;
				empty_buffer();
			}
			if (o_valid == true)
			{
				break;
			}
		}
        if (option == 7){
		    break;
	    }
	}

	std::cout << "Thank you for using our reservation system." << std::endl;
	wait_for_enter(); 

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
	std::pair<Passenger*, Passenger*> pointers = p_search(reservation_number);
	Passenger *current = pointers.second;
	Passenger *previous = pointers.first;

	if (current == NULL)
	{
		std::cout << "Reservation not found!" << std::endl << std::endl;
		return;
	}

	if (current != NULL && current->reservation_number() == reservation_number)
	{
		printElement("Name", 30);
		printElement("Phone", 15);
		printElement("Seat", 8);
		printElement("Resrv", 10);
		printElement("Meal", 10);
		std::cout << std::endl;

		printElement(current->last_name() + ", " + current->first_name(), 30);
		printElement(current->phone_number(), 15);
		printElement(current->seat_number(), 8);
		printElement(current->reservation_number(), 10);
		printElement(current->menu_preference(), 10);
		std::cout << std::endl << std::endl;
		return;
	}
}

bool Reservation_List::modify_passenger(int reservation)
{
	std::pair<Passenger*, Passenger*> pointers = p_search(reservation);
	Passenger *current = pointers.second;
	Passenger *previous = pointers.first;
	int meal = -1;
	int seat = -1;

	if (current == NULL)
	{
		std::cout << "Reservation not found!" << std::endl << std::endl;
		return false;
	}

	while (true)
	{
		//Print current seat number.  Then, ask for changes
		std::cout << "Current seat number: " << current->seat_number() << std::endl;

		std::cout << "Enter -1 for no change." << std::endl;
		std::cout << "Seat Number: ";
		std::cin >> seat;

		//if -1, no change to seat number
		if (seat == -1)
		{
			break;
		}

		//validate new seat number
		if (std::cin.good() &&
			seat <= 122 &&
			seat > 0 &&
			!seatTaken(seat))
		{
			break;
		}

		// Throw seat errors.
		if (seatTaken(seat))
		{
			std::cout << "Seat already taken"
				<< std::endl;
			empty_buffer();
		}
		else
		{
			std::cout << "Seat number does not exist for this flight!"
				<< std::endl;
			empty_buffer();
		}
	}

	std::cout << std::endl
		<< " 1. Turkey Sandwich" << std::endl
		<< " 2. Shrimp Pasta" << std::endl
		<< " 3. Steak and Potatoes" << std::endl << std::endl;

	//Print current menu choice.  Then ask for changes
	std::cout << std::endl << "Current menu choice: " << current->menu_preference() << std::endl;

	while (true)
	{
		std::cout << "Enter -1 for no change." << std::endl;
		std::cout << "Menu Option: ";
		std::cin >> meal;

		//if -1, no change to menu option
		if (meal == -1)
		{
			break;
		}

		//validate menu option
		if (std::cin.good() &&
			meal <= 3 &&
			meal > 0)
		{
			break;
		}
		else
		{
			std::cout << "Invalid menu option!" << std::endl;
			empty_buffer();
		}
	}

	if (seat == -1 && meal == -1){
		std::cout << std::endl << "No changes made!" << std::endl << std::endl;
		return true;
	}

	//check to see if modification necessary for seat number
	if (current != NULL && seat != -1)
	{
		current->set_seat_number(seat);
		std::cout << "Seat number updated!" << std::endl;
	}

	//check to see if modification necessary for meal option
	if (current != NULL && meal != -1)
	{
		current->set_menu_preference(meal);
		std::cout << "Menu preference updated!" << std::endl;
	}

	return true;
}

void Reservation_List::print_report(){
	Passenger *temp = head;
	int count_turkey = 0, count_shrimp = 0,
		count_steak = 0, count_passengers = 0;

	while (temp != NULL){
		//add passenger
        count_passengers++;
		if (temp->menu_preference() == 1){
			count_turkey++;
		}
		else if (temp->menu_preference() == 2){
			count_shrimp++;
		}
		else if (temp->menu_preference() == 3){
			count_steak++;
		}

		temp = temp->next_passanger;
	}

	//print headings for report
    printElement("Passengers", 15);
	printElement("Turkey", 10);
	printElement("Shrimp", 10);
	printElement("Steak", 10);
	std::cout << std::endl;

	printElement(count_passengers, 15);
	printElement(count_turkey, 10);
	printElement(count_shrimp, 10);
	printElement(count_steak, 10);
	std::cout << std::endl << std::endl;
}