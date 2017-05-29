#include <string>
#include "prison.h"
using namespace std;
namespace utils
{
	bool Prompt(string text = "Continue? (y/n): ");
	void ClearInput();
	void WriteToFile(CriminalSet crims, string fileName = "crims.txt");
	void WriteRecord(Criminal *crim, ofstream &fout);
	template<typename T>
	void GetUserInputTo(T &object, const string prompt);
	bool IsAllAlpha(string &str);
	void MakeUpper(string &str);
	void MakeFirstLetterUpper(string &str);

	template<typename T>
	void GetUserInputTo(T & object, const string prompt)
	{
		cout << prompt;
		while (!(cin >> object)) {
			cout << "Invalid input please try again" << endl;
			ClearInput();
			cout << prompt;
		}
		ClearInput();
	}

}

