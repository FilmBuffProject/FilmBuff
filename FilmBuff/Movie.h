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
	double score;

public:
	Movie();
	Movie(string _title, int _year, string _genre, string _description, double _score);
	string getTitle() const;
	string getGenre() const;
	string getDescription() const;
	int getYear() const;
	double getScore() const;
};