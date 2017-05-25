/**********************************************************************
 * crim.h - CSCI251/851 - Ass5- Criminal class declaration
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#ifndef CRIM_H
#define CRIM_H

#include <string>
using namespace std;

// base class...

class Criminal {
public:
	Criminal();
	Criminal(string FName, string LName, string Crm, int Mths, int Cell);
	bool operator<(const Criminal &C);
	virtual void Print();
protected:
	string FamilyName, FirstName; // Prisoner's name
	string Crime; // Crime Committed 
	int Months;// Number of months remaining in sentence
	int CellNo; // The cell the inmate occupies, initially set to -1
};

//derived classes...

class Robber : public Criminal {
public:
	Robber::Robber(string FName, string LName, string Crm, int Mths, int Amnt, int Cell) : Criminal(FName, LName, Crm, Mths, Cell) {
		AmountStolen = Amnt;
	}
	void Print() {
		cout << "Cell " << this->CellNo << " " << this->FamilyName << ", " << this->FirstName << " ";
		cout << "[" << this->Months << " months for stealing" << " $" << AmountStolen << "]" << endl;
	}
private:
	int AmountStolen;
};

class Murderer : public Criminal
{
public:
	Murderer::Murderer(string FName, string LName, string Crm, int Mths, string victimfName, string victimlName, int Cell) : Criminal(FName, LName, Crm, Mths, Cell) {
		VictimsFirstName = victimfName;
		VictimsFamilyName = victimlName;
	}
	void Print() {
		cout << "Cell " << this->CellNo << " " << this->FamilyName << ", " << this->FirstName << " ";
		cout << "[" << this->Months << " months for murdering" << " " << VictimsFamilyName << ", " << FirstName << "]" << endl;
	}
private:
	string VictimsFirstName, VictimsFamilyName;
};

#endif

