# 📚 Library Management System (C++)

This is a command-line based Advance Library Management System written in **C++** to practice object-oriented programming, file handling, and system design.

---

## ✅ Features

### 👤 User & Admin Authentication
- User Registration & Login
- Admin Privileges for managing books & users

### 📖 Book Management
- Add / Remove books (Admin only)
- List and search books (all users)

### 📦 Borrowing System
- Borrow and return books
- Borrow history and active borrowed list
- Due dates and overdue book detection

### 🗃️ Persistent Storage
- Stores data in files:
  - `books.txt`
  - `users.txt`
  - `borrowHistory.txt`

---

## 🧠 Tech Stack

- **C++17**
- Standard Template Library (STL)
- File I/O
- Object-Oriented Programming (OOP)

---

## 📁 File Structure

📂 data/

├── books.txt

├── users.txt

└── borrowHistory.txt


📂 src/

├── main.cpp

├── Book.cpp/hpp

├── User.cpp/hpp

├── Library.cpp/hpp

├── BorrowRecord.cpp/hpp

├── UserManager.cpp/hpp

└── Utils.cpp/hpp

## 🚀 How to Run

1. Clone the repo
2. Compile using:
   ```bash
   g++ Main.cpp Library.cpp Book.cpp User.cpp Utils.cpp BorrowRecord.cpp UserManager.cpp -o library
   
3. Run the app:
   ```bash
    ./library
   
👨‍💻 Author
Made with ❤️ by Adnan Sheikh as a mini project for learning full-stack basics in C++.
