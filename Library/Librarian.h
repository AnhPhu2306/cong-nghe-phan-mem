#pragma once
#include "User.h"
#include <iostream>
#include <vector>
#include "Book.h"
#include "BorrowSlip.h"
using namespace std;

class Book;

class BorrowSlip;

class Librarian : protected User
{
public:

	Librarian(int id, string user, string pass, string Role, string Status) 
		: User(id, user, pass, Role, Status)
	{
	}

	~Librarian() {}

	void addBook(vector<Book>& books, const Book& newBook) // Thêm sách mới vào thư viện
	{
		books.push_back(newBook);
		cout << "Book added to the library: " << newBook.getTitle() << endl;
	}

	void updateBook(Book* book, string newTitle, string newAuthor, int newYear) // Cập nhật thông tin sách
	{
		book->setTitle(newTitle);
		book->setAuthor(newAuthor);
		book->setPublishYear(newYear);
		cout << "Book information updated." << endl;
	}

	void deleteBook(vector<Book>& books, int bookId) //xóa sách khỏi thư viện
	{
		auto it = find_if(books.begin(), books.end(), [bookId](const Book& book) {
			return book.getBookId() == bookId;
		});
		if (it != books.end()) {
			books.erase(it);
			cout << "Book deleted from the library." << endl;
		} else {
			cout << "Book not found." << endl;
		}
	}

	BorrowSlip* createBorrowSlip(int readerId, vector<BorrowDetail> details) // Tạo phiếu mượn
	{
		static int borrowIdCounter = 1; // Counter để tạo ID phiếu mượn duy nhất
		BorrowSlip* newSlip = new BorrowSlip(borrowIdCounter++, readerId, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, "active");
		newSlip->setDetails(details);
		cout << "Borrow slip created for reader ID: " << readerId << endl;
		return newSlip;
	}

	void processReturn(BorrowSlip* slip) // Xử lý trả sách
	{
		slip->setReturnDate({0, 0, 0}); // Cập nhật ngày trả sách (giả sử ngày hiện tại)
		slip->setStatus("returned"); // Cập nhật trạng thái phiếu mượn
		cout << "Book return processed for borrow ID: " << slip->getDetails().size() << endl;
	}

	void comfirmBorrow(BorrowSlip* slip) // Xác nhận mượn sách
	{
		slip->setStatus("confirmed");
		cout << "Borrow confirmed for borrow ID: " << slip->getDetails().size() << endl;
	}

	void manageFines(BorrowSlip* slip, int DateLate)
	{
		double fineAmount = slip->calculateFine({0, 0, 0}); // Giả sử ngày hiện tại
		if (fineAmount > 0) {
			cout << "Fine calculated: $" << fineAmount << endl;
			// Xử lý thanh toán phạt nếu cần
		} else {
			cout << "No fine for this borrow slip." << endl;
		}
	}

};
