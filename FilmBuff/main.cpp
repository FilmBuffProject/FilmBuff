#include <string>
#include <iostream>
#include "Movie.h"
#include "ProgramManager.h"
using namespace std;

int main() {
	ProgramManager db;
	db.initialize();
	bool cont = true;
	int option = 0;

	cout << "Welcome to FilmBuff! ";

	while (cont)
	{
		cout << "Select menu item:" << endl << "0. Exit FilmBuff" << endl << "1. Search Movie" << endl << "2. Search Personnel" << endl;
		cin >> option;

		switch (option)
		{
		default:
			cout << "none" << endl;
			break;
		case 0:
			cout << "Thanks for visiting!" << endl;
			cont = false;
			break;
		case 1:
			cout << "movie" << endl;
			break;
		case 2:
			cout << "personnel" << endl;
			break;
		}
	}

	return 0;
}