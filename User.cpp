#include "User.hpp"
#include<iostream>

User::User(string firstName, string lastName, string userName, string password, bool isAdmin){
    this->firstName = firstName;
    this->lastName = lastName;
    this->userName = userName;
    this->password = password;
    this->isAdmin = isAdmin;
}

void User::borrowBook(int bookId){
    booksBorrowed.push_back(bookId);
    borrowHistory.push_back(bookId);
    cout<<"Book Borrowed Successfully"<<endl;
}

bool User::returnBook(int bookId){

    auto it = find(booksBorrowed.begin(), booksBorrowed.end(), bookId);
    if(it != booksBorrowed.end()){
        booksBorrowed.erase(it);
        return true;
    }else{
        return false;
    }
}

void User::displayUser(){
    cout<<"User's First Name: "<<firstName<<" | "<<"User's Last Name: "<<lastName<<" | "<<"Username: "<<userName<<"Is User Admin: "<<isUserAdmin()<<endl;
}

string User::getFirstName() const{
    return firstName;
}

string User::getLastName() const{
    return lastName;
}

string User::getUserName() const{
    return userName;
}

string User::getPassword() const{
    return password;
}

vector<int>& User::getBooksBorrowed(){
    return booksBorrowed;
}

vector<int>& User::getBorrowHistory(){
    return borrowHistory;
}

bool User::isUserAdmin() const{
    return isAdmin;
}