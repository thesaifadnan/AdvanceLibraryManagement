#include "Utils.hpp"
#include<sstream>
#include<iomanip>


string Utils::getCurrentDate(){

    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);

    ostringstream oss;
    oss << setfill('0') << setw(2) << now->tm_mday << "-"
        << setfill('0') << setw(2) << now->tm_mon + 1 << "-"
        << (now->tm_year + 1900);

    return oss.str();
}

string Utils::getDate30DaysLater(){
    time_t t = std::time(nullptr);

    t += 30 * 24 * 60 * 60;
    tm* future = std::localtime(&t);

    ostringstream oss;
    oss << setfill('0') << setw(2) << future->tm_mday << "-"
        << setfill('0') << setw(2) << future->tm_mon + 1 << "-"
        << (future->tm_year + 1900);

    return oss.str();
}

bool Utils::checkOverDue(string dueDate){
    
    int day, month, year;
    char dash1, dash2;
    istringstream iss(dueDate);
    iss >> day >> dash1 >> month >> dash2 >> year;

    if (dash1 != '-' || dash2 != '-' || iss.fail()) {
        return false;
    }

    tm due = {};
    due.tm_mday = day;
    due.tm_mon = month - 1;
    due.tm_year = year - 1900;
    due.tm_hour = 0;
    due.tm_min = 0;
    due.tm_sec = 0;

    time_t due_time = mktime(&due);

    time_t now = time(nullptr);

    return now > due_time;
}