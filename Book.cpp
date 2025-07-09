#include "Book.hpp"
#include<iostream>
#include<iomanip>

Book::Book(int id, string title, string author, double price, string bookAddDate, bool isAvailable, string borrowDate){
    this->id = id;
    this->title = title;
    this->author = author;
    this->price = price;
    this->bookAddDate = bookAddDate;
    this->isAvailable = isAvailable;
    this->borrowDate = borrowDate;
}

void Book::displayBook(){
        cout<<"Book ID: "<<id<<" | "<<"Book Title: "<<title<<" | "<<"Author: "<<author<<" | "<<fixed << setprecision(2) <<price<<" | "<<"Available: "<<(isAvailable?"Yes":"Currently Borrowed")<<endl;
}

void Book::changeAvailablity(bool status){
    isAvailable = status;
}

void Book::updateBorrowDate(){
    borrowDate = Utils::getCurrentDate();
}