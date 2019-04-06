#include "CrewMember.h"

Crew::Crew(string n, int i, string s) {
	status = s;
	id = i;
	name = n;
}


void Crew::print() {
	cout << "ID: " << id << " Name: " << name << " Status: " << status << endl;
}

Pilot::Pilot(string rc, int fh, string n, int i, string s) :Crew(n, i, s) {
	ratingCode = rc;
	flightHours = fh;
}


void Pilot::print() { 	//prints Pilot info
	Crew::print();
	cout << "Type: Pilot " << "Rating Code: " << ratingCode << " Flight Hours: " << flightHours << endl;
}

CoPilot::CoPilot(string rc, int fh, string n, int i, string s) :Crew(n, i, s) {	
	ratingCode = rc;
	flightHours = fh;
}


void CoPilot::print() {	//prints CoPilot info
	Crew::print();
	cout << "Type: Co-Pilot " << "Rating Code: " << ratingCode << " Flight Hours: " << flightHours << endl;
}

Cabin::Cabin(string p, string n, int i, string s) :Crew(n, i, s) { //
	position = p;
}

void Cabin::print() {	//prints Cabin info
	Crew::print();
	cout << "Type: Cabin " << "Position: " << position << endl;
}

ostream& operator<<(ostream& st, Crew& it) {
	it.print();
	return st;
}