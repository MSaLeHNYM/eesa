#include <iostream>
#include <cstdlib>
#include "../include/User.h"
#include "../include/Functions.h"
#include "../include/FileOperations.h"

using namespace std; // Add this line

int main()
{
    vector<User> notebook;

    loadAll(notebook);

    while (true)
    {
        cout << "\nNotebook App Options:\n"
             << "1. Add User\n"
             << "2. Search User\n"
             << "3. Delete User\n"
             << "4. Delete All Users\n"
             << "5. Show All Users\n"
             << "6. Sort All Users Alphabetically\n"
             << "7. Save All To DB\n"
             << "8. Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;
        system("clear");
        switch (choice)
        {
        case 1:
            addUser(notebook);
            break;
        case 2:
            searchUser(notebook);
            break;
        case 3:
            deleteUser(notebook);
            break;
        case 4:
            deleteAll(notebook);
            break;
        case 5:
            showAll(notebook);
            break;
        case 6:
            sortAll(notebook);
            break;
        case 7:
            // Save all users to db.txt
            saveAll(notebook);
            cout << "All Data Saved!\n";
            break;
        case 8:
            // Save all users to db.txt before exiting
            saveAll(notebook);
            cout << "Exiting the notebook app.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


