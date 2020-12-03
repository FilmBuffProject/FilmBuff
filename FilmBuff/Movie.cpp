#include "Movie.h"

Movie::Movie() {
	this->title = "";
	this->genre = "";
	this->description = "";
	this->year = 0;
	this->score = 0;
}

Movie::Movie(string _title, int _year, string _genre, string _description, double _score) {
	this->title = _title;
	this->genre = _genre;
	this->description = _description;
	this->year = _year;
	this->score = _score;
}

string Movie::getTitle() const {
	return this->title;
}

string Movie::getGenre() const {
	return this->genre;
}

string Movie::getDescription() const {
	return this->description;
}

int Movie::getYear() const {
	return this->year;
}

double Movie::getScore() const {
	return this->score;
}