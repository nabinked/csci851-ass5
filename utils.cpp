#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"
#include "prison.h"
#include <algorithm>


using namespace std;

namespace utils
{
	bool Prompt(string txt)
	{
		cout << endl;
		cout << txt;
		char Ans;
		cin >> Ans;
		if (toupper(Ans) == 'Y') {
			ClearInput();
			return true;
		}
		else {
			ClearInput();
			return false;
		}
	};

	void ClearInput()
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void WriteToFile(CriminalSet crims, string fileName)
	{
		ofstream fout(fileName);
		if (fout.fail()) {
			return;
		}
		for (CriminalIterator crimItr = crims.begin(); crimItr != crims.end(); crimItr++)
		{
			WriteRecord((*crimItr), fout);
		}
		fout.close();

	}

	//Write a record to filestream
	void WriteRecord(Criminal*crim, ofstream &fout)
	{
		Criminal c = (*crim);
		fout << c.GetFirstName() << " " << c.GetFamilyName() << " " << c.GetCrime() << c.GetMonths();
		Robber* r = dynamic_cast<Robber*>(crim);
		if (r != NULL) {
			fout << " " << (*r).GetAmountStolen();
		}
		Murderer* m = dynamic_cast<Murderer*>(crim);
		if (m != NULL) {
			fout << " " << (*m).GetVictimFirstName() << " " << (*m).GetFamilyName();
		}
		fout << endl;

	}

	//Check all alphabets
	bool IsAllAlpha(string &str)
	{

		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ') {
				if (!isalpha(str[i])) {
					return false;
				}
			}
		}
		return true;
	}

	// Takes a string input and turns it into upper case
	void MakeUpper(string &str)
	{
		transform(str.begin(), str.end(), str.begin(), ::toupper);
	}

	//Make first letter uppercase
	void MakeFirstLetterUpper(string &str)
	{
		str[0] = toupper(str[0]);
		for (size_t i = 1; i < str.length(); ++i)
			str[i] = tolower(str[i]);
	}
}