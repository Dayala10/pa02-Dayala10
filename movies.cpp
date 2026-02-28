#include "movies.h"
using namespace std;

//Comparison helpers and printing 
//helps check if the movie starts with prefix
bool Movie::hasPrefix(const string& prefix) const{
    bool isTrue = false;
    if(prefix.size() > title.size()){
        return false;
    }

    isTrue = title.compare(0,prefix.size(), prefix) == 0;
    return isTrue;
} 


//sorts list in descending rating order and alphabetical if tied. 
bool Movie::byRating(const Movie& a, const Movie& b){
    if(a.getRating() == b.getRating()){
        return a.getTitle() < b.getTitle();
    }
    return a.getRating() > b.getRating();
} 

