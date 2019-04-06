#pragma once
#include <iostream>
#include <vector>
#include "CrewMember.h"
using namespace std;

class CrewMembers {
private:
	int count;	//crew count
	vector<Crew*>crewList;	//vector of pointers to objects
public:
	CrewMembers() { count = 0; }
	void addCrew();
	void printCrew();
	void editCrew();
	Crew *findCrew(int);
	void removeCrew();
	void saveCrew();
	void loadCrew();
	void findByName(string name);
	void searchCrew();
	void findByStatus(string status);
	//void findByType(string type);
	bool findPilot(int id);
	bool findCoPilot(int id);
	bool findCabin(int id);
	//int findCrewID(string name);
	void cleanup();
	~CrewMembers();
};