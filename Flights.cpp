#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "CrewMembers.h"
#include "Planes.h"
#include "Flights.h"
using namespace std;

extern CrewMembers crew;
extern Planes planes;

void Flights::addFlight() {	//adds Flight object to vector
	Flight temp;		//creates temp flight object
	string tnum, sc, ec;	//tail number, start code, end code
	string name;	//crew name
	bool checkNumP; //to check number of passengers
	bool planeMatch, crewMatch;	//used to check if plane/crew time is valid
	int id, nump;	//id, number of passengers
	struct tm t = { 0 };	//inintiales t struct members to 0
	int begin, end;		//start date, end date
	int month, day, year, hour, minute;	

	cout << "Enter the Start Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();

	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;

	begin = mktime(&t);
	temp.setSDate(begin);

	cout << "Enter the End Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();

	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;

	end = mktime(&t);
	temp.setEDate(end);

	cout << "Enter the Starting Airport Code: "; cin >> sc; cin.ignore();
	cout << "Enter the Ending Airport Code: "; cin >> ec; cin.ignore();
	cout << "Enter the Tail Number of the Plane to schedule: "; cin >> tnum; cin.ignore();
	planeMatch = planes.findPlane(tnum);	//checks if planes exists
	if (planeMatch == false) {
		cout << "This plane does not exist or is not available." << endl;
		return;
	}

	if (count > 0) {
		planeMatch = planeAvailable(tnum, begin, end);
		if (planeMatch = false) {
			cout << "This Plane is not available at the time entered." << endl;
			return;
		}
	}


	cout << "Enter the amount of passengers for this flight: "; cin >> nump; cin.ignore();

	checkNumP = planes.checkPassengers(tnum, nump);	//checks if number of passengers is valid
	if (checkNumP == false) {
		cout << "This plane does not have enough seats." << endl;
		return;
	}

	cout << "Enter the ID of the Pilot to schedule: "; cin >> id; cin.ignore();
	crewMatch = crew.findPilot(id);
	if (!crewMatch) {
		cout << "This person is not available, of the right type, or does not exist.";
		return;
	}

	if (count > 0) {
		crewMatch = pilotAvailable(id, begin, end);
		if (crewMatch == false) {
			cout << "This Pilot is not available at the time entered." << endl;
			return;
		}
	}
	temp.setPID(id);

	cout << "Enter the ID of the Co-Pilot to schedule: "; cin >> id; cin.ignore();
	crewMatch = crew.findCoPilot(id);

	if (!crewMatch) {
		cout << "This person is not available, of the right type, or does not exist.";
		return;
	}

	if (count > 0) {
		crewMatch = copilotAvailable(id, begin, end);
		if (crewMatch == false) {
			cout << "This Co-Pilot is not available at the time entered." << endl;
			return;
		}
	} 
	temp.setCPID(id);

	cout << "Enter the ID of Cabin member #1: "; cin >> id; cin.ignore();
	crewMatch = crew.findCabin(id);
	if (!crewMatch) {
		cout << "This person is not available, of the right type, or does not exist.";
		return;
	}
	
	if (count > 0) {
		crewMatch = cabinAvailable(id, begin, end);
		if (crewMatch == false) {
			cout << "This Cabin member is not available at the time entered." << endl;
			return;
		}
	}
	temp.setCID1(id);

	cout << "Enter the ID of Cabin member #2: "; cin >> id; cin.ignore();
	crewMatch = crew.findCabin(id);
	if (id == -1) {
		cout << "This Cabin member is not available, of the right type, or does not exist.";
		return;
	}
	
	if (count > 0) {
		crewMatch = cabinAvailable(id, begin, end);
		if (crewMatch == false) {
			cout << "This Cabin member is not available at the time entered." << endl;
			return;
		}
	}
	temp.setCID2(id);

	cout << "Enter the ID of Cabin member #3: "; cin >> id; cin.ignore();
	crewMatch = crew.findCabin(id);
	if (id == -1) {
		cout << "This person is not available, of the right type, or does not exist.";
		return;
	}
	
	if (count > 0) {
		crewMatch = cabinAvailable(id, begin, end);
		if (crewMatch == false) {
			cout << "This Cabin member is not available at the time entered." << endl;
			return;
		}
	}
	temp.setCID3(id);

	temp.setTNum(tnum);
	temp.setSCode(sc);
	temp.setECode(ec);
	temp.setNumPass(nump);

	flightList.push_back(temp);
	count += 1;
	saveFlights();

}

