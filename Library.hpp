#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include "Book.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include "BorrowRecord.hpp"
#include<vector>

class Library{
    private:
        vector<Book> books;
        vector<BorrowRecord> allBorrowHistory;
    public:

        //Book's Functions
        void listBooks();
        int getNewBookId();
        void addBook();
        void removeBook();
        void searchBook();
        string toString(Book &book);
        void saveBooksToFile(string fileName);
        void loadBooksFromFile(string fileName);
        Book* getBookById(int);

        //User's Functions
        void borrowUserBook(User *user);
        void returnUserBook(User *user);
        void allBorrowedBooks(User *user);
        void userBorrowHistory(User *user);
        string toString(User &user);
        string toString(BorrowRecord userBookPair);
        void updateUserBorrowHistory(User *user);
        void saveBooksBorrowedToFile(string fileName);
        void loadBooksBorrowedFromFile(string fileName);
        void listOverDues();
        
};

#endif