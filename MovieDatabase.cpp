#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

MovieDatabase::MovieDatabase()
{
    m_called = false;

}

MovieDatabase::~MovieDatabase(){
    for(int i = 0; i < toDelete.size(); i++) delete toDelete[i];
}


bool MovieDatabase::load(const string& filename) {
    if (m_called) {
        // if this function is called already, return false
        return false;
    }

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open " << filename << "!" << endl;
        return false;
    }

    string line;
    // read one line at a time from movie.txt
    while (getline(infile, line)) {
        
        if(line.empty())
            getline(infile, line);
        // parse the line into separate fields.
        string id = line;
        getline(infile, line); // read next line into name...
        string name = line;
        getline(infile, line);
        string year = line;
        getline(infile, line);
        vector<string> directors = split(line);
        getline(infile, line);
        vector<string> actors = split(line);
        getline(infile, line);
        vector<string> genres = split(line);
        float rating;
        infile >> rating;
        infile.ignore(10000, '\n');

        // declare and instantiate a new Movie object with the above fields.
        Movie* currentM = new Movie(id, name, year, directors, actors, genres, rating);
        
        toDelete.push_back(currentM);

        // add the new object to their coresponding data structures.
        id = tolower(id);
        name = tolower(name);
        for (auto d : directors) tmmD.insert(tolower(d), currentM);
        for (auto a : actors) tmmA.insert(tolower(a), currentM);
        for (auto g : genres) tmmG.insert(tolower(g), currentM);
        tmmID.insert(id, currentM);
    }

    // if successfully loaded, m_called becomes true
    m_called = true;
    return true;
}


Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    // duplicate code that I don't know how to solve
    string check;
    for (int x=0; x<id.size(); x++)
            check += std::tolower(id[x]);
    auto it = tmmID.find(check);
    if(!it.is_valid()) return nullptr;
    return it.get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string check;
    for (int x=0; x<director.size(); x++)
            check += std::tolower(director[x]);
    auto it = tmmD.find(check);
    if(!it.is_valid()) return vector<Movie*> ();
    vector<Movie*> result;
    while(it.is_valid()){
        result.push_back(it.get_value());
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string check;
    for (int x=0; x<actor.size(); x++)
            check += std::tolower(actor[x]);
    auto it = tmmA.find(check);
    if(!it.is_valid()) return vector<Movie*> ();
    vector<Movie*> result;
    while(it.is_valid()){
        result.push_back(it.get_value());
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string check;
    for (int x=0; x<genre.size(); x++)
            check += std::tolower(genre[x]);
    auto it = tmmG.find(check);
    if(!it.is_valid()) return vector<Movie*> ();
    vector<Movie*> result;
    while(it.is_valid()){
        result.push_back(it.get_value());
        it.advance();
    }
    return result;
}



vector<string> MovieDatabase::split(string inputString)
{
    vector<string> result;
    string segment;

    for (char c : inputString)
    {
        if (c == ',')
        {
            result.push_back(segment);
            segment.clear();
        }
        else
        {
            segment += c;
        }
    }

    //add the last segment if needed
    if (!segment.empty())
    {
        result.push_back(segment);
    }

    return result;
}

 string MovieDatabase::tolower( string s){
    string lower;
    for (int x=0; x<s.size(); x++)
            lower += std::tolower(s[x]);
    return lower;
}
