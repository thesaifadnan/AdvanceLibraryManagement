#ifndef UTILS_HPP
#define UTILS_HPP
#include<string>
using namespace std;

class Utils{
    public:
        static string getCurrentDate();
        static string getDate30DaysLater();
        static bool checkOverDue(string dueDate);
};

#endif