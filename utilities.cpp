#include "utilities.h"
#include "movies.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


//other helpful functions 
//returns a vector of movies that match a prefix. 
vector<Movie> getMovieP(const vector<Movie>& movieTitles, const string &prefix){
    vector<Movie> mlist;
    for(const auto &m : movieTitles){
        if(m.getTitle().size() >= prefix.size() && m.getTitle().compare(0, prefix.size(),prefix) == 0){
            mlist.push_back(m);
        }
    }

    return mlist;
}

//easy printing! 
void printM(const vector<Movie> &movies){
    // cout << movieName << " has rating " << movieRating << endl;
    for(const auto &m : movies){
        cout << m.getTitle() << ", " << m.getRating() << endl;
    }
} 

//sort alphabetically 
vector<Movie> sortTitles(const vector<Movie>& movieTitles){
    vector<Movie> sorted = movieTitles;
    sort(sorted.begin(), sorted.end(), [](const Movie& a,const Movie&b ){
        return a.getTitle() < b.getTitle();
    });

    return sorted;
}