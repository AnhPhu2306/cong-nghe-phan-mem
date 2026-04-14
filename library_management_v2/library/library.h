#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

//  CÁC HẰNG SỐ 
const string DATA_USERS    = "data/users.txt";
const string DATA_BOOKS    = "data/books.txt";
const string DATA_BORROWS  = "data/borrows.txt";
const string DATA_FINES    = "data/fines.txt";

const double FINE_PER_DAY  = 2000.0;  // 2000 VND / ngày trễ
const int    MAX_BORROW    = 5;        // Tối đa 5 sách / lần mượn

//  STRUCT ĐỊNH NGHĨA 

struct User {
    int    id;
    string username;
    string password;   // lưu dạng đơn giản (hash giả lập)
    string role;       // "admin", "librarian", "reader"
    string status;     // "active", "locked"
    string fullname;
    string email;
};

struct Book {
    int    id;
    string title;
    string author;
    string publisher;
    int    year;
    string category;
    int    quantity;    // tổng số lượng
    int    available;   // số lượng còn lại
    string location;    // vị trí kệ sách
};

struct BorrowDetail {
    int bookId;
    int quantity;
};

struct BorrowSlip {
    int    id;
    int    readerId;
    string borrowDate;  // "dd/mm/yyyy"
    string dueDate;     // hạn trả
    string returnDate;  // ngày trả thực tế (rỗng nếu chưa trả)
    string status;      // "borrowing", "returned", "overdue"
    vector<BorrowDetail> details;
};

struct Fine {
    int    id;
    int    borrowId;
    int    readerId;
    double amount;
    string reason;
    string status;  // "unpaid", "paid"
    string createdDate;
};

//  BIẾN TOÀN CỤC 
extern vector<User>       gUsers;
extern vector<Book>       gBooks;
extern vector<BorrowSlip> gBorrows;
extern vector<Fine>       gFines;
extern User*              gCurrentUser;  // người đang đăng nhập

//  KHAI BÁO HÀM 

// --- Tiện ích ---
string  getCurrentDate();
int     daysBetween(string date1, string date2);
string  addDays(string date, int days);
string  hashPassword(string password);
void    clearScreen();
void    pause();
int     generateId(int size);

// --- File I/O ---
void loadAllData();
void saveAllData();
void loadUsers();
void loadBooks();
void loadBorrows();
void loadFines();
void saveUsers();
void saveBooks();
void saveBorrows();
void saveFines();

// --- Auth ---
bool login();
void logout();
void changePassword();

// --- Sách ---
void manageBook();
void addBook();
void updateBook();
void deleteBook();
void listBooks();
void searchBook();
void viewBookDetail(int bookId);

// --- Độc giả ---
void manageReader();
void addReader();
void updateReader();
void deleteReader();
void lockReader();
void listReaders();

// --- Mượn sách ---
void manageBorrow();
void createBorrowSlip();
void confirmReturn();
void listBorrows();
void viewBorrowHistory(int readerId = -1);

// --- Tiền phạt ---
void manageFine();
void listFines();
void payFine();

// --- Báo cáo ---
void viewReport();
void reportBookStat();
void reportOverdue();
void reportTopBorrower();

// --- Quản lý User (Admin) ---
void manageUser();
void listUsers();
void lockUser();
void unlockUser();

// --- Menu ---
void menuReader();
void menuLibrarian();
void menuAdmin();

#endif
