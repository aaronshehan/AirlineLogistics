#pragma once
#include <iostream>
#include <string>
using namespace std;

class Plane {
	private:
		string make;	//plane make
		string model;	//plane model
		string tailNumber;	//plane tail number
		int seats;	//number of seats
		int range;	//range of plane
		string status;	//plane status

	public:
		Plane();	//constuctor
		void setMake(string mk) { make = mk; }
		string getMake() { return make; }
		void setModel(string md) { model = md; }
		string getModel() { return model; }
		void setTNum(string tnum) { tailNumber = tnum; }
		string getTNum() { return tailNumber; }
		void setSeats(int s) { seats = s; }
		int getSeats() { return seats; }
		void setRange(int r) { range = r; }
		int getRange() { return range; }
		void setStatus(string st) { status = st; }
		string getStatus() { return status; }
};