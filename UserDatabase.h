#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    // DESTRUCTOR??

    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;


  private:
    bool m_called;
    TreeMultimap<string, User*> tmm;
    vector<User*> toDelete;
};

#endif // USERDATABASE_INCLUDED
