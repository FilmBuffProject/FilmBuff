#include "ProgramManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

const string ProgramManager::moviesPath = "../Database/IMDb movies.csv";
const string ProgramManager::namesPath = "../Database/IMDb names.csv";
const string ProgramManager::principalsPath = "../Database/IMDb title_principals.csv";

ProgramManager::ProgramManager() {

}

void ProgramManager::initialize()
{
	fstream movieStream(moviesPath);
	fstream nameStream(namesPath);
	fstream principalStream(principalsPath);
	string entry;

	cout << "Initializing..." << endl;

	//Processes movie database and adds to map
	while(getline(movieStream, entry))
	{
		vector<string> movieData;
		bool inQuotes = false;
		bool doubleQuotes = false;
		string tempString = "";
		
		for (int i = 0; i < entry.length(); i++) {
			if (inQuotes == false && entry[i] == '"') {
				inQuotes = true;
				continue;
			}
			else if (inQuotes == true && entry[i] == '"') {
				if (doubleQuotes == true) {
					tempString += '"';
					doubleQuotes = false;
					continue;
				}
				
				if (entry[i + 1] == '"') {
					doubleQuotes = true;
					continue;
				}
				
				movieData.push_back(tempString);
				tempString = "";
				inQuotes = false;
				i++;
				continue;
			} else if (inQuotes == false && entry[i] == ',') {
				movieData.push_back(tempString);
				tempString = "";
				continue;
			}

			tempString += entry[i];
		}

		movieData.push_back(tempString);
		Movie* m = new Movie(movieData[1], movieData[3], movieData[4], stoi(movieData[2]), stof(movieData[5]));
		this->Movies[movieData[0]] = m;
	}

	cout << "Movies Loaded!" << endl;

	//Processes personnel database and adds to map
	while (getline(nameStream, entry)) {
		vector<string> nameData;
		bool inQuotes = false;
		bool doubleQuotes = false;
		string tempString = "";

		for (int i = 0; i < entry.length(); i++) {
			if (inQuotes == false && entry[i] == '"') {
				inQuotes = true;
				continue;
			}
			else if (inQuotes == true && entry[i] == '"') {
				if (doubleQuotes == true) {
					tempString += '"';
					doubleQuotes = false;
					continue;
				}

				if (entry[i + 1] == '"') {
					doubleQuotes = true;
					continue;
				}

				nameData.push_back(tempString);
				tempString = "";
				inQuotes = false;
				i++;
				continue;
			}
			else if (inQuotes == false && entry[i] == ',') {
				nameData.push_back(tempString);
				tempString = "";
				continue;
			}

			tempString += entry[i];
		}

		nameData.push_back(tempString);
		this->Personnel[nameData[0]] = nameData[0];
	}

	cout << "Personnel Loaded!" << endl;

	//Processes principals database and adds to both maps
	while (getline(principalStream, entry)) {
		vector<string> principalData;
		bool inQuotes = false;
		bool doubleQuotes = false;
		string tempString = "";

		for (int i = 0; i < entry.length(); i++) {
			if (inQuotes == false && entry[i] == '"') {
				inQuotes = true;
				continue;
			}
			else if (inQuotes == true && entry[i] == '"') {
				if (doubleQuotes == true) {
					tempString += '"';
					doubleQuotes = false;
					continue;
				}

				if (entry[i + 1] == '"') {
					doubleQuotes = true;
					continue;
				}

				principalData.push_back(tempString);
				tempString = "";
				inQuotes = false;
				i++;
				continue;
			}
			else if (inQuotes == false && entry[i] == ',') {
				principalData.push_back(tempString);
				tempString = "";
				continue;
			}

			tempString += entry[i];
		}

		principalData.push_back(tempString);
		this->Movie_to_Personnel[principalData[0]].insert(principalData[1]);
		this->Personnel_to_Movies[principalData[1]].insert(principalData[0]);
	}

	cout << "Connections Loaded!" << endl;
}