#ifndef BOOK_HPP
#define BOOK_HPP

#include "Utils.hpp"
#include<string>
using namespace std;
class Book{
    public:
        int id;
        string title;
        string author;
        double price;
        string bookAddDate;
        string borrowDate;
        bool isAvailable;

        Book(int id, string title, string author, double price, string bookAddDate, bool isAvailable, string borrowDate);

        void displayBook();
        void changeAvailablity(bool);
        void updateBorrowDate();

};

#endif