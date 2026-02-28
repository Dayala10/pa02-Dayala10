
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include "movies.h" 
using namespace std;

//other helpful functions 
vector<Movie> getMovieP(const vector<Movie>& movieTitles, const string &prefix); //returns a vector of movies that match a prefix. 
void printM(const vector<Movie> &movies); //easy printing! 

//sort alphabetically
vector<Movie> sortTitles(const vector<Movie>& movieTitles);
#endif