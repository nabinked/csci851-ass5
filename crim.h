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
	void ReduceSentence(int months);
	bool CanBeReleased();
	virtual bool ReadyForParole();
	//get-set
	int GetMonths();
	void SetMonths(int months);

	string GetFamilyName();
	void SetFamilyName(string famName);
	
	string GetFirstName();
	void SetFirstName(string fName);

	string GetCrime();
	void SetCrime(string crime);

	void SetCellNo(int cellNo);

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
	bool ReadyForParole() {
		return this->Months <= 12;
	}
	int GetAmountStolen() {
		return this->AmountStolen;
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

	bool ReadyForParole() {
		return this->Months <= 6;
	}

	string GetVictimFirstName()
	{
		return this->VictimsFirstName;
	}

	string GetVictimFamilyName()
	{
		return this->VictimsFamilyName;
	}
private:
	string VictimsFirstName, VictimsFamilyName;
};

#endif

