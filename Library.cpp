#include "Library.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<limits>

void Library::listBooks(){
    if(books.empty()){
        cout<<"Library is Empty, there are not Books in it. Please Check after some Time!"<<endl;
        return;
    }else{
        cout<<"Here are all the Books in the Library: "<<endl;
        for(auto& book: books){
            book.displayBook();
        }
    }
}

int Library::getNewBookId(){
    srand(time(0));
    int newId = rand()%90000 + 10000;
    for(Book &book: books){
        if(book.id == newId) 
            newId = getNewBookId();
    }
    return newId;
}

void Library::addBook(){
    string title;
    string author;
    double price;
    cout<<"PLease Enter the Book Information Below: "<<endl;
    cin.ignore();
    cout<<"Book's Title: ";
    getline(cin, title);

    cout<<"Book's Author: ";
    getline(cin, author);
 
    cout<<"Book's Price: ";
    cin>>price;
    books.push_back({getNewBookId(),title,author,price,Utils::getCurrentDate(),true,""});
}

void Library::removeBook(){
    int removeId;
    cout<<"Enter the ID of the Book you want to Remove: ";
    cin>>removeId;

    auto it = remove_if(books.begin(), books.end(), [removeId](const Book& b){return b.id == removeId;});
    if(it != books.end()){
        books.erase(it, books.end());
        cout<<"Book removed from Library Successfully"<<endl;
    }else{
        cout<<"No Book found with Id: "<<removeId<<endl;
    }
    
}

string Library::toString(Book &book) {
    stringstream ss;
    ss << book.id << "," << book.title << "," << book.author << ",";
    ss << fixed << setprecision(2) << book.price << ",";
    ss << book.bookAddDate << "," << book.isAvailable << "," << book.borrowDate;

    return ss.str();
}


void Library::saveBooksToFile(string fileName){
    ofstream file(fileName);

    if(file.is_open()){
        for(auto& book: books){
            file << toString(book) <<'\n';
        }
        cout<<"All the Books are saved to the File: "<<fileName<<endl;
    }else{
        cout<<"Unable to open the File: "<<fileName<<endl;
    }
}

void Library::loadBooksFromFile(string fileName){
    ifstream file(fileName);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string title,idStr,priceStr,author,bookAddDate,isAvailableStr, borrowDate;

            getline(ss, idStr, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, priceStr, ',');
            getline(ss, bookAddDate, ',');
            getline(ss, isAvailableStr, ',');
            getline(ss, borrowDate, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);
            bool isAvailable = stoi(isAvailableStr);

            books.push_back({id,title,author,price,bookAddDate,isAvailable,borrowDate});
        }
        cout<<"Books loaded from file Successfully"<<endl;

    }else{
        cout<<"Unable to open the File: "<<fileName<<endl;
    }
}

void Library::searchBook(){
    string query,lquery; bool found = false;
    cout<<"Enter the Book Title or Author's Name to Search: ";
    getline(cin,query);
    lquery = query;
    transform(lquery.begin(), lquery.end(), lquery.begin(), ::tolower);

    for(auto& book: books){
        string bookTitle = book.title;
        string bookAuthor = book.author;
        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);
        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);
        if(bookTitle.find(query) != string::npos || bookAuthor.find(query) != string::npos){
            book.displayBook();
            found = true;
        }
    }
    if(!found){
        cout<<"There are no Books in Library with Title or Author: "<<query<<endl;
    }
}

Book* Library::getBookById(int id){
    for(Book &book: books){
        if(book.id == id){
            return &book;
        }
    }
    return nullptr;
}

//USER'S FUNCTIONS IMPLEMENTATIONS


void Library::borrowUserBook(User *user){
    int borrowId; bool found = false;
    cout<<"Enter the Book Id you want to Borrow: "; cin>>borrowId;

    for(Book &book : books){
        if(book.id == borrowId){
            found = true;
            if(book.isAvailable){
                book.changeAvailablity(false);
                book.updateBorrowDate();
                allBorrowHistory.push_back({user->getUserName(),borrowId,Utils::getCurrentDate(),"",Utils::getDate30DaysLater()});
                user->borrowBook(borrowId);
            }else{
                cout<<"Sorry the Book is not Currently Available!"<<endl;
            }
            break;
        }
    }
    if(!found){
        cout<<"No Book Found with Book Id: "<<borrowId<<endl;
    }
}

