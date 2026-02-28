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


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.

    vector<string> bestMLines; //our printed string! can't be printed right away

    for(const string& r : prefixes){
        vector<Movie> matches = getMovieP(movieList, r); //data is added

        if(matches.empty()){
            cout << "No movies found with prefix " << r << endl;
            continue;
        }
        //sorting matches by rating and alphebitically if rating is the same
        sort(matches.begin(), matches.end(), Movie::byRating);
//printing matches
        for(const Movie &m :matches){
            cout << m.getTitle() << ", " << std::fixed << std::setprecision(1) << m.getRating() << endl;
        }

        const Movie& bestRated = matches[0];//highest rated movie

        //prints after
        stringstream ss;
        ss << "Best movie with prefix " << r << " is: " << bestRated.getTitle() << " with rating " << fixed << setprecision(1) << bestRated.getRating();

        bestMLines.push_back(ss.str());

    }
    //prints neat lists
    for(const string& line : bestMLines){
        cout << line << endl;
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

-Reading the movies took O(n*l) because there are n lines and operations done on strings take up to l time
-part 1 sorting took: O(n*log n*l) because of sort and comparison of titles that took O(l)
-For m prefixes: 
    prefix matching took O(m*n*l) per prefix 
    when sorting the matches alphabet order and best rate order we got: O(m* k log k) 
-part 2 Time complexity-> O(m*(n*l+k log k))

worse case : O(n* l+ log n * l + m * n *l +(m*k *log k))

PART 3b:
Space complexity Analysis:

 Parameters: 
 n = total number of movies 
 m = total number of prefixes 
 k = Maximum length of a prefix 
 l = Maximum length of a movie title 
For every prefix, a 'matches' vector is created to store movies whose title starts with the prefix. 
For the worst case, all the n movies that ‘match’ a prefix will use O(n) space. 
Sorting these ‘matches’ uses O(log n) space 
There can only exist one ‘matches’ vector at a time, so the space won't multiply by m 
The prefix and title length of k and l do not add extra space because we pass by reference the strings already stored in movielist 
Worst-case: extra space: O(n)
 Final Big-O space complexity: O(n)



PART 3c: 

We designed the algorithm primarily for low space complexity.
We used a simple vector to store all the movies and created a temporary
vector called 'matches' to store movies that match each prefix.

Our achieved target space complexity was O(n). The 'matches'
vector is reused for each prefix and does not multiply by m. At most,
one additional vector of size n exists at any time.

The time complexity was not optimized. For each prefix, the algorithm
scans all n movies, resulting in O(nm) time before sorting.

Achieving lower time complexity would have been harder than achieving
low space complexity. To improve time complexity, we would have needed a more complex data structure such as a trie or a BST,
which in turn would increase space complexity.

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