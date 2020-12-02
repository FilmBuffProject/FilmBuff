#include "ProgramManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept> 
#include <iostream>

const string ProgramManager::moviesPath = "../Database/IMDb movies.csv";
const string ProgramManager::namesPath = "../Database/IMDb names.csv";
const string ProgramManager::principalsPath = "../Database/IMDb title_principals.csv";

void ProgramManager::initialize()
{
	loadMovies();
	//loadPersonnel();
	//loadPrincipals();
}

void ProgramManager::loadMovies()
{
	fstream fileStream(moviesPath);
	string entry;

	int numOfMovies = 1;
	while(getline(fileStream, entry))//processes all movies
	{
		++numOfMovies;
		/*file format: IMDb movie ID, title, year, genre, description, score
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules, from what I can tell
		*/

		const int numOfFields = 6;
		stringstream entryStream(entry);
		string columns[numOfFields]; //IMDb_ID, title, year, genre, description, scoreString;
		double score;

		//fill columns array with field data
		for(int i = 0; i < numOfFields; ++i)
		{
			if(entryStream.peek() != '\"')//field isn't quoted
			{
				if(i != numOfFields - 1)//not last field
				{
					getline(entryStream, columns[i], ',');
				}
				else
				{
					getline(entryStream, columns[i]);
				}
			}
			else//field is quoted
			{
				entryStream.get();//discard first quote
				char temp;

				while(entryStream.get(temp))
				{
					if(temp == '\"')//quote can signify the start of an actual quote or the end of field
					{
						entryStream.get(temp);

						if(temp == '\"')//actual quote
						{
							columns[i] += '\"';
						}
						else//end of field
						{
							break;
						}
					}
					else//normal character to be added
					{
						columns[i] += temp;
					}
				}
			}
		}

		try
		{
			score = stod(columns[numOfFields - 1]);
			Movie movie(columns[1], columns[2], columns[3], columns[4], score);
			addMovie(columns[0], movie);
		}
		catch(invalid_argument exception)
		{
			cout << "bad news";
			cerr << "Couldn't load movies";
		}
	}

	cout << "finsihed" << numOfMovies;
}

void ProgramManager::loadPersonnel()
{
	fstream fileStream(namesPath);
	string entry;

	while(getline(fileStream, entry))//processes all personnel
	{
		/*file format: IMDb personnel ID, name
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules, from what I can tell
		*/

		const int numOfFields = 2;
		stringstream entryStream(entry);
		string columns[numOfFields]; //IMDb_ID, title, year, genre, description, scoreString;

		//fill columns array with field data
		for(int i = 0; i < numOfFields; ++i)
		{
			if(entryStream.peek() != '\"')//field isn't quoted
			{
				if(i != numOfFields - 1)//not last field
				{
					getline(entryStream, columns[i], ',');
				}
				else
				{
					getline(entryStream, columns[i]);
				}
			}
			else//field is quoted
			{
				entryStream.get();//discard first quote
				char temp;

				while(entryStream.get(temp))
				{
					if(temp == '\"')//quote can signify the start of an actual quote or the end of field
					{
						entryStream.get(temp);

						if(temp == '\"')//actual quote
						{
							columns[i] += '\"';
						}
						else//end of field
						{
							break;
						}
					}
					else//normal character to be added
					{
						columns[i] += temp;
					}
				}
			}
		}

		try
		{
			addPersonnel(columns[0], columns[1]);
		}
		catch(invalid_argument exception)
		{
			cerr << "Couldn't load personnel";
		}
	}
}

void ProgramManager::loadPrincipals()
{
}

void ProgramManager::addMovie(const string& movieID, const Movie& movie)
{
	Movies[movieID] = movie;
}

void ProgramManager::addPersonnel(const string& personnelID, const string& name)
{
	Personnel[personnelID] = name;
}

void ProgramManager::addConnection(const string& movieID, const string& personnelID)
{

}