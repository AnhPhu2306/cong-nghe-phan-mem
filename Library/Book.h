#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    int book_id;
    int category_id;
    string title;
    string author;
    string publisher;
    int publish_year;
    int quantity;
    string location;
    void* extra; // Placeholder for pointer, adjust type as needed

public:
	//Hàm constructor có tham số
    Book(int bookId, int categoryId, const string& bookTitle, const string& bookAuthor, const string& bookPublisher, int year, int qty, const string& loc, void* extraPtr)
        : book_id(bookId), category_id(categoryId), title(bookTitle), author(bookAuthor), publisher(bookPublisher), publish_year(year), quantity(qty), location(loc), extra(extraPtr)
    {
    }

    // Default constructor
    Book()
        : book_id(0), category_id(0), title(""), author(""), publisher(""), publish_year(0), quantity(0), location(""), extra(nullptr)
    {
    }

    int getBookId() const { return book_id; }
    string getTitle() const { return title; }
    void setTitle(const string& newTitle) { title = newTitle; }
    void setAuthor(const string& newAuthor) { author = newAuthor; }
    void setPublishYear(int newYear) { publish_year = newYear; }
};

