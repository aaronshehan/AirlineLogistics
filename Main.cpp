/*	Aaron Shehan
	ats0109
	aaronshehan@my.unt.edu
	CSCE 1040
	Computer Science and Engineering
	Homework 5*/




#include <iostream>
#include <string>
#include "CrewMembers.h"
#include "Planes.h"
#include "Flights.h"
using namespace std;

CrewMembers crew;
Planes planes;
Flights flights;

int Menu() { 		//Menu to diplays options
	int choice;

	cout << "Choose an option: " << endl << "\t0-Quit" << endl;
	cout << "\t1-Add Crew Member" << endl << "\t2-Add Plane" << endl;
	cout << "\t3-Add Flight" << endl << "\t4-Edit Crew Member" << endl << "\t5-Edit Plane" << endl;
	cout << "\t6-Edit Flight" << endl << "\t7-Remove Crew Member" << endl << "\t8-Remove Plane" << endl;
	cout << "\t9-Remove Flight" << endl << "\t10-Print All Crew" << endl;
	cout << "\t11-Print All Planes" << endl << "\t12-Print All Flights" << endl;
	cout << "\t13-Print Single Crew Member" << endl << "\t14-Print Single Plane" << endl << "\t15-Print Single Flight" << endl;
	cout << "\t16-List Crew Members by Type/Status" << endl << "\t17-List Flights by Criteria";
	cout << endl << "\t18-List Planes by Criteria" << endl << "\t19-Remove Cancelled/Completed Flights" << endl << "\t20-Print Crew/Plane Active flights" << endl;
	cout << "\t21-Save Data" << endl << "\t22-Load Data" << endl;
	cin >> choice; cin.ignore();

	return choice;
}
int main()
{

cout << "\t\t**********************************************" << endl;
cout<< "\t\t\t\tAaron Shehan" << endl;
cout<< "\t\t\t\tats0109" << endl;
cout<< "\t\t\t\taaronshehan@my.unt.edu" << endl;
cout<< "\t\t\t\tCSCE 1040" << endl;
cout<< "\t\t\t\tHomework 5" << endl;
cout << "\t\t**********************************************" << endl;


	int choice;		//stores input for menu selection
	string name;		//stores name when prompted
	do {
		choice = Menu();

		switch (choice) {
		case 0: {
			break;
		}
		case 1: {
			crew.addCrew();
			break;
		}
		case 2: {
			planes.addPlane();
			break;
		}
		case 3: {
			flights.addFlight();
			break;
		}
		case 4: {
			crew.editCrew();
			break;
		}
		case 5: {
			planes.editPlane();
			break;
		}
		case 6: {
			flights.editFlight();
			break;
		}
		case 7: {
			crew.removeCrew();
			break;
		}
		case 8: {
			planes.removePlane();
			break;
		}
		case 9: {
			flights.removeFlight();
			break;
		}
		case 10: {
			crew.printCrew();
			break;
		}
		case 11: {
			planes.printPlanes();
			break;
		}
		case 12: {
			flights.printFlights();
			break;
		}
		case 13: {
			cout << "Enter Name: "; getline(cin, name);
			crew.findByName(name);
			break;
		}
		case 14: {
			planes.printByTNum();
			break;
		}
		case 15: {
			flights.printSingleFlight();
			break;
		}
		case 16: {
			crew.searchCrew();
			break;
		}
		case 17: {
			flights.searchFlights();
			break;
		}
		case 18: {
			planes.searchPlanes();
			break;
		}
		case 19: {
			flights.deleteCompletedFlights();
			break;
		}
		case 20: {
			flights.printActive();
			break;
		}
		case 21: {
			crew.saveCrew();
			planes.savePlanes();
			flights.saveFlights();
			break;
		}
		case 22: {
			crew.loadCrew();
			planes.loadPlanes();
			flights.loadFlights();
			break;
		}
		default: {
			cout << "Choose Again" << endl;
			choice = Menu();
			break;
		}

		}
		flights.updateFlights();	//updates flights to completed
	} while (choice != 0);			//loop repeats when user does not input 0

	return 0;
}

