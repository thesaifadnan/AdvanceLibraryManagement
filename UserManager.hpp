#ifndef USER_MANAGER
#define USER_MANAGER
#include "User.hpp"

class UserManager{
    vector<User> users;
    User* currentUser = nullptr;
    public:

        User* getCurrentUser();
        bool registerUser();
        void addUser();
        void removeUser();
        bool loginUser();
        bool logoutUser();
        void listAllUsers();
        string toString(User&);
        void loadUsersFromFile(string fileName);
        void saveUsersToFile(string fileName);
        bool isAdmin();
};

#endif