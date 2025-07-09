#include "BorrowRecord.hpp"

BorrowRecord::BorrowRecord(string userName, int bookId, string borrowDate, string returnDate, string dueDate){
    this->userName = userName;
    this->bookId = bookId;
    this->borrowDate = borrowDate;
    this->returnDate = returnDate;
    this->dueDate = dueDate;
}