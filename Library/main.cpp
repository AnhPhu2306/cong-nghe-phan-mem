#include <iostream>
#include <vector>
#include "User.h"
#include "Admin.h"
#include "Reader.h"
#include "Librarian.h"
#include "Book.h"
#include "Category.h"
#include "BorrowSlip.h"
#include "Fine.h"
#include "BorrowDetail.h"
using namespace std;

int main() {
    // Tạo một số đối tượng để kiểm tra
    Admin admin(1, "adminUser", "adminPass", "admin", "active");
    Reader reader(2, "John Doe", { 1, 1, 1990 }, "F", "HCM", "0123", "mail@gmail.com");
    Librarian librarian(3, "libUser", "libPass", "librarian", "active");
    // Kiểm tra chức năng của Admin
    admin.mangeUsers();
    admin.viewReports();
    // Kiểm tra chức năng của Librarian

	std::vector<Book> books; // Tạo một vector để lưu trữ sách
    librarian.addBook(books, Book(1, 1, "Book Title", "Author Name", "Publisher", 2020, 10, "A1", nullptr));

    librarian.createBorrowSlip(reader.getUserId(), std::vector<BorrowDetail>());
    // Kiểm tra chức năng của Reader
    cout << "Reader Name: " << reader.getStatus() << endl;
    return 0;
}