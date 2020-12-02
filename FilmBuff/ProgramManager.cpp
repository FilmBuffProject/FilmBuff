#include "ProgramManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Timer.cpp"

const string ProgramManager::moviesPath = "../Database/IMDb movies.csv";
const string ProgramManager::namesPath = "../Database/IMDb names.csv";
const string ProgramManager::principalsPath = "../Database/IMDb title_principals.csv";
const string ProgramManager::moviePreferencesPath = "../Database/preferredMovies";
const string ProgramManager::personnelPreferencesPath = "../Database/preferredPersonnel";

ProgramManager::ProgramManager() 
{
}

void ProgramManager::initialize()
{
	cout << "Initializing..." << endl;
	Timer t;
	loadMovies();
	loadPersonnel();
	loadPrincipals();
	loadPreferred();
	cout << "Time elapsed: " << t.elapsed() << " seconds\n" << endl;
}

void ProgramManager::loadMovies()
{
	fstream fileStream(moviesPath);
	string entry;

	while (getline(fileStream, entry))//processes all movies
	{
		/*file format: IMDb movie ID, title, year, genre, description, score
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules, from what I can tell
		*/

		const int numOfFields = 6;
		stringstream entryStream(entry);
		string columns[numOfFields]; //IMDb_ID, title, year, genre, description, scoreString;
		double score;

		//fill columns array with field data
		for (int i = 0; i < numOfFields; ++i)
		{
			if (entryStream.peek() != '\"')//field isn't quoted
			{
				if (i != numOfFields - 1)//not last field
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

				while (entryStream.get(temp))
				{
					if (temp == '\"')//quote can signify the start of an actual quote or the end of field
					{
						entryStream.get(temp);

						if (temp == '\"')//actual quote
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
		catch (invalid_argument ex)
		{
			cout << "Error" << ex.what() << endl;
			cerr << "Couldn't Load Movies." << endl;
		}
		catch (exception ex)
		{
			cout << "Something went wrong." << endl;
		}
	}

	cout << "Loaded Movies!" << endl;
}

void ProgramManager::loadPersonnel()
{
	fstream fileStream(namesPath);
	string entry;

	while (getline(fileStream, entry))//processes all personnel
	{
		/*file format: IMDb personnel ID, name
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules, from what I can tell
		*/

		const int numOfFields = 2;
		stringstream entryStream(entry);
		string columns[numOfFields];

		//fill columns array with field data
		for (int i = 0; i < numOfFields; ++i)
		{
			if (entryStream.peek() != '\"')//field isn't quoted
			{
				if (i != numOfFields - 1)//not last field
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

				while (entryStream.get(temp))
				{
					if (temp == '\"')//quote can signify the start of an actual quote or the end of field
					{
						entryStream.get(temp);

						if (temp == '\"')//actual quote
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
		catch (exception ex)
		{
			cerr << "Couldn't Load Personnel.";
		}
	}

	cout << "Loaded Personnel!" << endl;
}

void ProgramManager::loadPrincipals()
{
	fstream fileStream(principalsPath);
	string entry;

	while (getline(fileStream, entry))//processes all personnel
	{
		/*file format: IMDb movie ID, IMDb personnel ID
		The CSV files follows RFC 4180 standard, https://en.wikipedia.org/wiki/Comma-separated_values#Basic_rules
		*/

		const int numOfFields = 2;
		stringstream entryStream(entry);
		string columns[numOfFields];

		//fill columns array with field data
		for (int i = 0; i < numOfFields; ++i)
		{
			if (entryStream.peek() != '\"')//field isn't quoted
			{
				if (i != numOfFields - 1)//not last field
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

				while (entryStream.get(temp))
				{
					if (temp == '\"')//quote can signify the start of an actual quote or the end of field
					{
						entryStream.get(temp);

						if (temp == '\"')//actual quote
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
		catch (exception ex)
		{
			cerr << "Couldn't Load Connections.";
		}
	}

	cout << "Loaded Connections!" << endl;
}

void ProgramManager::loadPreferred()
{
	//read preferred movies
	fstream fileStream(moviePreferencesPath, ios_base::in);

	string movieID;
	
	while(getline(fileStream, movieID, ','))
	{
		moviePreferences.insert(movieID);
	}

	fileStream.close();

	//write preferred personnel
	fstream.open(personnelPreferencesPath);
	string personnelEntry;

	getline(fstream, personnelEntry);
	int numOfPersonnel = stoi(personnelEntry);

	for(; numOfPersonnel != 0; --numOfPersonnel)
	{
		string personnelID, appearancesString;
		getline(fStream, personnelEntry, '\"');//discard first quote
		getline(fstream, personnelID, ',');//personnelID
		getline(fstream, appearancesString, '\"');//numOfAppearances and last quote

		personnelPreferences[personnelID] = stoi[appearancesString];
	}
}

void ProgramManager::writePreferred()
{
	//write preferred movies
	fstream fileStream(moviePreferencesPath, ios_base::out | ios_base::trunc);
	auto movieIter = moviePreferences.begin();

	if(movieIter != moviePreferences.end())
	{
		fileStream << *movieIter;
		++movieIter;
	}

	for(; movieIter != moviePreferences.end(); ++movieIter)
	{
		
		fileStream << "," << *movieIter;
	}

	fileStream.close();

	//write preferred personnel
	fileStream.open(personnelPreferencesPath);
	auto personnelIter = personnelPreferences.begin();

	fileStream << personnelPreferences.size << endl;

	if(personnelIter != moviePreferences.end())
	{
		fileStream << '\"' << (*personnelIter).first() << ',' << (*personnelIter).second() << '\"';
		++personnelIter;
	}

	for(; personnelIter != moviePreferences.end(); ++personnelIter)
	{

		fileStream << ",";
		fileStream << '\"' << (*personnelIter).first() << ',' << (*personnelIter).second() << '\"';
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

unordered_set<string> ProgramManager::searchMovies(const string& movieName) {
	unordered_set<string> results;

	for (auto i = this->Movies.begin(); i != Movies.end(); i++) {
		Movie m = i->second;

		if (i->second.getTitle().find(movieName) != std::string::npos) {
			cout << (results.size() + 1) << ". " << i->second.getTitle() << " (" << i->second.getYear() << ")" << endl;
			cout << "Genre: " << i->second.getGenre() << endl;
			cout << "Description: " << i->second.getDescription() << endl << endl;

			results.insert(i->first);
		}
	}

	return results;
}

unordered_set<string> ProgramManager::searchPersonnel(const string& personnelName) {
	unordered_set<string> results;
	int count = 1;

	for (auto i = this->Personnel.begin(); i != Personnel.end(); i++) {
		if (personnelName == i->second) {
			results = Personnel_to_Movies.at(i->first);
			break;
		}
	}

	for (auto i = results.begin(); i != results.end(); i++) {
		cout << count << ". " << this->Movies.at(*i).getTitle() << " (" << this->Movies.at(*i).getYear() << ")" << endl;
		cout << "Genre: " << this->Movies.at(*i).getGenre() << endl;
		cout << "Description: " << this->Movies.at(*i).getDescription() << endl << endl;

		count++;
	}

	return results;
}