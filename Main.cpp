#include <iostream>
#include "Library.hpp"
#include "UserManager.hpp"
using namespace std;

int main() {
    Library library;
    UserManager userManager;

    library.loadBooksFromFile("data/books.txt");
    library.loadBooksBorrowedFromFile("data/borrowHistory.txt");
    userManager.loadUsersFromFile("data/users.txt");

    cout << "📚 Welcome to the Library Management System\n";

    bool loggedIn = false;
    int choice;
    while(!loggedIn){
        while (!loggedIn) {
            cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
            cin >> choice; cin.ignore();
            switch (choice) {
                case 1:
                    loggedIn = userManager.loginUser();
                    if(loggedIn){
                        cout<<"Login Successfull"<<endl;
                    }else{
                        cout<<"Login Failed! Please Check your Credentials and Try Aagin"<<endl;
                    }
                    break;
                case 2:
                    loggedIn = userManager.registerUser();
                    break;
                case 3:
                    library.saveBooksToFile("data/books.txt");
                    library.saveBooksBorrowedToFile("data/borrowHistory.txt");
                    userManager.saveUsersToFile("data/users.txt");
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }

        User* user = userManager.getCurrentUser();
        bool isAdmin = userManager.isAdmin();
        library.updateUserBorrowHistory(user);

        while (loggedIn) {
            cout << "\n====== Main Menu ======\n";
            if (isAdmin) {
                cout << "1. Add Book\n2. Remove Book\n3. List Books\n4. Search Book by Title/Auhtor\n5. Add User\n6. Remove User\n";
                cout << "7. List Users\n8. List OverDue Books\n9. Logout\n10. Save & Exit\nChoice: ";
            } else {
                cout << "1. List Books\n2. Borrow Book\n3. Return Book\n4. Search Book by Title/Author\n";
                cout << "5. My Borrowed Books\n6. Borrow History\n7. Logout\n8. Save & Exit\nChoice: ";
            }
            cin >> choice; cin.ignore();

            if (isAdmin) {
                switch (choice) {
                    case 1: library.addBook(); break;
                    case 2: library.removeBook(); break;
                    case 3: library.listBooks(); break;
                    case 4: library.searchBook(); break;
                    case 5: userManager.addUser(); break;
                    case 6: userManager.removeUser(); break;
                    case 7: userManager.listAllUsers(); break;
                    case 8: library.listOverDues(); break;
                    case 9: userManager.logoutUser(); loggedIn = false; break;
                    case 10:
                        userManager.logoutUser(); loggedIn = false;
                        library.saveBooksToFile("data/books.txt");
                        library.saveBooksBorrowedToFile("data/borrowHistory.txt");
                        userManager.saveUsersToFile("data/users.txt");
                        cout << "Data saved. Exiting...\n";
                        return 0;
                    default: cout << "Invalid Choice! Please Try Again!\n";
                }
            } else {
                switch (choice) {
                    case 1: library.listBooks(); break;
                    case 2: library.borrowUserBook(user); break;
                    case 3: library.returnUserBook(user); break;
                    case 4: library.searchBook(); break;
                    case 5: library.allBorrowedBooks(user); break;
                    case 6: library.userBorrowHistory(user); break;
                    case 7: userManager.logoutUser(); loggedIn = false; break;
                    case 8:
                        userManager.logoutUser(); loggedIn = false;
                        library.saveBooksToFile("data/books.txt");
                        library.saveBooksBorrowedToFile("data/borrowHistory.txt");
                        userManager.saveUsersToFile("data/users.txt");
                        cout << "Data saved. Exiting...\n";
                        return 0;
                    default: cout << "Invalid Choice! Please Try Again!\n";
                }
            }
        }
    }

    return 0;
}
