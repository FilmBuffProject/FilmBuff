#include "Movie.h"

Movie::Movie() {
	this->title = "";
	this->genre = "";
	this->description = "";
	this->year = 0;
	this->score = 0;
}

Movie::Movie(string _title, string _genre, string _description, int _year, int _score) {
	this->title = _title;
	this->genre = _genre;
	this->description = _description;
	this->year = _year;
	this->score = _score;
}

string Movie::getTitle() {
	return this->title;
}

string Movie::getGenre() {
	return this->genre;
}

string Movie::getDescription() {
	return this->description;
}

int Movie::getYear() {
	return this->year;
}

int Movie::getScore() {
	return this->score;
}