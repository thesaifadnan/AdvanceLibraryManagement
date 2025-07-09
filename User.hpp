#ifndef USER_HPP
#define USER_HPP
#include<string>
#include<vector>
using namespace std;
class User{
    private:
        string firstName;
        string lastName;
        string userName;
        string password;
        bool isAdmin;
        vector<int> booksBorrowed;
        vector<int> borrowHistory;
    public:
        User(string firstName, string lastName, string userName, string password, bool isAdmin);
        void borrowBook(int bookId);
        bool returnBook(int bookId);
        void displayBooksBorrowed();
        void displayUser();
        string getFirstName() const;
        string getLastName() const;
        string getUserName() const;
        string getPassword() const;
        bool isUserAdmin() const;
        vector<int>& getBooksBorrowed();
        vector<int>& getBorrowHistory();

};

#endif