bool Flights::planeAvailable(string tn, int sd, int ed) {	//checks if planes is available
	bool match = false;
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getTNum() == tn) {
			if (sd >= flightList.at(i).getSDate() && sd <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else if (ed >= flightList.at(i).getSDate() && ed <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else {
				match = true;
			}
		}
	}
	return match;
}

bool Flights::pilotAvailable(int id, int sd, int ed) {	//checks if pilot is available
	bool match = false;
	int index = 0;
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getPID() == id) {
			index += 1;
			break;
		}
	}
	if (index == 0) {
		return true;
	}

	if (index)
		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getPID() == id) {
				if (sd >= flightList.at(i).getSDate() && sd <= flightList.at(i).getEDate()) {
					match = false;
					return match;
				}
				else if (ed >= flightList.at(i).getSDate() && ed <= flightList.at(i).getEDate()) {
					match = false;
					return match;
				}
				else {
					match = true;
				}
			}
		}
	return match;
}

bool Flights::copilotAvailable(int id, int sd, int ed) {	//checks if copilot is available
	bool match = false;
	int index = 0;
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCPID() == id) {
			index += 1;
			break;
		}
	}
	if (index == 0) {
		return true;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCPID() == id) {
			if (sd >= flightList.at(i).getSDate() && sd <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else if (ed >= flightList.at(i).getSDate() && ed <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else {
				match = true;
			}
		}
	}
	return match;
}

bool Flights::cabinAvailable(int id, int sd, int ed) {	//checks if cabin member is available
	bool match = false;
	int index = 0;
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCID1() == id || flightList.at(i).getCID2() == id || flightList.at(i).getCID3() == id) {
			index += 1;
			break;
		}
	}
	if (index == 0) {
		return true;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCID1() == id || flightList.at(i).getCID2() == id || flightList.at(i).getCID3() == id) {
			if (sd >= flightList.at(i).getSDate() && sd <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else if (ed >= flightList.at(i).getSDate() && ed <= flightList.at(i).getEDate()) {
				match = false;
				return match;
			}
			else {
				match = true;
			}
		}
	}
	return match;
}

void Flights::printFlights() {	//prints flights
	for (int i = 0; i < count; i++) {
		cout << "Flight #" << i + 1 << endl;
		cout << "Status: " << flightList.at(i).getStatus() << endl;
		cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
		cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
		cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
		cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
		cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
		cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
		cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
		cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl;
	}
}

void Flights::saveFlights() {	//saves to file
	ofstream fout;
	fout.open("Flights");

	fout << count << endl;
	for (int i = 0; i < count; i++) {
		fout << flightList.at(i).getPID() << "\t";
		fout << flightList.at(i).getCPID() << "\t";
		fout << flightList.at(i).getCID1() << "\t";
		fout << flightList.at(i).getCID2() << "\t";
		fout << flightList.at(i).getCID3() << "\t";
		fout << flightList.at(i).getTNum() << "\t";
		fout << flightList.at(i).getSCode() << "\t" << flightList.at(i).getECode() << "\t";
		fout << flightList.at(i).getSDate() << "\t" << flightList.at(i).getEDate() << "\t";
		fout << flightList.at(i).getNumpass() << "\t" << flightList.at(i).getStatus() << endl;
	}
	fout.close();
}

