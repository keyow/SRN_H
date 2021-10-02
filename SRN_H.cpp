#include <iostream>
#include "MD5.h"
#include <iomanip>

using namespace std;

int main()
{
	string message = "";
	char answer = ' ';
	cout << "Start? (y/n)\t";
	cin >> answer;
	if (answer == 'y') {
		for (int i = 0; i < 1000; i++)
		{
			message += "a";
			cout << setfill(' ') << dec << setw(6) << i << "'a' symbols: ";
			MD5_starter(message);
		}
	}

	system("pause");
	return 0;
}