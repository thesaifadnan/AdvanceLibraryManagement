#ifndef BORROW_RECORD
#define BORROW_RECORD
#include<string>
using namespace std;


class BorrowRecord{
    public:
        string userName;
        int bookId;
        string borrowDate;
        string returnDate;
        string dueDate;

        BorrowRecord(string userName, int bookId, string borrowDate, string returnDate, string dueDate);
};

#endif