#include "ProgramManager.h"
#include <fstream>
#include <sstream>

const string ProgramManager::moviesPath = "Database/IMDb movies.csv";
const string ProgramManager::namesPath = "Database/IMDb names.csv";
const string ProgramManager::principalsPath = "Database/IMDb title_principals.csv";

void ProgramManager::initialize()
{
	fstream fileStream(moviesPath);
	string entry;

	while(getline(fileStream, entry))//processes all movies
	{
		/*file format: IMDb movie ID, title, year, genre, description, score
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules, from what I can tell
		*/

		stringstream entryStream(entry);
		string IMDb_ID, title, year, genre, description, scoreString;
		int score;


	}
}