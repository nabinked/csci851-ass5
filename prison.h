/**********************************************************************
 * prison.h - CSCI251/851 - Ass5- Prison class declaration
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#ifndef PRISON_H
#define PRISON_H

#include <iostream>
#include <cstring>
#include <set>
#include "crim.h"
using namespace std;


struct Comp
{
	bool operator()(Criminal* x, Criminal* y) { return(*x < *y); }; // compare what pointers are pointing at
};

typedef set<Criminal*, Comp>::iterator CriminalIterator;
typedef set<Criminal*, Comp> CriminalSet;


class Prison {
public:
	Prison();
	~Prison();
	void ReadCrimFile();
	void DisplayPrisioners(); // prints inmates in order of their names
	void ReduceSentence();
	void CheckForParole();
	void AddNewPrisoner();
private:
	set<Criminal*, Comp> Crims; // set of pointers to class Criminal
	string FileName; //input file name crims.txt;
	Criminal* GetCriminal(string line, int cellNo);
	void ProcessSenetenceReduced(CriminalSet &criminalsToRelease);
	void ProcessParole(CriminalSet &criminalsToRelease);
	string GetName(string type);
	int GetMonths();
	bool ValidName(string & name);

};


#endif

