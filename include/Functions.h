#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <limits>
#include <string>
#include <cctype>
#include "FileOperations.h"
#include "User.h"

using namespace std;

void addUser(vector<User> &notebook);
void searchUser(const vector<User> &notebook);
void deleteUser(vector<User> &notebook);
void deleteAll(vector<User> &notebook);
void showAll(const vector<User> &notebook);
void sortAll(vector<User> &notebook);
string phoneTypeToString(PhoneType type);

void addUser(vector<User> &notebook)
{
    User user;
    cout << "Enter first name: ";
    cin >> user.firstName;
    cout << "Enter last name: ";
    cin >> user.lastName;
    cout << "Enter email: ";
    cin >> user.email;

    string number;
    PhoneType type;

    do
    {
        cout << "Enter number: ";
        cin >> number;

        bool isValidNumber = true;
        for (char digit : number)
        {
            if (!isdigit(digit))
            {
                isValidNumber = false;
                break;
            }
        }

        if (!isValidNumber)
        {
            cout << "Invalid input for the number. Please enter a valid number.\n";
            continue;
        }

        int category;
        while (true)
        {
            cout << "Enter category (1: Main, 2: Home, 3: Work, 4: Office, 5: Fax): ";
            cin >> category;

            if (cin.fail() || (category < 1 || category > 5))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid category. Please enter a valid category.\n";
            }
            else
            {
                type = static_cast<PhoneType>(category);
                break;
            }
        }

        user.numbers.push_back(make_pair(number, type));

        cout << "Do you want to add another number? (y/n): ";
        char choice;
        cin >> choice;

        if (choice != 'y' && choice != 'Y')
            break;

    } while (true);

    notebook.push_back(user);
    cout << "User added successfully.\n";
}

void searchUser(const vector<User> &notebook)
{
    string search;
    cout << "Enter first name, last name, email, or number to search: ";
    cin >> search;

    cout << "Search results:\n";
    for (size_t i = 0; i < notebook.size(); ++i)
    {
        const User &user = notebook[i];
        if (user.firstName == search || user.lastName == search || user.email == search)
        {
            cout << "First Name: " << user.firstName << "\n";
            cout << "Last Name: " << user.lastName << "\n";
            cout << "Email: " << user.email << "\n";
            cout << "Numbers:\n";
            for (const auto &entry : user.numbers)
            {
                cout << "    " << entry.first << " (Category: " << phoneTypeToString(entry.second) << ")\n";
            }
            cout << "\n";
        }
        else
        {
            for (const auto &entry : user.numbers)
            {
                if (entry.first == search)
                {
                    cout << "First Name: " << user.firstName << "\n";
                    cout << "Last Name: " << user.lastName << "\n";
                    cout << "Email: " << user.email << "\n";
                    cout << "Numbers:\n";
                    for (const auto &entry : user.numbers)
                    {
                        cout << "    " << entry.first << " (Category: " << phoneTypeToString(entry.second) << ")\n";
                    }
                    cout << "\n";
                    break;
                }
            }
        }
    }
}

void deleteUser(vector<User> &notebook)
{
    string searchName;
    cout << "Enter first name or last name to delete: ";
    cin >> searchName;

    vector<size_t> indicesToDelete;
    size_t displayedIndex = 1;

    for (size_t i = 0; i < notebook.size(); ++i)
    {
        const User &user = notebook[i];
        if (user.firstName == searchName || user.lastName == searchName)
        {
            cout << "____________________________\n";
            indicesToDelete.push_back(i);

            cout << "Index " << displayedIndex << ":\n";
            cout << "First Name: " << user.firstName << "\n";
            cout << "Last Name: " << user.lastName << "\n";
            cout << "Email: " << user.email << "\n";
            cout << "Numbers:\n";
            for (const auto &entry : user.numbers)
            {
                cout << "    " << entry.first << " (Category: " << phoneTypeToString(entry.second) << ")\n";
            }
            cout << "____________________________\n";

            displayedIndex++;
        }
    }

    if (indicesToDelete.empty())
    {
        cout << "No user found with the given first or last name.\n";
    }
    else
    {
        int indexToDelete;
        cout << "Enter index to delete (starting from 1): ";
        cin >> indexToDelete;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid index (integer).\n";
        }
        else if (indexToDelete >= 1 && static_cast<size_t>(indexToDelete) <= displayedIndex)
        {
            size_t actualIndex = indicesToDelete[indexToDelete - 1];
            notebook.erase(notebook.begin() + actualIndex);
            cout << "User deleted successfully.\n";
        }
        else
        {
            cout << "Invalid index.\n";
        }
    }
}

void deleteAll(vector<User> &notebook)
{
    cout << "Are you sure you want to delete all users? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        notebook.clear();
        cout << "All users deleted.\n";
    }
    else
    {
        cout << "Deletion canceled.\n";
    }
}

void showAll(const vector<User> &notebook)
{
    cout << "All users:\n";
    for (const User &user : notebook)
    {
        cout << "First Name: " << user.firstName << "\n";
        cout << "Last Name: " << user.lastName << "\n";
        cout << "Email: " << user.email << "\n";
        cout << "Numbers:\n";
        for (const auto &entry : user.numbers)
        {
            cout << "    " << entry.first << " (Category: " << phoneTypeToString(entry.second) << ")\n";
        }
        cout << "____________________________\n";
    }
}

void sortAll(vector<User> &notebook)
{
    for (size_t i = 0; i < notebook.size() - 1; ++i)
    {
        for (size_t j = 0; j < notebook.size() - i - 1; ++j)
        {
            if (notebook[j].firstName + notebook[j].lastName > notebook[j + 1].firstName + notebook[j + 1].lastName)
            {
                swap(notebook[j], notebook[j + 1]);
            }
        }
    }

    cout << "Notebook sorted alphabetically.\n";
}

string phoneTypeToString(PhoneType type)
{
    switch (type)
    {
    case PhoneType::Main:
        return "Main";
    case PhoneType::Home:
        return "Home";
    case PhoneType::Work:
        return "Work";
    case PhoneType::Office:
        return "Office";
    case PhoneType::Fax:
        return "Fax";
    default:
        return "Unknown";
    }
}

#endif
