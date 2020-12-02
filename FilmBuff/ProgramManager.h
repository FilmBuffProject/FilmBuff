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
	static const string moviesPath;
	static const string namesPath;
	static const string principalsPath;

	//Data Structures
	unordered_map<string, Movie> Movies; //key: IMDb Movie ID, value: Movie instance
	unordered_map<string, string> Personnel; //key: IMDb Personnel ID, value: personnel's name
	unordered_map<string, unordered_set<string>> Movie_to_Personnel; //key: IMDb Movie ID, value: ID of all personnel affiliated with movie 
	unordered_map<string, unordered_set<string>> Personnel_to_Movies; //key: IMDb Personnel ID, value: ID of all movies the person has worked on

	public:
	//Constructors

	//functions
	void initialize();
	void loadMovies();
	void loadPersonnel();
	void loadPrincipals();
	bool doesMovieExist(const string& movieID) const;
	bool doesPersonnelExist(const string& personnelID) const;
	bool isConnection(const string& movieID, const string& personnelID) const;
	void addMovie(const string& movieID, const Movie& movie);
	void addPersonnel(const string& personnelID, const string& name);
	void addConnection(const string& movieID, const string& personnelID);
};

#endif