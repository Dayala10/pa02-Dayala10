#ifndef MOVIES_H
#define MOVIES_H


#include <string>
#include <vector>
using namespace std;


class Movie {
private:


    string title;
    double rating;


    //now helpful functions


public:
    //constructor
    Movie(const string& t, double r): title(t),rating(r){}


    //helps get values
    string getTitle() const {return title;}
    double getRating() const {return rating;}

    //Comparison helpers and printing 
    bool hasPrefix(const string& prefix) const; //helps check if the movie starts with prefix
    static bool byRating(const Movie& a, const Movie& b); //sorts list in descending rating order and alphabetical if tied. 
};


#endif