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
	string search = "";

	cout << "Welcome to FilmBuff! ";

	while (cont)
	{
		cout << "Select menu item:" << endl << "0. Exit FilmBuff" << endl << "1. Search Movie" << endl << "2. Search Personnel" << endl;
		cin >> option;
		cin.ignore();

		switch (option)
		{
		default:
		{
			cout << "none" << endl;
			break;
		}
		case 0:
		{
			cout << "Thanks for visiting!" << endl;
			cont = false;
			break;
		}
		case 1: 
		{		
			string temp = "";
			
			cout << "Please enter a keyword to search for: ";
			getline(cin, search);

			vector<string> movies = db.searchMovies(search);

			cout << "Please enter space separated list of movies you wish to add: ";
			getline(cin, search);

			for (int i = 0; i < search.length(); i++) {
				if (search[i] == ' ') {
					if (stoi(temp) - 1 < movies.size()) {
						db.addPreferences(movies[stoi(temp) - 1]);
					}
					else {
						cout << "List only contains " << movies.size() << " movies. Could not add movie #" << temp << "!" << endl;
					}

					temp = "";
					continue;
				}

				temp += search[i];
			}

			if (stoi(temp) - 1 < movies.size()) {
				db.addPreferences(movies[stoi(temp) - 1]);
			}
			else {
				cout << "List only contains " << movies.size() << " movies. Could not add movie #" << temp << "!" << endl;
			}

			break;
		}
		case 2: 
		{
			string temp = "";
			
			cout << "Please enter an actor to search for: ";
			getline(cin, search);

			vector<string> movies = db.searchPersonnel(search);

			cout << "Please enter space separated list of movies you wish to add: ";
			getline(cin, search);

			for (int i = 0; i < search.length(); i++) {
				if (search[i] == ' ') {
					if (stoi(temp) - 1 < movies.size()) {
						db.addPreferences(movies[stoi(temp) - 1]);
					}
					else {
						cout << "List only contains " << movies.size() << " movies. Could not add movie #" << temp << "!" << endl;
					}

					temp = "";
					continue;
				}

				temp += search[i];
			}

			if (stoi(temp) - 1 < movies.size()) {
				db.addPreferences(movies[stoi(temp) - 1]);
			}
			else {
				cout << "List only contains " << movies.size() << " movies. Could not add movie #" << temp << "!" << endl;
			}

			break;
		}
		}
	}

	return 0;
}