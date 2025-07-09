#include "UserManager.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

bool UserManager::registerUser(){
    string firstName, lastName, userName, password;
    bool isAdmin;

    cout<<"Enter User Information: "<<endl;
    cout<<"Enter Your First Name: "; getline(cin,firstName);
    cout<<"Enter Your Last Name: "; getline(cin,lastName);
    InputUserName:
    cout<<"Create Your Unique Username: "; getline(cin,userName);

    for(auto& user :users){
        if(user.getUserName() == userName){
            cout<<"Username already Exists! Please Choose another Username and Try Again."<<endl;
            goto InputUserName;
        }
    }

    cout<<"Create Your Strong Password: "; getline(cin,password);
    cout<<"Are You an Admin (1/0): "; cin>>isAdmin;
    cin.ignore();
    users.push_back({firstName, lastName, userName, password, isAdmin});
    currentUser = &users.back();
    cout<<(isAdmin ? "Admin":"User")<<" Registered Successfully."<<endl;
    return true;
}

void UserManager::removeUser(){
    string removeUser;
    cout<<"Enter the Username of the User you want to Remove: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,removeUser);

    auto it = remove_if(users.begin(), users.end(), [removeUser](const User& user){return (user.getUserName() == removeUser);});
    if(it != users.end()){
        users.erase(it, users.end());
        cout<<"User removed from Library Successfully"<<endl;
    }else{
        cout<<"No User found with Username: "<<removeUser<<endl;
    }
}

void UserManager::addUser(){
    string firstName, lastName, userName, password;
    bool isAdmin;

    cout<<"Enter User Information: "<<endl;
    cout<<"Enter User's First Name: "; getline(cin,firstName);
    cout<<"Enter User's Last Name: "; getline(cin,lastName);
    cout<<"Create User's Unique Username: "; getline(cin,userName);
    cout<<"Create User's Strong Password: "; getline(cin,password);
    cout<<"Is User an Admin (1/0): "; cin>>isAdmin;
    users.push_back({firstName, lastName, userName, password, isAdmin});
    currentUser = &users.back();
    cout<<(isAdmin ? "Admin":"User")<<" Added Successfully."<<endl;
}

void UserManager::listAllUsers(){
    if(users.empty()){
        cout<<"There are no Users Regsitered in the Library!"<<endl;
    }else{
        cout<<"Here are all the Users: "<<endl;
        for(User &user : users){
            user.displayUser();
        }
    }
}



string UserManager::toString(User &user) {
    stringstream ss;
    ss << user.getFirstName()<<","<<user.getLastName()<<","<<user.getUserName()<<","<<user.getPassword()<<","<<user.isUserAdmin();

    return ss.str();
}

void UserManager::saveUsersToFile(string fileName){
    ofstream file(fileName);

    if(file.is_open()){
        for(auto& user: users){
            file << toString(user) <<'\n';
        }
        cout<<"All the Users are saved to the File: "<<fileName<<endl;
    }else{
        cout<<"Unable to open the File: "<<fileName<<endl;
    }
}

void UserManager::loadUsersFromFile(string fileName){
    ifstream file(fileName);

    if(file.is_open()){
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string firstName, lastName, userName, password, isAdminStr;

            getline(ss,firstName,',');
            getline(ss,lastName, ',');
            getline(ss, userName, ',');
            getline(ss, password, ',');
            getline(ss, isAdminStr, ',');

            bool isAdmin = stoi(isAdminStr);

            users.push_back({firstName,lastName,userName,password,isAdmin});
        }
        cout<<"Users Data Successfully Loaded from File: "<<fileName<<endl;
    }else{
        cerr<<"Unable to Open User's Data File: "<<fileName<<endl;
    }
}

bool UserManager::loginUser(){
    string userName, password;

    cout<<"Enter Your Username: "; getline(cin,userName);
    cout<<"Enter Your Password: "; getline(cin,password);

    for(User &user: users){
        if(user.getUserName() == userName && user.getPassword() == password){
            currentUser = &user;
            return true;
        }
    }
    return false;
}

bool UserManager::logoutUser(){
    currentUser = nullptr;
    return false;
}

User* UserManager::getCurrentUser(){
    return currentUser;
}

bool UserManager::isAdmin(){
    return currentUser->isUserAdmin();
}