void Flights::loadFlights() {	//reads from file
	ifstream fin;
	int pid, cpid, cid1, cid2, cid3, nump, sd, ed;
	string tnum, sc, ec, st;
	fin.open("Flights");

	fin >> count; fin.ignore();
	for (int i = 0; i < count; i++) {
		Flight temp;
		fin >> pid >> cpid >> cid1 >> cid2 >> cid3 >> tnum >> sc >> ec >> sd >> ed >> nump >> st;
		temp.setPID(pid); temp.setCPID(cpid); temp.setCID1(cid1); temp.setCID2(cid2);
		temp.setCID3(cid3); temp.setTNum(tnum); temp.setSCode(sc); temp.setECode(ec);
		temp.setSDate(sd); temp.setEDate(ed); temp.setNumPass(nump); temp.setStatus(st);
		fin.ignore();
		flightList.push_back(temp);
	}
	fin.close();
}

void Flights::removeFlight() {	//allows user to remove flight
	int month, day, year, hour, minute;
	string name;
	bool crewMatch;
	int id, index;
	struct tm t = { 0 };
	int startTime;
	cout << "Enter the Start Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();
	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;
	startTime = mktime(&t);

	cout << "Enter the ID of the Pilot: "; cin >> id; cin.ignore();
	crewMatch = crew.findPilot(id);

	if (!crewMatch) {
		cout << "Pilot could not be found." << endl;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getPID() == id) {
			if (flightList.at(i).getSDate() == startTime) {
				index = i;
				flightList.erase(flightList.begin() + index);
				count -= 1;
				saveFlights();
				return;
			}
		}
	}

	cout << "No flight match was found." << endl;
}

void Flights::editFlight() {
	int choice;		//user choice 
	int month, day, year, hour, minute;
	int id;			//pilot id
	bool crewMatch;
	struct tm t = { 0 };	//initializes struct members to 0
	int startTime;		//start date
	cout << "Enter the Start Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();
	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;
	startTime = mktime(&t);

	cout << "Enter the ID of the Pilot: "; cin >> id; cin.ignore();
	crewMatch = crew.findPilot(id);	

	if (!crewMatch) {
		cout << "Pilot could not be found." << endl;
		return;
	}

	cout << "Enter 1 to change Flight status to Cancelled, Any other number to return to menu: "; cin >> choice; cin.ignore();

	if (choice != 1) {
		return;
	}
	
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getPID() == id) {
			if (flightList.at(i).getSDate() == startTime) {
				flightList.at(i).setStatus("Cancelled");
				saveFlights();
				return;
			}
		}
	}
	cout << "Flight could not be found." << endl;

	
}


void Flights::searchFlights() {	//provides menu to specifiy which detail the user would like to search flights by
	int choice;
	cout << "Enter number corresponding to detail: " << endl;
	cout << "\t1-Pilot" << endl << "\t2-Co-Pilot" << endl << "\t3-Cabin" << endl << "\t4-Start Code" << endl;
	cout << "\t5-End Code" << endl << "\t6-Start Date" << endl << "\t7-End Date" << endl << "\t8-Status" << endl; cin >> choice; cin.ignore();

	switch (choice) {
	case 1:
		findByPilot();
		break;
	case 2:
		findByCoPilot();
		break;
	case 3:
		findByCabin();
		break;
	case 4:
		findByCode("start");
		break;
	case 5:
		findByCode("end");
		break;
	case 6:
		findByDate("start");
		break;
	case 7:
		findByDate("end");
		break;
	case 8:
		findByStatus();
		break;
	}
}

void Flights::findByPilot() {	//finds flights by pilot and prints information
	string name;
	bool crewMatch;
	int id;
	cout << "Enter the ID of the Pilot: "; cin >> id; cin.ignore();
	crewMatch = crew.findPilot(id);

	if (!crewMatch) {
		cout << "Pilot could not be found." << endl;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getPID() == id) {
			cout << "Status: " << flightList.at(i).getStatus() << endl;
			cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
			cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
			cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
			cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
		}
	}
}

