/**********************************************************************
 * crim.cpp - CSCI251/851 - Ass5- Criminal class definition
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include "crim.h"
#include "utils.h"
using namespace std;

// ========== Base class Criminal Function definitions ==========

// Default constructor: inits Months to zero and CellNo to -1
Criminal::Criminal() {
	this->Months = 0;
	this->CellNo = -1;
}

// Standard constructor
Criminal::Criminal(string FName, string LName, string Crm, int Mths, int Cell) {
	this->FirstName = FName;
	this->FamilyName = LName;
	this->Crime = Crm;
	this->Months = Mths;
	this->CellNo = Cell;
}

// Operator< returns true if *this name is less than Other name
bool Criminal::operator<(const Criminal &Other) {

	return this->FamilyName < Other.FamilyName;
}

// Prints criminal details on screen
void Criminal::Print() {
	cout << "Cell " << this->CellNo << " " << this->FamilyName << ", " << this->FirstName << " ";
	cout << "[" << this->Months << " months for " << this->Crime << "]" << endl;
}

