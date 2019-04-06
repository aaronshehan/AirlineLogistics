#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Crew {
private:
	string name;
	int id;
	//string type;
	string status;
public:
	Crew(string, int, string);	//constructor
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setID(int i) { id = i; }
	int getID() { return id; }
	//void setType(string t) { type = t; }
	//string getType() { return type; }
	void setStatus(string s) { status = s; }
	string getStatus() { return status; }
	virtual void print();
	friend ostream& operator<<(ostream& st, Crew& it);
};

class Pilot : public Crew {	//child class of Crew
private:
	string ratingCode;
	int flightHours;

public:
	Pilot(string rc, int fh, string n, int i, string s);
	void setRatingCode(string rc) { ratingCode = rc; }
	void setFlightHours(int fh) { flightHours = fh; }
	string getRatingCode() { return ratingCode; }
	int getFlightHours() { return flightHours; }
	void print();
};

class CoPilot : public Crew {	//child class of Crew
private:
	string ratingCode;
	int flightHours;
public:
	CoPilot(string rc, int fh, string n, int i, string s);
	void setRatingCode(string rc) { ratingCode = rc; }
	void setFlightHours(int fh) { flightHours = fh; }
	string getRatingCode() { return ratingCode; }
	int getFlightHours() { return flightHours; }
	void print();
};

class Cabin : public Crew {	//child class of Crew
private:
	string position;
public:
	Cabin(string p, string n, int i, string s);
	void setPosition(string p) { position = p; }
	string getPosition() { return position; }
	void print();
};