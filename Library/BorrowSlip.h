#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Fine.h"
#include "Book.h"
#include "Reader.h"
#include "BorrowDetail.h"
using namespace std;

class BorrowSlip
{
private:
	int borrow_id;
	int reader_id;
	Date borrow_date;
	Date due_date;
	Date return_date;
	string status;
	vector<BorrowDetail> details; //Mỗi phiếu mượn có thể có nhiều chi tiết mượn
	Fine* fine = nullptr; //Trỏ đến Fine, có thể là nullptr nếu không có phạt Fine* fine = nullptr
public:
	BorrowSlip(int id, int readerId, Date borrowDate, Date dueDate, Date returnDate, string stat)
		: borrow_id(id), reader_id(readerId), borrow_date(borrowDate), due_date(dueDate), return_date(returnDate), status(stat), fine(nullptr)
	{
	}

	void setReturnDate(const Date& newReturnDate) // Set ngày trả sách
	{
		return_date = newReturnDate;
	}

	void setStatus(const string& newStatus) // Set trạng thái phiếu mượn
	{
		status = newStatus;
	}

	void setDetails(const vector<BorrowDetail>& newDetails)// Set chi tiết mượn cho phiếu mượn
	{
		details = newDetails;
	}

	const vector<BorrowDetail>& getDetails() const // Thêm get cho details
	{
		return details;
	}

	~BorrowSlip()
	{
		delete fine; // Giải phóng bộ nhớ cho đối tượng Fine nếu nó tồn tại
	}

	double calculateFine(Date currentDate)
	{
		if (return_date.year == 0) // Nếu chưa trả sách
		{
			int daysLate = (currentDate.year - due_date.year) * 365 + (currentDate.month - due_date.month) * 30 + (currentDate.day - due_date.day);
			if (daysLate > 0)
			{
				Fine fine(0, 0.0, "Late return", "unpaid");
				return fine.calculateFine(daysLate);
			}
		}
		return 0.0; // Không có phí nếu đã trả sách hoặc chưa đến hạn
	}
};

BorrowSlip* createBorrowSlip(int readerId, vector<BorrowDetail> details) // Tạo phiếu mượn
{
	static int borrowIdCounter = 1; // Counter để tạo ID phiếu mượn duy nhất
	BorrowSlip* newSlip = new BorrowSlip(borrowIdCounter++, readerId, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, "active"); // Tạo phiếu mượn mới với thông tin cơ bản
	newSlip->setDetails(details); // Sử dụng set thay vì truy cập trực tiếp
	cout << "Borrow slip created for reader ID: " << readerId << endl;
	return newSlip;
}