void Flights::findByCoPilot() {	//finds flights by copilot and prints information
	string name;
	bool crewMatch;
	int id;
	cout << "Enter the name of the Co-Pilot: "; cin >> id;  cin.ignore();
	crewMatch = crew.findCoPilot(id);

	if (!crewMatch) {
		cout << "Co-Pilot could not be found." << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCPID() == id) {
			cout << "Status: " << flightList.at(i).getStatus() << endl;
			cout << "Co-Pilot ID: " << flightList.at(i).getCPID() << endl;
			cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
			cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
			cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
		}
	}
}

void Flights::findByCabin() {	//finds flights by cabin member and prints information
	string name;
	int id;
	bool crewMatch;
	cout << "Enter the ID of the Cabin member: "; cin >> id; cin.ignore();
	crewMatch = crew.findCabin(id);

	if (!crewMatch) {
		cout << "Cabin member could not be found." << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getCID1() == id || flightList.at(i).getCID2() == id || flightList.at(i).getCID3() == id) {
			cout << "Status: " << flightList.at(i).getStatus() << endl;
			cout << "Cabin ID: " << id << endl;
			cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
			cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
			cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
		}
	}
}

void Flights::findByStatus() {	//finds flights by status and prints information
	int choice;
	string st;
	cout << "Enter number corresponding to detail:" << endl;
	cout << "\t1-Active" << endl << "\t2-Cancelled" << endl << "\t3-Completed" << endl; cin >> choice; cin.ignore();

	switch (choice) {
	case 1:
		st = "Active";
		break;
	case 2:
		st = "Cancelled";
		break;
	case 3:
		st = "Completed";
		break;
	}

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getStatus() == st) {
			cout << "Status: " << flightList.at(i).getStatus() << endl;
			cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
			cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
			cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
			cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
			cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
			cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
			cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
			cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
		}
	}
}

void Flights::findByDate(string eosdate) {	//finds flights by start or end date and prints information
	struct tm t = { 0 };
	int month, day, year, hour, minute, date;
	cout << "Enter the Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();

	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;

	date = mktime(&t);

	if (eosdate == "start") {
		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getSDate() == date) {
				cout << "Status: " << flightList.at(i).getStatus() << endl;
				cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
				cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
				cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
				cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
				cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
				cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
				cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
				cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
			}
		}
	}

	if (eosdate == "end") {
		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getEDate() == date) {
				cout << "Status: " << flightList.at(i).getStatus() << endl;
				cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
				cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
				cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
				cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
				cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
				cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
				cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
				cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
			}
		}
	}
}

void Flights::findByCode(string c) {	//finds flights by start or end code and prints information
	string eoscode;
	cout << "Enter the Code: "; cin >> eoscode; cin.ignore();

	if (c == "start") {
		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getSCode() == eoscode) {
				cout << "Status: " << flightList.at(i).getStatus() << endl;
				cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
				cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
				cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
				cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
				cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
				cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
				cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
				cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
			}
		}
	}

	if (c == "end") {
		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getECode() == eoscode) {
				cout << "Status: " << flightList.at(i).getStatus() << endl;
				cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
				cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
				cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
				cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
				cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
				cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
				cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
				cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
			}
		}
	}

}

void Flights::updateFlights() {	//checks current date and time to update flights

	int x = time(0);
	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getStatus() == "Active") {
			if (flightList.at(i).getEDate() <= x) {
				flightList.at(i).setStatus("Completed");
			}
		}
	}
	saveFlights();
}

void Flights::deleteCompletedFlights() {	//deletes all flights that are completed or cancelled
	for (int i = count - 1; i >= 0; i--) {
		if (flightList.at(i).getStatus() == "Completed" || flightList.at(i).getStatus() == "Cancelled") {
			flightList.erase(flightList.begin() + i);
			count -= 1;
		}
	}
	saveFlights();
}

