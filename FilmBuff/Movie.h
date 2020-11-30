#pragma once
#include <string>
using namespace std;

class Movie
{
private:
	string title;
	string genre;
	string description;
	int year;
	int score;

public:
	Movie();
	Movie(string _title, string _genre, string _description, int _year, int _score);
	string getTitle();
	string getGenre();
	string getDescription();
	int getYear();
	int getScore();
};

