#include <string>
#include <iostream>
#include "Movie.h"
#include "ProgramManager.h"
#include "movieGraph.h";
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
		cout << "Select menu item:" << endl << "0. Exit FilmBuff" << endl << "1. Display Current Preferences" << endl << "2. Search Movie" << endl << "3. Search Personnel" << endl << "4. Get Recommendations" << endl << "5. Display Movie Graph" << endl;
		cin >> option;
		cin.ignore();

		switch (option)
		{
		default:
		{
			cout << "Please select a valid option." << endl;

			break;
		}
		case 0:
		{
			cout << "Thanks for visiting!" << endl;
			cont = false;
			db.writePreferred();

			break;
		}
		case 1:
		{
			db.displayPreferences();

			break;
		}
		case 2: 
		{		
			string temp = "";
			
			cout << "Please enter a keyword to search for: ";
			getline(cin, search);

			vector<string> movies = db.searchMovies(search);

			if (movies.size() > 0) {
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
			}
			else {
				cout << "No movies found containing this keyword!" << endl;
			}

			break;
		}
		case 3: 
		{
			string temp = "";
			
			cout << "Please enter movie personnel to search for: ";
			getline(cin, search);

			vector<string> movies = db.searchPersonnel(search);

			if (movies.size() > 0) {
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
			}
			else {
				cout << "No movies found containing this personnel!" << endl;
			}

			break;
		}
		case 4: 
		{	
			cout << "How many recommendations would you like? ";
			getline(cin, search);

			vector<string> recommendations = db.findRecommendations();

			for (int i = 0; i < stoi(search); i++) {
				db.displayMovie(recommendations[i], i + 1);
			}

			break;
		}
		case 5:
		{
			cout << "movie graph";

			break;
		}
		}
	}

	return 0;
}