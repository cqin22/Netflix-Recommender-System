#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    bool m_called;
    TreeMultimap<string, Movie*> tmmID;
    TreeMultimap<string, Movie*> tmmD;
    TreeMultimap<string, Movie*> tmmA;
    TreeMultimap<string, Movie*> tmmG;
    vector<string> split(string inputString);
     string tolower( string s) ;
    vector<Movie*> toDelete;
};

#endif // MOVIEDATABASE_INCLUDED
