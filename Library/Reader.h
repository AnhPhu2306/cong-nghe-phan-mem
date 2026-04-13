#pragma once
#include "User.h"
#include <ctime>
#include <list>
#include "Book.h"

using namespace std;

struct Date
{
	int day;
	int month;
	int year;
};

class Reader : protected User
{
private:
	int reader_id;
	string full_name;
	Date dob;
	string gender;
	string address;
	string phone;
	string email;
public:
	Reader(int Id, string fullName, Date dob, string gender, string address, string phone, string email) // Hàm constructor có tham số
		: User(Id, "", "", "", ""), reader_id(Id), full_name(fullName), dob(dob), gender(gender), address(address), phone(phone), email(email)
	{
	}
	// Hàm constructor mặc định
	Reader() : User(), reader_id(0), full_name(""), dob{0, 0, 0}, gender(""), address(""), phone(""), email("")
	{
	}

	~Reader() {}

	int getReaderId() const
	{
		return reader_id;
	}

	int setReaderId(int id)
	{
		this->reader_id = id;
	}
	
	int getUserId() const
    {
		return User::getUserId(); //Sử dụng get của lớp User để lấy user_id
    }

	string getStatus() const
	{
		return User::getStatus(); //Sử dụng get của lớp User để lấy status
	}
};

