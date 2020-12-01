#ifndef PROGRAM_MANAGER_HEADER
#define PROGRAM_MANAGER_HEADER

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Movie.h"

using namespace std;

class ProgramManager
{
	private:
	//file paths
	static const string moviesPath = "Database/IMDb movies.csv";
	static const string namesPath = "Database/IMDb names.csv";
	static const string principalsPath = "Database/IMDb title_principals.csv";

	//Data Structures
	unordered_map<string, Movie> Movies; //key: IMDb Movie ID, value: Movie instance
	unordered_map<string, string> Personnel; //key: IMDb Personnel ID, value: personnel's name
	unordered_map<string, unordered_set<string>> Movie_to_Personnel; //key: IMDb Movie ID, value: ID of all personnel affiliated with movie 
	unordered_map<string, unordered_set<string>> Personnel_to_Movies; //key: IMDb Personnel ID, value: ID of all movies the person has worked on

	//Constructors
	ProgramManager();

	//functions
	void initialize();
	bool doesMovieExist(const string& movieID) const;
	bool doesPersonnelExist(const string& personnelID) const;
	bool isConnection(const string& movieID, const string& personnelID) const;
	bool addMovie(const string& movieID, const Movie& movie);
	bool addPersonnel(const string& personnelID, const string& name);
	bool addConnection(const string& movieID, const string& personnelID);
};

#endif