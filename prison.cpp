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
		if (criminalIterator != Crims.end() && !Prompt()) {
			break;
		}
	}
}

void Prison::ReduceSentence()
{
	CriminalSet criminalsToRelease;
	for (CriminalIterator criminalItr = Crims.begin(); criminalItr != Crims.end(); criminalItr++)
	{
		(*criminalItr)->ReduceSentence(6);
		if ((*criminalItr)->CanBeReleased()) {
			criminalsToRelease.insert(*criminalItr);
		}
	}

	if (criminalsToRelease.size() > 0) {
		ProcessSenetenceReduced(criminalsToRelease);
	}
	WriteToFile(Crims);
}

void Prison::CheckForParole()
{
	CriminalSet criminalsToParole;
	for (CriminalIterator criminalItr = Crims.begin(); criminalItr != Crims.end(); criminalItr++)
	{
		if ((*criminalItr)->ReadyForParole()) {
			criminalsToParole.insert(*criminalItr);
		}
	}

	if (criminalsToParole.size() > 0) {
		ProcessParole(criminalsToParole);
	}
	WriteToFile(Crims);
}

void Prison::AddNewPrisoner()
{
	Criminal *newCrim = new Criminal();

	//First name
	newCrim->SetFirstName(GetName("First"));

	//Fam Name
	string famName = GetName("Family");
	MakeUpper(famName);
	newCrim->SetFamilyName(famName);

	//Crime
	string crime;
	GetUserInputTo(crime, "Crime: ");
	MakeUpper(crime);
	newCrim->SetCrime(crime);

	//sentence
	newCrim->SetMonths(GetMonths());

	//Cell no
	newCrim->SetCellNo(Crims.size() + 1);
	newCrim->Print();

	Crims.insert(newCrim);
	WriteToFile(Crims);
	cout << "... has been added to prison" << endl;
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

void Prison::ProcessSenetenceReduced(CriminalSet &criminalsToRelease)
{
	cout << criminalsToRelease.size() << " prisoners have reached their release date." << endl;
	for (CriminalIterator crimItr = criminalsToRelease.begin(); crimItr != criminalsToRelease.end(); crimItr++)
	{
		(*crimItr)->Print();
	}
	for (CriminalIterator crimItr = Crims.begin(); crimItr != Crims.end();)
	{
		string fName = (*crimItr)->GetFirstName();
		string famName = (*crimItr)->GetFamilyName();
		if ((*crimItr)->CanBeReleased()) {
			string prompt = "Do you want to release " + fName + " " + famName + " (y/n)?";
			if (Prompt(prompt)) {
				Crims.erase(crimItr++);//Remove from list
				cout << fName << " " << famName << " has been released" << endl;
			}
			else {
				(*crimItr)->SetMonths(6);
				cout << fName << " " << famName << "'s sentence has been increased to 6 months" << endl;
				crimItr++;
			}
		}
		else {
			crimItr++;
		}

	}
}

void Prison::ProcessParole(CriminalSet & criminalsToRelease)
{
	cout << criminalsToRelease.size() << " prisoners have reached their parole date." << endl;
	for (CriminalIterator crimItr = criminalsToRelease.begin(); crimItr != criminalsToRelease.end(); crimItr++)
	{
		(*crimItr)->Print();
	}

	for (CriminalIterator crimItr = Crims.begin(); crimItr != Crims.end();)
	{
		string fName = (*crimItr)->GetFirstName();
		string famName = (*crimItr)->GetFamilyName();
		if ((*crimItr)->ReadyForParole()) {
			string prompt = "Do you want to	parole " + fName + " " + famName + " (y/n)?";
			if (Prompt(prompt)) {
				Crims.erase(crimItr++);//Remove from list
				cout << fName << " " << famName << " has been paroled" << endl;
			}
			else {
				crimItr++;
				cout << fName << " " << famName << " has been refused" << endl;
			}
		}
		else {
			crimItr++;
		}
	}

}

//Get Name from cin
string Prison::GetName(string type)
{
	string input;
	GetUserInputTo(input, type + " Name: ");
	if (ValidName(input)) {
		MakeFirstLetterUpper(input);
		return input;
	}
	else {
		return GetName(type);
	}
}

int Prison::GetMonths()
{
	int months;
	GetUserInputTo(months, "Senetence (months): ");
	if (months > 1) {
		return months;
	}
	else {
		return GetMonths();
	}

}


//Validate name
bool Prison::ValidName(string &name)
{
	//check for length
	if (name.length() < 1 || name.length() > 50) {
		cout << "Name length is not valid. Name must be between 1 and 50 characters." << endl;
		return false;
	}
	//check if all alphabets
	if (!IsAllAlpha(name)) {
		cout << "Name should be all alphabet." << endl;
		return false;
	}
	return true;
}
