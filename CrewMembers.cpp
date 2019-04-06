#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <typeinfo>
#include "CrewMember.h"
#include "CrewMembers.h"
using namespace std;

void CrewMembers::addCrew() {	//adds crew member
	Crew *temp;	//temporary Crew pointer object
	string n, p, rc;	//name, position, rating code
	int fh, choice;	//flight hours, user choice

	cout << "Enter name: "; getline(cin, n);

	cout << "Enter 1 for Pilot, 2 for Co-Pilot, or 3 for Cabin: "; cin >> choice; cin.ignore();

	if (choice == 1) {
		cout << "Enter Rating Code (5 Characters): "; cin >> rc; cin.ignore();
		cout << "Enter Flight Hours: "; cin >> fh; cin.ignore();
		temp = new Pilot(rc, fh, n, 100000000 + count, "Available");
	}
	else if (choice == 2) {
		cout << "Enter Rating Code (4 Characters): "; cin >> rc; cin.ignore();
		cout << "Enter Flight Hours: "; cin >> fh; cin.ignore();
		temp = new CoPilot(rc, fh, n, 100000000 + count, "Available");
	}
	else if (choice == 3) {
		cout << "Enter Position ( First Class, Business Class EconomyFront, EconomyRear, Lead): "; cin >> p; cin.ignore();
		temp = new Cabin(p, n, 100000000 + count, "Available");
	}

	crewList.push_back(temp);
	count += 1;


}

void CrewMembers::printCrew() {	//prints crew member info
	if (count < 0) {
		return;
	}

	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		cout << "ID: " << (*it)->getID() << " Name: " << (*it)->getName() << " Status: " << (*it)->getStatus() << endl;

		if (typeid(**it) == typeid(Pilot)) {
			Pilot *tempP = dynamic_cast<Pilot*>(*it);
			cout << "Type: Pilot Rating Code: " << tempP->getRatingCode() << " Flight Hours: " << tempP->getFlightHours() << endl;
		}

		else if (typeid(**it) == typeid(CoPilot)) {
			CoPilot *tempCP = dynamic_cast<CoPilot*>(*it);
			cout << "Type: Co-Pilot Rating Code: " << tempCP->getRatingCode() << " Flight Hours: " << tempCP->getFlightHours() << endl;
		}

		else if (typeid(**it) == typeid(Cabin)) {
			Cabin *tempC = dynamic_cast<Cabin*>(*it);
			cout << "Type: Cabin Position: " << tempC->getPosition() << endl;
		}
	}
}

void CrewMembers::editCrew() {	//allows user to edit crew member
	int id, choice, fh;	//id, user choice, flight hours
	string p;	//position
	int index = -1;
	int type;
	cout << "Enter ID of the crew member to edit: "; cin >> id; cin.ignore();

	for (int i = 0; i < count; i++)
	{
		if (crewList[i]->getID() == id)
		{
			index = i;
			if (typeid(*crewList.at(i)) == typeid (Pilot)) {
				type = 1;
				break;
			}
			else if (typeid(*crewList.at(i)) == typeid (CoPilot)) {
				type = 2;
				break;
			}
			else if (typeid(*crewList.at(i)) == typeid (Cabin)) {
				type = 3;
				break;
			}
		}
	}

	if (index == -1) {
		cout << "Crew Member could not be found." << endl;
		return;
	}

	cout << "Enter 1 to change status, 2 for Flight Hours, or 3 for Position: "; cin >> choice; cin.ignore();

	if (choice == 1) {
		cout << "Enter 1 to change status to Available, 2 for On Leave, or 3 for Sick: "; cin >> choice; cin.ignore();
		if (choice == 1) {
			crewList[index]->setStatus("Available");
			saveCrew();
		}
		else if (choice == 2) {
			crewList[index]->setStatus("On Leave");
			saveCrew();
		}
		else if (choice == 3) {
			crewList[index]->setStatus("Sick");
			saveCrew();
		}
		return;
	}

	if (choice == 2) {
		if (type == 1) {
			Crew *temp;
			temp = crewList.at(index);
			Pilot *tempP = dynamic_cast<Pilot*> (temp);
			cout << "Enter the new Flight Hours: "; cin >> fh; cin.ignore();
			tempP->setFlightHours(fh);	//sets new data
			crewList.at(index) = tempP;	//new data at indexed element
			saveCrew();	//saves data to file
			return;
		}

		if (type == 2) {
			Crew *temp;
			temp = crewList.at(index);
			CoPilot *tempCP = dynamic_cast<CoPilot*> (temp);
			cout << "Enter the new Flight Hours: "; cin >> fh; cin.ignore();
			tempCP->setFlightHours(fh);	//sets new data
			crewList.at(index) = tempCP;	//new data at indexed element
			saveCrew();	//saves data to file
			return;
		}
	}

	if (choice == 3) {
		Crew *temp;
		temp = crewList.at(index);
		Cabin *tempC = dynamic_cast<Cabin*> (temp);
		cout << "Enter the new Position ( First Class, Business Class EconomyFront, EconomyRear, Lead): "; getline(cin, p);
		tempC->setPosition(p);	//sets new data
		crewList.at(index) = tempC;	//new data at indexed element
		saveCrew();	//saves data to file
	}
}

