#pragma once
#include "User.h"
#include <iostream>
#include "Reader.h"
#include "Librarian.h"
using namespace std;
class Admin : protected User
{
public:
	Admin(int id, string user, string pass, string Role, string Status) 
		: User(id, user, pass, Role, Status)
	{
	}

	~Admin(){}

	void addUser(vector<User>& users, User newUser) // Thêm người dùng mới
	{
		users.push_back(newUser);
		cout << "New user added: " << newUser.getUserId() << endl;
	}

	void updateUser(User& user, string newUsername, string newPassword, string newRole, string newStatus) // Cập nhật thông tin người dùng
	{
		user.setUserName(newUsername);
		user.setPassword(newPassword);
		user.setRole(newRole);
		user.setStatus(newStatus);
		cout << "User information updated for user ID: " << user.getUserId() << endl;
	}
	
	void deleteUser(vector<User>& users, int userId) // Xóa người dùng
	{
		auto it = find_if(users.begin(), users.end(), [userId](const User& user) {
			return user.getUserId() == userId;
		});
		if (it != users.end()) {
			users.erase(it);
			cout << "User deleted with ID: " << userId << endl;
		} else {
			cout << "User not found." << endl;
		}
	}

	void mangeUsers() // Quản lý người dùng
	{
		cout << "User management interface.\n" << endl;
	}

	void managePermissions(User* user, string newRole) // Quản lý quyền hạn người dùng
	{
		user->setRole(newRole);
		cout << "Permissions updated for user ID: " << user->getUserId() << " to role: " <<	newRole << endl;
	}

	void viewReports() // Xem báo cáo hoạt động của thư viện
	{
		cout << "Viewing library activity reports.\n" << endl;
	}
	
};

