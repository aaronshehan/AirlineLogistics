#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Plane.h"
using namespace std;

class Planes {
private:
	int count;
	vector<Plane>planeList;	//vector of Plane objects
public:
	Planes() { count = 0; }	//constructor
	void addPlane();
	void printPlanes();
	void savePlanes();
	void loadPlanes();
	void removePlane();
	void editPlane();
	void searchPlanes();
	void printByMake();
	void printByModel();
	void printByTNum();
	void printBySeats();
	void printByRange();
	void printByStatus();
	bool findPlane(string tnum);
	bool checkPassengers(string tn, int np);


};
