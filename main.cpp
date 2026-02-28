// Winter'24
// Instructor: Diba Mirza
// Student name: Daisy Ayala and Emily Santana-Mendoza
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> movieList;
 
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movieList.push_back({movieName, movieRating});
            
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names

            vector<Movie> sorted = sortTitles(movieList);
            printM(sorted);
            
            
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for(const string& p : prefixes){
        vector<Movie> matches;
        for(const Movie& m : movieList){
            if(m.hasPrefix(p)){
                matches.push_back(m);
            }
        }
        if(matches.empty()){
            cout << "No movies found with prefix "<< p << endl;
        }
    }


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for(const string& r : prefixes){
        vector<Movie> matches = getMovieP(movieList, r); //data is added

        if(matches.empty()){
            cout << "No movies found with prefix "<< r << endl;
        }
        else{
            //sorting matches by rating and alphebitically if rating is the same
            sort(matches.begin(), matches.end(), Movie::byRating);
//printing matches
            for(const Movie &m :matches){
                cout << m.getTitle() << ", " << std::fixed << std::setprecision(1) << m.getRating() << endl;
            }

            const Movie& bestRated = matches[0];//highest rated movie
            cout << "Best movie with prefix " << r << " is: " << bestRated.getTitle() << " with rating " << std::fixed << std::setprecision(1) << bestRated.getRating() << endl;
        }
    }
    return 0;

}

/* Add your run time analysis for part 3 of the assignment here as commented block
PART 3A:

Assume that:
-there are n movies in the dataset.
-there are m prefixes specified in a given run of your program.
-at most k movies begin with each prefix.
-l is the maximum number of characters in a movie name

*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}