void CrewMembers::removeCrew() {	//allows user to remove crew member
	int id;
	cout << "Enter ID of the crew member to remove: "; cin >> id; cin.ignore();

	for (auto it = crewList.begin(); it != crewList.end(); ++it)
	{
		if ((*it)->getID() == id)
		{
			crewList.erase(it);	//erases element
			count -= 1;
			break;
		}
	}
	return;
}

Crew* CrewMembers::findCrew(int id) {
	Crew *temp;
	for (int i = 0; i < count; i++) {
		if (crewList[i]->getID() == id) {
			return crewList[i];
		}
	}
	return NULL;
}



void CrewMembers::saveCrew() {	//saves crew info to file
	ofstream fout;
	fout.open("CrewMembers");
	fout << count << endl;

	Crew *temp;
	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		temp = *it;
		fout << temp->getID() << "\t" << temp->getName() << "\t" << temp->getStatus() << endl;

		if (typeid(**it) == typeid (Pilot)) {
			Pilot *tempP = dynamic_cast<Pilot*> (temp);
			fout << "\t1\t" << tempP->getRatingCode() << "\t" << tempP->getFlightHours() << endl;
		}
		else if (typeid(**it) == typeid (CoPilot)) {
			CoPilot *tempCP = dynamic_cast<CoPilot*> (temp);
			fout << "\t2\t" << tempCP->getRatingCode() << "\t" << tempCP->getFlightHours() << endl;
		}
		else if (typeid(**it) == typeid (Cabin)) {
			Cabin *tempC = dynamic_cast<Cabin*> (temp);
			fout << "\t3\t" << tempC->getPosition() << "\t" << endl;
		}
	}
	fout.close();
}

void CrewMembers::loadCrew() {	//loads crew info from file
	ifstream fin;
	int id, t, fh;
	string n, s, p, rc;
	fin.open("CrewMembers");
	fin >> count; fin.ignore();
	Crew *temp;

	for (int i = 0; i < count; i++) {
		fin >> id; fin.ignore();
		getline(fin, n,'\t');
		fin >> s >> t;

		if (t == 1) {
			fin >> rc >> fh;
			Pilot *crew = new Pilot(rc, fh, n, id, s);
			crewList.push_back(crew);
		}

		else if (t == 2) {
			fin >> rc >> fh;
			CoPilot *crew = new CoPilot(rc, fh, n, id, s);
			crewList.push_back(crew);
		}

		else if (t == 3) {
			getline(fin, p);
			Cabin *crew = new Cabin(p, n, id, s);
			crewList.push_back(crew);
		}
	}

	fin.close();
}

void CrewMembers::findByName(string name) {	//prints crew by name
	for (int i = 0; i < count; i++) {
		if (crewList.at(i)->getName() == name) {
			cout << "Name: " << crewList.at(i)->getName() << "\tID: " << crewList.at(i)->getID() << "\tStatus: " << crewList.at(i)->getStatus() << endl;
			break;
		}
	}
} 

void CrewMembers::findByStatus(string status) {	//prints crew by status
	for (int i = 0; i < count; i++) {
		if (crewList.at(i)->getStatus() == status) {
			cout << "Name: " << crewList.at(i)->getName() << "\tID: " << crewList.at(i)->getID() << "\tStatus: " << crewList.at(i)->getStatus() << endl;
		}
	}
}
/*
void CrewMembers::findByType(string type) {
	for (int i = 0; i < count; i++) {
		if (crewList.at(i).getType() == type) {
			cout << "Name: " << crewList.at(i).getName() << "\tID: " << crewList.at(i).getID() << "\tType: " << crewList.at(i).getType() << "\tStatus: " << crewList.at(i).getStatus() << endl;
			break;
		}
	}
} */

void CrewMembers::searchCrew() {	//search crew by status
	int s;

		cout << "Enter: 1 to search for Available, 2 for On Leave, 3 for Sick" << endl; cin >> s; cin.ignore();
		switch (s) {
			case 1:
				findByStatus("Available");
				break;
			case 2:
				findByStatus("OnLeave");
				break;
			case 3:
				findByStatus("Sick");
				break;
		}
	
}

bool CrewMembers::findPilot(int id) {	//checks if pilot
	Crew *temp;
	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		temp = *it;
		if (temp->getID() == id && temp->getStatus() == "Available") {
			if (typeid(**it) == typeid (Pilot)) {
				return true;
			}
		}
	}
	return false;
}

bool CrewMembers::findCoPilot(int id) {	//checks if copilot
	Crew *temp;
	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		temp = *it;
		if (temp->getID() == id && temp->getStatus() == "Available") {
			if (typeid(**it) == typeid (CoPilot)) {
				return true;
			}
		}
	}
	return false;
}

bool CrewMembers::findCabin(int id) {	//checks if cabin
	Crew *temp;
	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		temp = *it;
		if (temp->getID() == id && temp->getStatus() == "Available") {
			if (typeid(**it) == typeid (Cabin)) {
				return true;
			}
		}
	}
	return false;
}

/*
int CrewMembers::findCrewID(string name) {

	for (int i = 0; i < count; i++) {
		if (name == crewList.at(i).getName()) {
			return crewList.at(i).getID();
		}
	}
	return -1;
} */

void CrewMembers::cleanup() {	//cleans up memory
	for (auto it = crewList.begin(); it != crewList.end(); ++it) {
		delete *it;
	}
	crewList.clear();
}

CrewMembers::~CrewMembers() {	//destructor
	cleanup();
}