#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std; 

enum PhoneType
{
    Main = 1,
    Home,
    Work,
    Office,
    Fax
};

struct User
{
    string firstName;
    string lastName;
    string email;
    vector<pair<string, PhoneType>> numbers;
};

#endif 
