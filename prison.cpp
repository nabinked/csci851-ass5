/**********************************************************************
 * prison.c - CSCI251/851 - Ass5- Prison class definitions
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include "prison.h"
#include "crim.h"
#include "utils.h"
using namespace std;
using namespace utils;


// ========== class Prison Function definitions ==========
//Constructor
Prison::Prison() {
	FileName = "crims.txt";
}


// Destructor: Iterates Crims set and deletes each ptr to Criminal 
Prison::~Prison() {
	for (CriminalIterator criminalItr = Crims.begin(); criminalItr != Crims.end(); criminalItr++)
	{
		delete (*criminalItr);
	}
}

// Reads data in "crims.txt" into Crims set
void Prison::ReadCrimFile() {
	ifstream fin(FileName);
	if (fin.fail()) {
		cout << "File not found";
		return;
	}
	int linePosition = 0;
	while (!fin.eof()) {

		string tempLine;
		getline(fin, tempLine);
		if (fin.eof()) break;
		Crims.insert(GetCriminal(tempLine, linePosition));
		linePosition++;
	}
	fin.close();
	cout << Crims.size() << " criminals found." << endl;;
}

// Iterates Crims set and displays criminal records on screen 10 at a time
void Prison::DisplayPrisioners() {

	for (CriminalIterator criminalIterator = Crims.begin(); criminalIterator != Crims.end();)
	{
		for (size_t i = 0; criminalIterator != Crims.end() && i < 10; i++)
		{
			if (*criminalIterator) {
				(*criminalIterator)->Print();
				criminalIterator++;
			}
		}
		if (criminalIterator != Crims.end() && !Continue()) {
			break;
		}
	}
}

Criminal* Prison::GetCriminal(string line, int cellNo)
{
	istringstream iStringStrm(line);
	Criminal* criminal;
	string fName, lName, crime, victimfName, victimlName;
	int months, amount = 0;
	iStringStrm >> fName;
	iStringStrm >> lName;
	iStringStrm >> crime;
	iStringStrm >> months;
	if (crime == "ROBBERY") {
		iStringStrm >> amount;
		criminal = new Robber(fName, lName, crime, months, amount, cellNo);
	}
	else if (crime == "MURDER") {
		iStringStrm >> victimfName;
		iStringStrm >> victimlName;
		criminal = new Murderer(fName, lName, crime, months, victimfName, victimlName, cellNo);
	}
	else {
		criminal = new Criminal(fName, lName, crime, months, cellNo);
	}
	return criminal;

}

