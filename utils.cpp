#include <iostream>
#include "Utils.h"
using namespace std;

namespace utils
{
	bool Continue() 
	{
		cout << endl;
		cout << "Continue? (y/n): ";
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

}