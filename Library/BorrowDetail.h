#pragma once
#include <iostream>
#include "Book.h"
using namespace std;

class BorrowDetail
{
private:
	int detail_id;
	int quantity;
	Book* book; // Association
public:
	BorrowDetail(int id, int qty, Book* b) : detail_id(id), quantity(qty), book(b) //ham constructor
	{
	}

	Book* getBook() const
	{
		return book;
	}
};