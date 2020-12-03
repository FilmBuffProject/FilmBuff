#include "ProgramManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
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

	//read preferred personnel
	fileStream.open(personnelPreferencesPath);
	string personnelEntry;

	getline(fileStream, personnelEntry);
	int numOfPersonnel = stoi(personnelEntry);

	for(; numOfPersonnel != 0; --numOfPersonnel)
	{
		string personnelID, appearancesString;
		getline(fileStream, personnelEntry, '\"');//discard first quote
		getline(fileStream, personnelID, ',');//personnelID
		getline(fileStream, appearancesString, '\"');//numOfAppearances and last quote

		personnelPreferences[personnelID] = stoi(appearancesString);
	}

	cout << "Loaded Preferences!" << endl;
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

	fileStream << personnelPreferences.size() << endl;

	if(personnelIter != personnelPreferences.end())
	{
		fileStream << '\"' << (*personnelIter).first << ',' << (*personnelIter).second << '\"';
		++personnelIter;
	}

	for(; personnelIter != personnelPreferences.end(); ++personnelIter)
	{

		fileStream << ",";
		fileStream << '\"' << (*personnelIter).first << ',' << (*personnelIter).second << '\"';
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

vector<string> ProgramManager::searchMovies(const string& movieName) {
	vector<string> results;

	for (auto i = this->Movies.begin(); i != Movies.end(); i++) {
		Movie m = i->second;

		if (i->second.getTitle().find(movieName) != std::string::npos) {
			displayMovie(i->first, results.size() + 1);

			/*cout << (results.size() + 1) << ". " << i->second.getTitle() << " (" << i->second.getYear() << ")" << endl;
			cout << "Genre: " << i->second.getGenre() << endl;
			cout << "Description: " << i->second.getDescription() << endl << endl;*/

			results.push_back(i->first);
		}
	}

	return results;
}

vector<string> ProgramManager::searchPersonnel(const string& personnelName) {
	vector<string> results;
	int count = 1;

	for (auto i = this->Personnel.begin(); i != Personnel.end(); i++) {
		if (personnelName == i->second) {
			for (auto j = Personnel_to_Movies.at(i->first).begin(); j != Personnel_to_Movies.at(i->first).end(); j++) {
				results.push_back(*j);
			}
			
			break;
		}
	}

	for (auto i = results.begin(); i != results.end(); i++) {
		displayMovie(*i, count);

		count++;
	}

	return results;
}

void ProgramManager::addPreferences(const string& movieID) {
	auto inserted = this->moviePreferences.insert(movieID);
	
	if (inserted.second == true) {
		unordered_set<string> m = this->Movie_to_Personnel.at(movieID);

		for (auto i = m.begin(); i != m.end(); i++) {
			this->personnelPreferences[*i] += 1;
		}
	}
}

vector<string> ProgramManager::findRecommendations() const 
{
	/*Rank Equation
		rank(n) = (k0 * total_personnel_weight(n)) + (k1 * IMDb weight(n))
		k0 and k1 are constants used for deciding which of total_personnel_weight and IMDb weight is valued more
	*/
	unordered_map<string, double> recommendations;//IMDb movie ID, rank

	double k0 = 1.0, k1 = 1.0;//k0, k1
	if(personnelPreferences.size() == 0)
	{
		return vector<string>{};
	}

	//fills recommendations map with total_personnel_weight
	for(auto iter = personnelPreferences.begin(); iter != personnelPreferences.end(); ++iter)//uses each personnel to recommend movies
	{
		const unordered_set<string>& recommendedMovies = Personnel_to_Movies.at(iter->first);

		for(auto recommendedIter = recommendedMovies.begin(); recommendedIter != recommendedMovies.end(); ++recommendedIter)
		{
			if(moviePreferences.find(*recommendedIter) == moviePreferences.end())//makes sure movie isn't already in set of preferences
			{
				if(recommendations.find(*recommendedIter) == recommendations.begin())//if first time being recommended
				{
					recommendations[*recommendedIter] = iter->second;//personnel_weight
				}
				else
				{
					recommendations[*recommendedIter] += iter->second;
				}
			}
		}
	}

	//finishes calculating ranks
	for(auto iter = recommendations.begin(); iter != recommendations.end(); ++iter)
	{
		double total_personnel_weight = iter->second;
		double IMDb_weight = Movies.at(iter->first).getScore();
		iter->second = (k0 * total_personnel_weight) + (k1 * IMDb_weight);
	}

	//returns a vector of recommendations sorted by greatest rank first
	vector<string> output;
	for(auto iter = recommendations.begin(); iter != recommendations.end(); ++iter)
	{
		output.push_back(iter->first);
	}

	sort(output.begin(), output.end(), [&](string a, string b) -> bool
		{
			return recommendations[a] > recommendations[b];
		});

	return output;
}

void ProgramManager::displayPreferences() const {
	int count = 1;

	for (auto i = this->moviePreferences.begin(); i != this->moviePreferences.end(); i++) {
		displayMovie(*i, count);

		count++;
	}
}

void ProgramManager::displayMovie(const string& movieID, int count) const {
	cout << count << ". " << this->Movies.at(movieID).getTitle() << " (" << this->Movies.at(movieID).getYear() << ")" << endl;
	cout << "Genre: " << this->Movies.at(movieID).getGenre() << endl;
	cout << "Description: " << this->Movies.at(movieID).getDescription() << endl << endl;
}