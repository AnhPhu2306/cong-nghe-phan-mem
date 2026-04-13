#pragma once
#include <string>
#include <iostream>
using namespace std;
class User
{
protected:
	int user_id;
	string username;
	string password;
	string role;
	string status;
public:

	User() : user_id(0), username(""), password(""), role(""), status("active") //Hàm constructor mặc định
	{}

	User(int id, string user, string pass, string Role, string Status) //Hàm constructor có tham số
	{
		user_id = id;
		username = user;
		password = pass;
		role = Role;
		status = Status;
	}

	~User() //Hàm hủy
	{	}

	int getUserId() const
	{
		return user_id;
	}

	string getStatus() const
	{
		return status;
	}

	string getRole() const
	{
		return role;
	}

	string getStatus()
	{
		return status;
	}

	string setUserName(string user)
		{
		this->username = user;
	}

	string setPassword(string pass)
	{
		this->password = pass;
	}

	string setRole(string role)
	{
		this->role = role;
	}

	string setStatus(string status)
	{
		this->status = status;
	}

	bool login()
	{
		string username, password;
		cout << "Username: " << username << "\nPassword:" << password << endl;
		if (this->username == username && this->password == password)
		{
			cout << "Login successful!" << endl;
			return true;
		}
		else
		{
			cout << "Login failed!" << endl;
			return false;
		}
	}

	void logout()
	{
		cout << "User logged out." << endl;
	}
	void changePassword(string newPassword)
	{
		this->password = newPassword;
		cout << "Password changed successfully!" << endl;
	}
};

