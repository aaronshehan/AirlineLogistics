#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Plane.h"
#include "Planes.h"
using namespace std;

void Planes::addPlane() {
	string mk, md, tnum;	//make, model, tail number
	int s, r;		//seats, range

	Plane temp;

	cout << "Enter the Make: "; getline(cin, mk);
	cout << "Enter the Model: "; cin >> md; cin.ignore();
	cout << "Enter the Tail Number: "; cin >> tnum; cin.ignore();
	cout << "Enter the Number of Seats: "; cin >> s; cin.ignore();
	cout << "Enter the Range: "; cin >> r; cin.ignore();


	temp.setMake(mk); temp.setModel(md); temp.setTNum(tnum);
	temp.setSeats(s); temp.setRange(r);

	planeList.push_back(temp);
	count += 1;
	savePlanes();

}

void Planes::printPlanes() {	//prints planes
	for (int i = 0; i < count; i++) {
		cout << "Make: " << planeList.at(i).getMake();
		cout << "\tModel: " << planeList.at(i).getModel();
		cout << "\tTail Number: " << planeList.at(i).getTNum();
		cout << "\tSeats: " << planeList.at(i).getSeats();
		cout << "\tRange: " << planeList.at(i).getRange();
		cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
	}
}

void Planes::savePlanes() {	//saves data to file
	ofstream fout;
	fout.open("Planes");
	fout << count << endl;

	for (int i = 0; i < count; i++) {
		fout << planeList.at(i).getMake() << "\t" << planeList.at(i).getModel() << "\t" << planeList.at(i).getTNum() << "\t" << planeList.at(i).getSeats();
		fout << "\t" << planeList.at(i).getRange() << "\t" << planeList.at(i).getStatus() << endl;
	}
	fout.close();
}

void Planes::loadPlanes() {	//reads in data from file
	ifstream fin;
	int s, r;
	string mk, md, tnum, st;
	fin.open("Planes");

	fin >> count; fin.ignore();

	for (int i = 0; i < count; i++) {
		Plane temp;
		getline(fin, mk, '\t');
		fin >> md >> tnum >> s >> r >> st;
		temp.setMake(mk);
		temp.setModel(md);
		temp.setTNum(tnum);
		temp.setSeats(s);
		temp.setRange(r);
		temp.setStatus(st);
		fin.ignore();
		planeList.push_back(temp);
	}
	fin.close();
}

void Planes::removePlane() {	//removes plane object
	string tnum;
	int index = -1;
	cout << "Enter the Tail Number of the Plane to remove: "; cin >> tnum; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getTNum() == tnum) {
			index = i;
			planeList.erase(planeList.begin() + index);
			count -= 1;
			savePlanes();
			break;
		}
	}

	if (index == -1) {
		cout << "Could not find Plane." << endl;
		return;
	}

}

void Planes::editPlane() {	//allows user to edit plane
	string tnum;
	int choice, r;
	int index = -1;
	cout << "Enter the Tail Number of the plane to edit: "; cin >> tnum; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getTNum() == tnum) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		cout << "Plane could not be found." << endl;
		return;
	}

	cout << "Enter 1 to edit Range, 2 to edit Status: "; cin >> choice; cin.ignore();

	if (choice == 1) {
		cout << "Enter new Range: "; cin >> r; cin.ignore();
		planeList.at(index).setRange(r);
		savePlanes();
		return;
	}

	if (choice == 2) {
		cout << "Enter 1 to change status to In, 2 for Out, 3 for Repair"; cin >> choice; cin.ignore();
		switch (choice) {
		case 1:
			planeList.at(index).setStatus("in");
			break;
		case 2:
			planeList.at(index).setStatus("out");
			break;
		case 3:
			planeList.at(index).setStatus("repair");
		}
		savePlanes();
		return;
	}

}

void Planes::searchPlanes() {	//provides menu to select specific detail to search for
	int choice;
	cout << "Enter: 1 for Make, 2 for Model, 3 for Tail Number, 4 for Number of Seats, 5 for Range, 6 for Status."; cin >> choice; cin.ignore();

	switch (choice) {
	case 1:
		printByMake();
		break;
	case 2:
		printByModel();
		break;
	case 3:
		printByTNum();
		break;
	case 4:
		printBySeats();
		break;
	case 5:
		printByRange();
		break;
	case 6:
		printByStatus();
		break;
		//default:

	}
}

void Planes::printByMake() {		//prints by make of plane
	string mk;
	int index = 0;
	cout << "Enter Make: "; getline(cin, mk);

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getMake() == mk) {
			index += 1;
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
		}
	}

	if (index == 0) {
		cout << "No planes of this model could be found." << endl;
		return;
	}
}

void Planes::printByModel() {	//prints by model of plane
	string md;
	int index = 0;
	cout << "Enter Model: "; cin >> md; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getModel() == md) {
			index += 1;
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
		}
	}

	if (index == 0) {
		cout << "No planes of this make could be found." << endl;
		return;
	}
}

void Planes::printByTNum() {	//prints by tail number of plane
	string tnum;
	int index = 0;
	cout << "Enter Tail Number: "; cin >> tnum; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getTNum() == tnum) {
			index += 1;
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
			break;
		}
	}

	if (index == 0) {
		cout << "No plane of this tail number could be found." << endl;
		return;
	}
}

void Planes::printBySeats() {	//prints by number of seats
	int s;
	int index = 0;
	cout << "Enter Number of Seats: "; cin >> s; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getSeats() == s) {
			index += 1;
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
		}
	}

	if (index == 0) {
		cout << "No planes could be found." << endl;
		return;
	}
}

void Planes::printByRange() {	//prints by range of plane
	int r;
	int index = 0;
	cout << "Enter Range: "; cin >> r; cin.ignore();

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getRange() == r) {
			index += 1;
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
		}
	}

	if (index == 0) {
		cout << "No planes could be found." << endl;
		return;
	}
}

void Planes::printByStatus() {	//prints by status of plane
	int choice;
	string st;

	cout << "Enter: 1 for In, 2 for Out, 3 for Repair. "; cin >> choice; cin.ignore();

	switch (choice) {
	case 1:
		st = "in";
		break;
	case 2:
		st = "out";
		break;
	case 3:
		st = "repair";
		break;
	}

	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getStatus() == st) {
			cout << "Make: " << planeList.at(i).getMake();
			cout << "\tModel: " << planeList.at(i).getModel();
			cout << "\tTail Number: " << planeList.at(i).getTNum();
			cout << "\tSeats: " << planeList.at(i).getSeats();
			cout << "\tRange: " << planeList.at(i).getRange();
			cout << "\tStatus: " << planeList.at(i).getStatus() << endl;
		}
	}
}

bool Planes::findPlane(string tnum) {	//checks to see if plane is available
	for (int i = 0; i < count; i++) {
		if (tnum == planeList.at(i).getTNum()) {
			if (planeList.at(i).getStatus() == "in") {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool Planes::checkPassengers(string tn, int np) {	//checks to see if their are enough seats for a flight
	for (int i = 0; i < count; i++) {
		if (planeList.at(i).getTNum() == tn) {
			if (np > planeList.at(i).getSeats()) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}