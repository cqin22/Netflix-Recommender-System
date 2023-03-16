#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    udbPtr = &user_database;
    mdbPtr = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // find movies watched in the past:
    vector<string> moviesWatchedStr;
    User* user = udbPtr->get_user_from_email(user_email);
    if(user != nullptr) moviesWatchedStr = user->get_watch_history();
    else return vector<MovieAndRank>();
    
    vector<MovieAndRank> movieRank;
    unordered_map<Movie*, int> databaseMovies;

    //  For each director d associated with m, each movie in the movie database that has d in its list of directors contributes 20 points to the compatibility score
    for(auto m:moviesWatchedStr){
        Movie* movie = mdbPtr->get_movie_from_id(m);
        vector<string> movieDirectors = movie->get_directors();
        vector<string> movieActors = movie->get_actors();
        vector<string> movieGenres = movie->get_genres();

        
        //retrive all movies from a director
        for(string d:movieDirectors){
            vector<Movie*> movies = mdbPtr->get_movies_with_director(d);
            for(auto mov:movies) databaseMovies[mov] += 20;
        }

        // retrive all movies from an actor
        for(string a:movieActors){
            vector<Movie*> movies = mdbPtr->get_movies_with_actor(a);
            for(auto mov:movies) databaseMovies[mov] += 30;
        }
        
        //Retrive all movies from a genre
        for(string g:movieGenres){
            vector<Movie*> movies = mdbPtr->get_movies_with_genre(g);
            for(auto mov:movies) databaseMovies[mov] += 1;
        }
    }
    
    // turn map into vector of MovieAndRank
    for(auto x: databaseMovies)
       {
           for(auto y:moviesWatchedStr){
               if(x.first->get_id() == y) x.second = -1;
           }

           if(x.second >= 1)
           {
               movieRank.push_back(MovieAndRank(x.first->get_id(), x.second));
           }
       }
    
    sort(movieRank.begin(), movieRank.end(), [this](MovieAndRank& a, MovieAndRank& b){
//        return true;
        if(a.compatibility_score > b.compatibility_score)
            return true;
        if(a.compatibility_score < b.compatibility_score)
            return false;
        
        Movie* a_movie = mdbPtr->get_movie_from_id(a.movie_id);
        Movie* b_movie = mdbPtr->get_movie_from_id(b.movie_id);
        
// HezekF0394@aol.com

        if(a_movie->get_rating() > b_movie->get_rating())
            return true;
        if(a_movie->get_rating() < b_movie->get_rating())
            return false;
        
        if(a_movie->get_title() > b_movie->get_title())
            return false;
        if(a_movie->get_title() < b_movie->get_title())
            return true;
        
        return false;
    });
    

//    int n = movieRank.size();
    

//    for (int gap = n/2; gap > 0; gap /= 2) {
//        for (int i = gap; i < n; i++) {
//            MovieAndRank temp = movieRank[i];
//
//            int j;
//            for (j = i; j >= gap && movieRank[j - gap].compatibility_score < temp.compatibility_score; j -= gap) {
//                if (movieRank[j - gap].compatibility_score == temp.compatibility_score) {
//                    if (mdbPtr->get_movie_from_id(movieRank[j - gap].movie_id)->get_rating() > mdbPtr->get_movie_from_id(temp.movie_id)->get_rating()) {
//                        movieRank[j] = movieRank[j - gap];
//                    } else if (mdbPtr->get_movie_from_id(movieRank[j - gap].movie_id)->get_rating() == mdbPtr->get_movie_from_id(temp.movie_id)->get_rating()) {
//                        if (mdbPtr->get_movie_from_id(movieRank[j - gap].movie_id)->get_title() > mdbPtr->get_movie_from_id(temp.movie_id)->get_title()) {
//                            movieRank[j] = movieRank[j - gap];
//                        } else {break;
//                        }
//                    } else { break;
//                    }
//                } else {
//                    movieRank[j] = movieRank[j - gap];
//                }
//            }
//
//            movieRank[j] = temp;
//        }
//    }
           
    
    // make new movieRank to only return the specified amount
    vector<MovieAndRank> movieRankResult;

    for(int i = 0; i < movie_count; i++){
        movieRankResult.push_back(movieRank[i]);
    }
    
    return movieRankResult;
}
