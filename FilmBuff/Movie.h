#pragma once
#include <string>
using namespace std;

class Movie
{
private:
	string title;
	string genre;
	string description;
	string year;
	double score;

public:
	Movie();
	Movie(string _title, string _genre, string _description, string _year, double _score);
	string getTitle();
	string getGenre();
	string getDescription();
	string getYear();
	double getScore();
};

