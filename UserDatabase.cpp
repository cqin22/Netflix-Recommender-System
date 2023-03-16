#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called = false;
}

UserDatabase::~UserDatabase(){
    for(int i = 0; i < toDelete.size(); i++) delete toDelete[i];
}


bool UserDatabase::load(const string& filename)
{
    if(m_called) return false;
    //    This method must load a user database from the specified input file, e.g., users.txt. If it has not
    //    yet been called before for this UserDatabase object and it is successful in loading all of the user
    //    records in the file, it must return true. Otherwise, it must return false. (If it returns false, the state
    //    of the object may or may not have been changed.) The method must load the data into data
    //    structures that enable you to meet the big-O requirements specified in the section above.

    
    ifstream infile(filename);
    if ( ! infile )                // Did opening the file fail?
    {
        cerr << "Error: Cannot open users.txt!" << endl;
        return false;
    }
    
    string line;
    // read one line at a time from movie.txt
    while (getline(infile, line)) {
        
        if(line.empty())
            getline(infile, line);
        
        string name = line;
        getline(infile, line); // read next line into name...
        string email = line;
        getline(infile, line);
        vector<string> history;
        
        //get movies watched
        for(int count = stoi(line); count != 0; count--){
            getline(infile, line);
            history.push_back(line);
        }
        User* u = new User(name, email, history);
        tmm.insert(email, u);
        toDelete.push_back(u);
    }
    
    m_called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    auto it = tmm.find(email);
    if(!it.is_valid()) return nullptr;
    return it.get_value();
}


