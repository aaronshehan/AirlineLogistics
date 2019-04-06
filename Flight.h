#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Flight {
private:
	string tNum;		//tail number
	int pID;		//pilot id
	int cpID;		//copilot id
	int cID1, cID2, cID3;	//cabin member #1 id, cabin member #2 id, cabin member #3 id
	int sDate;		//start date
	int eDate;		//end date
	string startCode;	//start code
	string endCode;		//end code
	int numPass;		//number of passengers
	string status;		//status
public:
	Flight();		//constructor
	void setTNum(string tn) { tNum = tn; }
	string getTNum() { return tNum; }
	void setPID(int id) { pID = id; }
	int getPID() { return pID; }
	void setCPID(int id) { cpID = id; }
	int getCPID() { return cpID; }
	void setCID1(int id) { cID1 = id; }
	int getCID1() { return cID1; }
	void setCID2(int id) { cID2 = id; }
	int getCID2() { return cID2; }
	void setCID3(int id) { cID3 = id; }
	int getCID3() { return cID3; }
	void setSDate(int sd) { sDate = sd; }
	int getSDate() { return sDate; }
	void setEDate(int ed) { eDate = ed; }
	int getEDate() { return eDate; }
	void setSCode(string sc) { startCode = sc; }
	string getSCode() { return startCode; }
	void setECode(string ec) { endCode = ec; }
	string getECode() { return endCode; }
	void setNumPass(int p) { numPass = p; }
	int getNumpass() { return numPass; }
	void setStatus(string s) { status = s; }
	string getStatus() { return status; }
};