void Flights::printSingleFlight() {	//prints single flight
	string name;
	int id;
	bool crewMatch;	//crew match
	cout << "Enter the ID of the Pilot: "; cin >> id; cin.ignore();
	crewMatch = crew.findPilot(id);	//check if crew exists

	struct tm t = { 0 };	//initializes struct to zero
	int month, day, year, hour, minute, date;
	cout << "Enter the Start Date and Time:" << endl;
	cout << "\tYear: "; cin >> year; cin.ignore(); year -= 1900;
	cout << "\tMonth (Ex. 1 for January): "; cin >> month; cin.ignore(); month -= 1;
	cout << "\tDay: "; cin >> day; cin.ignore();
	cout << "\tHour (GMT): "; cin >> hour; cin.ignore();
	cout << "\tMinute: "; cin >> minute; cin.ignore();

	t.tm_year = year; t.tm_mon = month;
	t.tm_mday = day; t.tm_mday = day;
	t.tm_hour = hour; t.tm_min = minute;

	date = mktime(&t);

	for (int i = 0; i < count; i++) {
		if (flightList.at(i).getPID() == id) {
			if (flightList.at(i).getSDate() == date) {
				cout << "Status: " << flightList.at(i).getStatus() << endl;
				cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
				cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
				cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
				cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
				cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
				cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
				cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
				cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
				return;
			}
		}
	}
	cout << "No flight with these details could be found." << endl;
}


void Flights::printActive() {	//prints active flights
	int choice, id;
	int index = 0;
	bool crewMatch;
	string name, tnum;
	cout << "Enter 1 to print active flights for a Crew Member, 2 for Planes, Any other number to return to menu: "; cin >> choice; cin.ignore();

	if (choice > 2 || choice < 1) {
		return;
	}

	if (choice == 1) {
		cout << "Enter ID of the Crew Member: "; cin >> id; cin.ignore();
		crewMatch = crew.findPilot(id);
		if (crewMatch) {
			for (int i = 0; i < count; i++) {
				if (flightList.at(i).getPID() == id) {
					if (flightList.at(i).getStatus() == "Active") {
						cout << "Status: " << flightList.at(i).getStatus() << endl;
						cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
						cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
						cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
						cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl << endl;
					}
				}
			}
			return;
		}

		crewMatch = crew.findCoPilot(id);

		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getCPID() == id) {
				if (flightList.at(i).getStatus() == "Active") {
					cout << "Status: " << flightList.at(i).getStatus() << endl;
					cout << "Co-Pilot ID: " << flightList.at(i).getCPID() << endl;
					cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
					cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
					cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl << endl;
				}
			}
		}


		crewMatch = crew.findCabin(id);

		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getCID1() == id || flightList.at(i).getCID2() == id || flightList.at(i).getCID3() == id) {
				if (flightList.at(i).getStatus() == "Active") {
					index += 1;
					cout << "Status: " << flightList.at(i).getStatus() << endl;
					cout << "Cabin ID: " << id << endl;
					cout << "Tail Number: " << flightList.at(i).getTNum() << endl;
					cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
					cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl << endl;
				}
			}
		}
		if (index > 0) {
			cout << "Crew Member could not be found." << endl;
			return;
		}
		return;
	}

	if (choice == 2) {
		cout << "Enter Tail Number: "; cin >> name;

		for (int i = 0; i < count; i++) {
			if (flightList.at(i).getTNum() == name) {
				if (flightList.at(i).getStatus() == "Active") {
					cout << "Status: " << flightList.at(i).getStatus() << endl;
					cout << "Pilot ID: " << flightList.at(i).getPID() << endl;
					cout << "CoPilot ID: " << flightList.at(i).getCPID() << endl;
					cout << "Cabin #1 ID: " << flightList.at(i).getCID1() << endl;
					cout << "Cabin #2 ID: " << flightList.at(i).getCID2() << endl;
					cout << "Cabin #3 ID: " << flightList.at(i).getCID3() << endl << "Tail Number: " << flightList.at(i).getTNum() << endl;
					cout << "Start Code: " << flightList.at(i).getSCode() << "  \tEnd Code: " << flightList.at(i).getECode() << endl;
					cout << "Start Time: " << flightList.at(i).getSDate() << "  \tEnd Time: " << flightList.at(i).getEDate() << endl;
					cout << "Number of Passengers: " << flightList.at(i).getNumpass() << endl << endl;
				}
			}
		}
	}

}