void Library::returnUserBook(User *user){
    if (user == nullptr) {
        cout << "No user Selected. Please Login First" << endl;
        return;
    }

    int returnId;
    cout << "Enter the Book Id you want to Return: ";
    cin >> returnId;

    if(user->returnBook(returnId)){
        for(auto& borrowRecord : allBorrowHistory){
            if(returnId == borrowRecord.bookId){
                borrowRecord.returnDate = Utils::getCurrentDate();
            }
        }
        getBookById(returnId)->changeAvailablity(true);
        cout<<"Book Returned Successfully"<<endl;
    }else{
        cout<<"You dont have this Book!"<<endl;
    }
}

void Library::allBorrowedBooks(User *user){
    if(user->getBooksBorrowed().empty()){
        cout<<"No Book are Borrowed Yet!"<<endl;
    }else{
        cout<<"All the Books Borrowed: "<<endl;
        for(const int &id: user->getBooksBorrowed()){
            Book* book = getBookById(id);
            if (book != nullptr) {
                book->displayBook();
            } else {
                cout << "Book Deleted From Library! No Information Available for Book with Id: "<<id <<endl;
            }
        }
    }
}

void Library::userBorrowHistory(User *user){
    if(user->getBorrowHistory().empty()){
        cout<<"No Book are Borrowed Yet!"<<endl;
    }else{
        cout<<"All the Books Previously Borrowed: "<<endl;
        for(const int& id: user->getBorrowHistory()){
            Book* book = getBookById(id);
            if (book != nullptr) {
                book->displayBook();
            } else {
                cout << "Book Deleted From Library! No Information Available for Book with Id: "<<id << endl;
            }
        }
    }
}

void Library::updateUserBorrowHistory(User *user){
    if(user->getBorrowHistory().empty()){
        string userName = user->getUserName();
        for(auto& userBookPair: allBorrowHistory){
            if(userBookPair.userName == userName){
                user->getBorrowHistory().push_back(userBookPair.bookId);
                if(!(getBookById(userBookPair.bookId)->isAvailable)){
                    user->getBooksBorrowed().push_back(userBookPair.bookId);
                }
            }
        }
    }
}

string Library::toString(BorrowRecord userBookPair) {
    stringstream ss;
    ss << userBookPair.userName << "," << userBookPair.bookId << "," << userBookPair.borrowDate << "," << userBookPair.returnDate << "," << userBookPair.dueDate;

    return ss.str();
}

void Library::saveBooksBorrowedToFile(string fileName){
    ofstream file(fileName);

    if(file.is_open()){
        for(auto& userBookPair: allBorrowHistory){
            file << toString(userBookPair) <<'\n';
        }
        cout<<"Books Borrow History is saved to the File: "<<fileName<<endl;
    }else{
        cout<<"Unable to open the File: "<<fileName<<endl;
    }
}

void Library::loadBooksBorrowedFromFile(string fileName){
    ifstream file(fileName);

    if(file.is_open()){
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string userName, bookIdStr,borrowDate, returnDate, dueDate;

            getline(ss, userName, ',');
            getline(ss, bookIdStr, ',');
            getline(ss, borrowDate, ',');
            getline(ss, returnDate, ',');
            getline(ss, dueDate, ',');

            int bookId = stoi(bookIdStr);
            allBorrowHistory.push_back({userName, bookId, borrowDate, returnDate, dueDate});
        }
        cout<<"Borrow History Loaded Successfully from File: "<<fileName<<endl;
    }else{
        cout<<"Unable to Open File: "<<fileName<<endl;
    }
}

void Library::listOverDues(){
    bool flag = false;
    cout<<"All the Books with OverDue: "<<endl;
    for(auto& borrowRecord : allBorrowHistory){
        if(borrowRecord.returnDate == "" && Utils::checkOverDue(borrowRecord.dueDate)){
            flag = true;
            getBookById(borrowRecord.bookId)->displayBook();
            cout<<"Borrower's Username: "<<borrowRecord.userName<<" | "<<"Borrow Date: "<<borrowRecord.borrowDate<<" | "<<"DueDate: "<<borrowRecord.dueDate<<" | "<<"Return Date: Not Returned Yet\n"<<endl;  
        }
    }
    if(!flag){
        cout<<"No Borrowed Books has reached DueDate."<<endl;
    }
}