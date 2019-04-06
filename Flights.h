#pragma once
#include "Flight.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Flights {
private:
	int count;
	vector<Flight>flightList; //vector of Flight objects
public:
	Flights() { count = 0; }	//constructor
	void addFlight();
	bool planeAvailable(string tn, int sd, int ed);
	bool pilotAvailable(int id, int sd, int ed);
	bool copilotAvailable(int id, int sd, int ed);
	bool cabinAvailable(int id, int sd, int ed);
	void printFlights();
	void removeFlight();
	void editFlight();
	void saveFlights();
	void loadFlights();
	void searchFlights();
	void findByPilot();
	void findByCoPilot();
	void findByCabin();
	void findByStatus();
	void findByDate(string eosdate);
	void findByCode(string c);
	void updateFlights();
	void printSingleFlight();;
	void deleteCompletedFlights();
	void printActive();
};