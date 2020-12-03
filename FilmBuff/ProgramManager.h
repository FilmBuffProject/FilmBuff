#ifndef PROGRAM_MANAGER_HEADER
#define PROGRAM_MANAGER_HEADER

#include <unordered_map>
#include <set>
#include <string>
#include "Movie.h"
#include "movieGraph.h"

using namespace std;

class ProgramManager
{
private:
	//file paths
	static const string moviesPath;
	static const string namesPath;
	static const string principalsPath;
	static const string moviePreferencesPath;
	static const string personnelPreferencesPath;

	//Data Structures
	unordered_map<string, Movie> Movies; //key: IMDb Movie ID, value: Movie instance
	unordered_map<string, string> Personnel; //key: IMDb Personnel ID, value: personnel's name
	unordered_map<string, set<string>> Movie_to_Personnel; //key: IMDb Movie ID, value: ID of all personnel affiliated with movie 
	unordered_map<string, set<string>> Personnel_to_Movies; //key: IMDb Personnel ID, value: ID of all movies the person has worked on
	set<string> moviePreferences;
	unordered_map<string, int> personnelPreferences;//key:IMDb personnel ID, value: number Of times actor appears across multiple movies
	movieGraph mGraph;

public:
	//Constructors
	ProgramManager();

	//functions
	void initialize();
	void loadMovies();
	void loadPersonnel();
	void loadPrincipals();
	void loadPreferred();
	void writePreferred();
	vector<string> searchMovies(const string& movieName);
	vector<string> searchPersonnel(const string& personnelName);
	bool doesMovieExist(const string& movieID) const;
	bool doesPersonnelExist(const string& personnelID) const;
	void addMovie(const string& movieID, const Movie& movie);
	void addPersonnel(const string& personnelID, const string& name);
	void addConnection(const string& movieID, const string& personnelID);
	void addPreferences(const string& movieID);
	vector<string> findRecommendations(double k0, double k1) const;
	void displayPreferences() const;
	void displayMovie(const string& movieID, int count) const;
};

#endif