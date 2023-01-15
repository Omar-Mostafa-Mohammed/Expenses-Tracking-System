#pragma once
#include <string>
#include <iostream>
using namespace std;
class expensedata
{
public:
	float amount;
	int day, month, year;
	string  category, wallet;
	expensedata(float, string, int, int, int, string);
	expensedata();
	void display();
};
expensedata::expensedata(float amoun, string cate, int d, int m, int y, string wall)
{
	amount = amoun;
	category = cate;
	day = d;
	month = m;
	year = y;
	wallet = wall;
}
expensedata::expensedata()
{
	amount = 0;
	category = "";
	day = 0;
	month = 0;
	year = 0;
	wallet = "";
}
void expensedata::display()
{
	cout << "Expense's Amount: " << amount << " , Category: " << category << " , date: " << day << "/" << month << "/" << year << " , Wallet: " << wallet << endl;
}