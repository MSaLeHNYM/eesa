#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <vector>
#include "User.h"
#include <fstream>

using namespace std;

void saveAll(const vector<User> &notebook)
{
    ofstream outFile("db.txt");
    if (outFile.is_open())
    {
        for (const User &user : notebook)
        {
            outFile << user.firstName << " " << user.lastName << " " << user.email << "\n";
            for (const auto &entry : user.numbers)
            {
                outFile << entry.first << " " << static_cast<int>(entry.second) << "\n";
            }
            outFile << "---\n";
        }
        outFile.close();
        cout << "All users saved to db.txt.\n";
    }
    else
    {
        cout << "Error opening db.txt for writing.\n";
    }
}

void loadAll(vector<User> &notebook)
{
    ifstream inFile("db.txt");
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            User user;
            inFile >> user.firstName >> user.lastName >> user.email;

            if (user.firstName.empty() && user.lastName.empty() && user.email.empty())
            {
                break;
            }

            string number;
            int category;
            while (true)
            {
                inFile >> number;
                if (number == "---")
                {
                    break;
                }
                inFile >> category;
                user.numbers.push_back(make_pair(number, static_cast<PhoneType>(category)));
            }

            notebook.push_back(user);
        }

        inFile.close();
        cout << "Data loaded from db.txt.\n";
    }
    else
    {
        cout << "No db.txt found or error opening db.txt for reading.\n";
    }
}



#endif 
