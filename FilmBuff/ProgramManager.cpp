#include "ProgramManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept> 
#include <iostream>
#include "Timer.cpp"

const string ProgramManager::moviesPath = "../Database/IMDb movies.csv";
const string ProgramManager::namesPath = "../Database/IMDb names.csv";
const string ProgramManager::principalsPath = "../Database/IMDb title_principals.csv";

void ProgramManager::initialize()
{
	Timer t;
	loadMovies();
	loadPersonnel();
	loadPrincipals();
	cout << "Time elapsed: " << t.elapsed() << " seconds\n" << endl;
}

void ProgramManager::loadMovies()
{
	fstream fileStream(moviesPath);
	string entry;

	while(getline(fileStream, entry))//processes all movies
	{
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
			score = stod(columns[5]);
			Movie movie(columns[1], stoi(columns[2]), columns[3], columns[4], score);
			addMovie(columns[0], movie);
		}
		catch(invalid_argument ex)
		{
			cout << "Error" << ex.what() << endl;
			cerr << "Couldn't load movies" << endl;
		}
		catch(exception ex)
		{
			cout << "something went wrong" << endl;
		}
	}
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
		string columns[numOfFields];

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
		catch(exception ex)
		{
			cerr << "Couldn't load personnel";
		}
	}
}

void ProgramManager::loadPrincipals()
{
	fstream fileStream(namesPath);
	string entry;

	while(getline(fileStream, entry))//processes all personnel
	{
		/*file format: IMDb movie ID, IMDb personnel ID
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules
		*/

		const int numOfFields = 2;
		stringstream entryStream(entry);
		string columns[numOfFields];

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
			addConnection(columns[0], columns[1]);
		}
		catch(exception ex)
		{
			cerr << "Couldn't load personnel";
		}
	}
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
	Movie_to_Personnel[movieID].insert(personnelID);
	Personnel_to_Movies[personnelID].insert(movieID);
}

bool ProgramManager::doesMovieExist(const string& movieID) const
{
	return Movies.find(movieID) != Movies.end();
}

bool ProgramManager::doesPersonnelExist(const string& movieID) const
{
	return Personnel.find(movieID) != Personnel.end();
}