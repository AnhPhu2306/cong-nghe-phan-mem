#pragma once
#include <iostream>
#include <string>
using namespace std;

class Fine
{
private:
	int fine_id;
	double amount;
	string reason;
	string payment_status;
public:
	Fine(int id, double amt, string rsn, string paymentStatus)
		: fine_id(id), amount(amt), reason(rsn), payment_status(paymentStatus)
	{
	}

	double calculateFine(int daysLate)
	{
		const double finePerDay = 5000;
		return daysLate * finePerDay;
	}

	void getFine()
	{
		cout << "Fine ID: " << fine_id << ", Amount: " << amount << ", Reason: " << reason << ", Payment Status: " << payment_status << endl;
	}

	void markPaid()
	{
		payment_status = "paid";
	}
};