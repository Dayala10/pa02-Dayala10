#include "movies.h"
#include <algorithm>
using namespace std;

//Comparison helpers and printing 
//helps check if the movie starts with prefix
bool Movie::hasPrefix(const string& prefix) const{
    if (prefix.size() > title.size()){
        return false;
    } 

    string s = title.substr(0,prefix.size());

    transform(s.begin(), s.end(), s.begin(), ::tolower); //lowercasing 
    string p = prefix;
    transform(p.begin(), p.end(), p.begin(), ::tolower);

    return s == p;
} 


//sorts list in descending rating order and alphabetical if tied. 
bool Movie::byRating(const Movie& a, const Movie& b){
    if(a.getRating() == b.getRating()){
        return a.getTitle() < b.getTitle();
    }
    return a.getRating() > b.getRating();
} 

