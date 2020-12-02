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
	fstream fileStream(moviesPath);
	string entry;

	while(getline(fileStream, entry)) //processes all movies
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
		Movie* m = new Movie(movieData[1], movieData[3], movieData[4], stoi(movieData[2]), stod(movieData[5]));
		this->Movies[movieData[0]] = m;
	}

	cout << "Movies Loaded..." << endl;
}