#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "ArrList.h"
#include "expe.h"
using namespace std;
using namespace chrono;
string checkenteredwallet();
int enterMonth();
int enterYear();
float checkamount();
int enterDay(int, int);
string MonthName(int month);
struct wallet
{
	float cash, credit;
};
class user
{
public:
	string name;
	wallet mywallet;
	int month, year;
	user(string, wallet, int, int);
	void DisplayAllExpenses(ArrList<expensedata> exp);
	void filterExpensesByWallet(ArrList<expensedata>, string);
	void filterExpensesByAmount(ArrList<expensedata>, float);
	void filterExpensesByCategory(ArrList<expensedata>, string);
	void filterExpensesByDate(ArrList<expensedata>, int, int, int);
	void filterExpensesByMany(ArrList<expensedata>);
	float RemMoneyForCash(float, float);
	float RemMoneyForCredit(float,float);
	float MoneyForCredit(ArrList<expensedata>);
	float MoneyForCash(ArrList<expensedata>);
	void writetxtfile(ArrList<expensedata>);
	int Mainmenu();
	void Displaymenu(ArrList<expensedata>);
	void RemMoneymenu(ArrList<expensedata>);
	void Caldebtsaving(ArrList<expensedata>);
	void continuemsg();
	void userinterface(ArrList<expensedata> exp);
};

user::user(string uname, wallet mywall, int mon, int yea)
{
	name = uname;
	mywallet = mywall;
	month = mon;
	year = yea;
}
float user::RemMoneyForCash(float allcashexp, float cashincome) {
	return cashincome - allcashexp;
}
float user::RemMoneyForCredit(float allcreditexp, float creditincome)
{
	return creditincome - allcreditexp;
}
float user::MoneyForCredit(ArrList<expensedata> exp)
{
	float sum = 0;
	for (int i = 0; i < exp.Length(); i++)
	{
		if (exp.At(i).wallet == "credit")
			sum += exp.At(i).amount;
	}
	return sum;
}
float user::MoneyForCash(ArrList<expensedata> exp)
{
	float sum = 0;
	for (int i = 0; i < exp.Length(); i++)
	{

		if (exp.At(i).wallet == "cash")
			sum += exp.At(i).amount;
	}
	return sum;
}
void user::DisplayAllExpenses(ArrList<expensedata> exp)
{
	for (int i = 0; i < exp.Length(); i++)
		exp.At(i).display();
}
void user::filterExpensesByWallet(ArrList<expensedata> exp, string wallet)
{
	ArrList<expensedata> tmp;
	for (int i = 0; i < exp.Length(); i++)
		if (exp.At(i).wallet == wallet)
			tmp.Append(exp.At(i));
	if (tmp.Length() == 0)
		cout << "No Data Found!!!" << endl;
	else
		for (int j = 0; j < tmp.Length(); j++)
			tmp.At(j).display();
}
void user::filterExpensesByAmount(ArrList<expensedata> exp, float amount)
{

	ArrList<expensedata> tmp;
	for (int i = 0; i < exp.Length(); i++)
		if (exp.At(i).amount == amount)
			tmp.Append(exp.At(i));
	if (tmp.Length() == 0)
		cout << "No Data Found!!!" << endl;
	else
		for (int j = 0; j < tmp.Length(); j++)
			tmp.At(j).display();
}
void user::filterExpensesByCategory(ArrList<expensedata> exp, string category)
{

	ArrList<expensedata> tmp;
	for (int i = 0; i < exp.Length(); i++)
		if (exp.At(i).category == category)
			tmp.Append(exp.At(i));
	if (tmp.Length() == 0)
		cout << "No Data Found!!!" << endl;
	else
		for (int j = 0; j < tmp.Length(); j++)
			tmp.At(j).display();
}
void user::filterExpensesByDate(ArrList<expensedata> exp, int day, int month, int year)
{

	ArrList<expensedata> tmp;
	for (int i = 0; i < exp.Length(); i++)
		if (exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year)
			tmp.Append(exp.At(i));
	if (tmp.Length() == 0)
		cout << "No Data Found!!!" << endl;
	else
		for (int j = 0; j < tmp.Length(); j++)
			tmp.At(j).display();
}
void user::filterExpensesByMany(ArrList<expensedata> exp)
{
	int number, day;
	float amount;
	string category, wallet;
	
	while (true)
	{
		ArrList<expensedata> tmp;
		system("CLS");
		cout << "****************************************************************" << endl;
		cout << setw(40) << "Many Filters Menu" << endl;
		cout << "****************************************************************" << endl << endl;
		cout << "1. Apply Amount and Category Filters." << endl;
		cout << "2. Apply Amount and Date Filters." << endl;
		cout << "3. Apply Amount and Wallet Filters." << endl;
		cout << "4. Apply Wallet and Category Filters." << endl;
		cout << "5. Apply Wallet and Date Filters." << endl;
		cout << "6. Apply Date and Category Filters." << endl;
		cout << "7. Apply Amount , Category and Wallet Filters." << endl;
		cout << "8. Apply Amount , Category and Date Filters." << endl;
		cout << "9. Apply Amount, Category, Date and Wallet Filters." << endl;
		cout << "10. Return to Previous Menu." << endl << endl;
		cout << "Enter Choice: ";
		cin >> number;
		system("CLS");
		if (number == 1)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Category of Expenses: ";
			cin >> category;
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).category == category)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 2)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Day of Expenses: ";
			day = enterDay(month, year);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 3)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Wallet of Expenses (cash or credit): ";
			wallet = checkenteredwallet();
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).wallet == wallet)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 4)
		{
			cout << "Enter Category of Expenses: ";
			cin >> category;
			cout << "Enter Wallet of Expenses (cash or credit): ";
			wallet = checkenteredwallet();
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).category == category && exp.At(i).wallet == wallet)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 5)
		{
			cout << "Enter Day of Expenses: ";
			day = enterDay(month, year);
			cout << "Enter Wallet of Expenses (cash or credit): ";
			wallet = checkenteredwallet();
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).wallet == wallet && exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 6)
		{
			cout << "Enter Day of Expenses: ";
			day = enterDay(month, year);
			cout << "Enter Category of Expenses (cash or credit): ";
			cin >> category;
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).category == category && exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 7)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Category of Expenses: ";
			cin >> category;
			cout << "Enter Wallet of Expenses (cash or credit): ";
			wallet = checkenteredwallet();
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).category == category && exp.At(i).wallet == wallet)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 8)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Category of Expenses: ";
			cin >> category;
			cout << "Enter Day of Expenses: ";
			day = enterDay(month, year);
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).category == category && exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 9)
		{
			cout << "Enter Amount of Expenses: ";
			amount = checkamount();
			cout << "Enter Category of Expenses: ";
			cin >> category;
			cout << "Enter Day of Expenses: ";
			day = enterDay(month, year);
			cout << "Enter Wallet of Expenses (cash or credit): ";
			wallet = checkenteredwallet();
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			for (int i = 0; i < exp.Length(); i++)
				if (exp.At(i).amount == amount && exp.At(i).category == category && exp.At(i).day == day && exp.At(i).month == month && exp.At(i).year == year && exp.At(i).wallet == wallet)
					tmp.Append(exp.At(i));
			if (tmp.Length() == 0)
				cout << "No Data Found!!!" << endl;
			else
			{
				for (int j = 0; j < tmp.Length(); j++)
					tmp.At(j).display();
				tmp.delArrList();
			}
			continuemsg();
		}
		else if (number == 10)
			break;
	}
}
void user::writetxtfile(ArrList<expensedata> exp)
{
	system("CLS");
	ofstream write;
	string filename = name + "_expensesdata.txt";
	write.open(filename);

	write << "Name: " << name << endl;
	write << "Cash Money: " << mywallet.cash << " , Credit card Money: " << mywallet.credit << endl;
	
	if (exp.Length() == 0)
		write << "No Expenses Found !!!" << endl;
	else
	{
		write << "All Expenses Information: " << endl;
		for (int i = 0; i < exp.Length(); i++)
		{
			write << "Expense's Amount: " << exp.At(i).amount << " , Category: " << exp.At(i).category << " , date: " << exp.At(i).day << "/" << exp.At(i).month << "/" << exp.At(i).year << " , Wallet: " << exp.At(i).wallet << endl;
		}
	}
	write << endl;
	float costofcashexpenses = MoneyForCash(exp);
	float costofcreditexpenses = MoneyForCredit(exp);
	write << "Cost of expenses you have to pay in cash: " << costofcashexpenses << endl;
	write << "Cost of expenses you have to pay from credit card: " << costofcreditexpenses << endl;
	float remcash = RemMoneyForCash(costofcashexpenses, mywallet.cash);
	float remincredit = RemMoneyForCredit(costofcreditexpenses, mywallet.credit);
	double saving = remincredit + remcash;
	if (remcash >= 0)
		write << "Remaining cash is: " << remcash << endl;
	else
	{
		remcash *= -1;
		write << "You have debt: " << remcash << "  on you to pay it in cash" << endl;
	}
	if (remincredit >= 0)
		write << "Remaining Money in Credit card is: " << remincredit << endl;
	else
	{
		remincredit *= -1;
		write << "You have debt: " << remincredit << "  on you to pay it for your credit card" << endl;
	}
	if (saving >= 0)
		write << "Your saving is: " << saving << endl;
	else
	{
		saving *= -1;
		write << "You have debt and its amount is: " << saving << endl;
	}
	time_t now = time(0);
	tm *ltm = localtime(&now);
	write << "This file was created on: " << asctime(ltm) << endl;
	cout << setw(45) << "File Created !!!" << endl << endl;
	write.close();
}
int user:: Mainmenu() 
{
	int ch;
	cout << "1. Enter your Daily Expenses.\n";
	cout << "2. Display All Expenses.\n";
	cout << "3. Display Remaining Money.\n";
	cout << "4. Calculating your debt and saving.\n";
	cout << "5. Save Data in a TextFile.\n";
	cout << "6. Exit Program.\n";
	do {
		cout << "\nEnter Your choice: ";
		cin >> ch;
	} while (ch <= 0 || ch > 6);
	return ch;
}
void user::Displaymenu(ArrList<expensedata> exp)
{
	int ch, day;
	float amount;
	string category, wallet;
	system("CLS");
	if (exp.Length() == 0)
	{
		cout << "You don't have any Expenses Please add some!!" << endl;
		continuemsg();
	}
	else
	{
		while (true)
		{
			system("CLS");
			cout << "****************************************************************" << endl;
			cout << setw(40) << "Display Your Expenses" << endl;
			cout << "****************************************************************" << endl << endl;
			cout << "1. Display All Expenses.\n";
			cout << "2. Apply Amount Filter on Expenses.\n";
			cout << "3. Apply Category Filter on Expenses.\n";
			cout << "4. Apply Date Filter on Expenses.\n";
			cout << "5. Apply Wallet Filter on Expenses.\n";
			cout << "6. Apply Many Filter on Expenses.\n";
			cout << "7. Return to Main Menu.\n\n";
			cout << "Enter Your Choice: ";
			cin >> ch;
			system("CLS");
			if (ch == 1)
			{
				DisplayAllExpenses(exp);
				continuemsg();
			}	
			else if (ch == 2)
			{
				cout << "Enter Cost of Expens you want to search for: ";
				amount = checkamount();
				filterExpensesByAmount(exp, amount);
				continuemsg();
			}
			else if (ch == 3)
			{
				cout << "Enter Category of Expens you want to search for: ";
				cin >> category;
				transform(category.begin(), category.end(), category.begin(), ::tolower);
				filterExpensesByCategory(exp, category);
				continuemsg();
			}
			else if (ch == 4)
			{
				cout << "Enter Day of Expens you want to search for: ";
				day = enterDay(month, year);
				filterExpensesByDate(exp, day, month, year);
				continuemsg();
			}
			else if (ch == 5)
			{
				cout << "Enter Wallet of Expens you want to search for (cash or credit): ";
				wallet = checkenteredwallet();
				filterExpensesByWallet(exp, wallet);
				continuemsg();
			}
			else if (ch == 6)
			{
				filterExpensesByMany(exp); 
				continuemsg();
			}
			else if (ch == 7)
				break;
		}//end of while

		/*cout << "1. Display All Expenses.\n";
		cout << "2. Apply Amount Filter on Expenses.\n";
		cout << "3. Apply Category Filter on Expenses.\n";
		cout << "4. Apply Date Filter on Expenses.\n";
		cout << "5. Apply Wallet Filter on Expenses.\n";
		cout << "6. Apply Many Filter on Expenses.\n\n";
		cout << "Enter Your Choice: ";
		cin >> ch;
		system("CLS");
		switch (ch)
		{
		case 1:
			DisplayAllExpenses(exp);
			break;
		case 2:
			cout << "Enter Cost of Expens you want to search for: ";
			amount = checkamount();
			filterExpensesByAmount(exp, amount);
			break;
		case 3:
			cout << "Enter Category of Expens you want to search for: ";
			cin >> category;
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			filterExpensesByCategory(exp, category);
			break;
		case 4:
			cout << "Enter Day of Expens you want to search for: ";
			day = enterDay(month, year);
			filterExpensesByDate(exp, day, month, year);
			break;
		case 5:
			cout << "Enter Wallet of Expens you want to search for (cash or credit): ";
			wallet = checkenteredwallet();
			filterExpensesByWallet(exp, wallet);
			break;
		case 6:
			filterExpensesByMany(exp);
			break;
		default:
			cout << "Invalid Choice";
			break;
		}*/
	}
}
void user::RemMoneymenu(ArrList<expensedata> exp)
{
	int ch;
	do 
	{
		system("CLS");
		cout << "*******************************************************************************" << endl << endl;
		cout << setw(45) << "Remaning Money" << endl << endl;
		cout << "*******************************************************************************" << endl << endl;
		cout << "1. Remaning Cash.\n";
		cout << "2. Remaning Money in Credit card.\n";
		cout << "\nEnter Your choice: ";
		cin >> ch;
		system("CLS");
		if (ch == 1)
		{
			float exepensescash = MoneyForCash(exp);
			float remcash = RemMoneyForCash(exepensescash, mywallet.cash);
			if (remcash >= 0)
				cout << "Remaining cash is: " << remcash << endl;
			else
			{
				remcash *= -1;
				cout << "You have debt: " << remcash << "  on you to pay it in cash" << endl;
			}
		}
		else if (ch == 2)
		{
			float exepensescredit = MoneyForCredit(exp);
			float remincredit = RemMoneyForCredit(exepensescredit, mywallet.credit);
			if (remincredit >= 0)
				cout << "Remaining Money in Credit card is: " << remincredit << endl;
			else
			{
				remincredit *= -1;
				cout << "You have debt: " << remincredit << "  on you to pay it for your credit card" << endl;
			}
		}
	} while (ch <= 0 || ch > 2);
}
void user::Caldebtsaving(ArrList<expensedata> exp)
{
	system("CLS");
	float saving;
	float exepensescash = MoneyForCash(exp);
	float remcash = RemMoneyForCash(exepensescash, mywallet.cash);
	float exepensescredit = MoneyForCredit(exp);
	float remincredit = RemMoneyForCredit(exepensescredit, mywallet.credit);
	saving = remincredit + remcash;
	cout << "*******************************************************************************" << endl << endl;
	cout << setw(45) << "Saving/Debt Information" << endl << endl;
	cout << "*******************************************************************************" << endl << endl;
	if (saving >= 0)
		cout << "Your saving is: " << saving << endl;
	else
	{
		saving *= -1;
		cout << "You have debt and its amount is: " << saving << endl;
	}
	cout << endl;
}
void user:: continuemsg()
{
	char ans;
	cout << "Do You want to go back?";
	cin >> ans;
	if (ans == 'n' || ans == 'N')
		exit(0);
}
void user::userinterface(ArrList<expensedata> exp)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	float cashsaving = 0, creditsaving = 0, cashdebt = 0, creditdebt = 0;
	float costofcashexpenses = MoneyForCash(exp);
	float costofcreditexpenses = MoneyForCredit(exp);
	float remcash = RemMoneyForCash(costofcashexpenses, mywallet.cash);
	float remincredit = RemMoneyForCredit(costofcreditexpenses, mywallet.credit);

	cout << "*******************************************************************************" << endl << endl;
	cout << setw(40) << "Welcome " << name << endl << endl;
	cout << "*******************************************************************************" << endl << endl;
	
	cout << "Date: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl << endl;
	cout << "Cash: " << mywallet.cash << setw(50) << "Credit card: " << mywallet.credit << endl << endl;
	if (remcash >= 0 && remincredit >= 0)
	{
		cashsaving = remcash;
		creditsaving = remincredit;
		cout << "Cash Saving: " << cashsaving << setw(50) << "Credit card Saving: " << creditsaving << endl;
	}	
	else if (remcash < 0 && remincredit >= 0)
	{
		cashdebt = (remcash*-1);
		creditsaving = remincredit;
		cout << "Cash Debt: " << cashdebt << setw(50) << "Credit card Saving: " << creditsaving << endl;
	}
	else if (remcash >= 0 && remincredit < 0)
	{
		creditdebt = (remincredit*-1);
		cashsaving = remcash;
		cout << "Cash Saving: " << cashsaving << setw(50) << "Credit card Debt: " << creditdebt << endl;
	}
	else
	{
		creditdebt = (remincredit*-1);
		cashdebt = (remcash*-1);
		cout << "Cash Debt: " << cashdebt << setw(50) << "Credit card Debt: " << creditdebt << endl;
	}
	cout << endl << "*******************************************************************************" << endl << endl;
}
string checkenteredwallet()
{
	bool flag = false;
	string wallet;
	do {
		cin >> wallet;
		transform(wallet.begin(), wallet.end(), wallet.begin(), ::tolower);
		if (wallet == "cash" || wallet == "credit")
			flag = true;
		else
			cout << "You have to enter either cash or credit as wallet for this expens: ";

	} while (flag == false);

	return wallet;
}
int enterMonth()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	bool flag = false;
	int month;
	do {
		cin >> month;
		if (month == 0)
		{
			month = 1 + ltm->tm_mon;
			flag = true;
		}
		else if (month > 12 || month < 0)
		{
			cout << "You can enter from 0 to 12 only!!!" << endl;
			cout << "Enter 0 for current month or Enter month: ";
		}
		else
			flag = true;
	} while (flag == false);

	return month;
}
int enterYear()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int year;
	cin >> year;
	if (year == 0)
		year = 1900 + ltm->tm_year;

	return year;
}
int enterDay(int month, int year)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	bool flag = false;
	int day;
	string monthname = MonthName(month);
	do {
		cin >> day;
		if (day == 0)
		{
			day = ltm->tm_mday;
			flag = true;
		}
		else if ((year % 4 == 0) && (year % 100 != 0) && day > 29 && month == 2)
		{
			cout << "Its a leap year and month is " << monthname << " !!" << endl;
			cout << "You can enter 0 for today's day or from (1 to 29): ";
		}
		else if (!(year % 4 == 0) && (year % 100 != 0) && day > 28 && month == 2)
		{
			cout << "Its a normal year and month is " << monthname <<" !!"<<endl;
			cout << "You can enter 0 for today's day or from (1 to 28): ";
		}
		else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
		{
			cout << "Its " << monthname << "!!" << endl;
			cout << "You can enter 0 for today's day or from (1 to 30): ";
		}
		else if (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
		{
			cout << "Its " << monthname << "!!" << endl;
			cout << "You can enter 0 for today's day or from (1 to 31): ";
		}
		else if (day < 0)
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				cout << "You can enter 0 for today's day or from (1 to 31): ";
			else if (month == 4 || month == 6 || month == 9 || month == 11)
				cout << "You can enter 0 for today's day or from (1 to 30): ";
		}
		else
			flag = true;

	} while (flag == false);
	return day;
}
float checkamount()
{
	float amount;
	bool flag = false;
	
	do {
		cin >> amount;
		if (amount >= 0)
			flag = true;
		else
			cout << "Enter Postive Amount: ";
	
	} while (flag == false);

	return amount;
}
string MonthName(int month)
{
	string monthname;
	switch (month)
	{
	case 1:
		monthname = "January";
		break;
	case 2:
		monthname = "February";
		break;
	case 3:
		monthname = "March";
		break;
	case 4:
		monthname = "April";
		break;
	case 5:
		monthname = "May";
		break;
	case 6:
		monthname = "June";
		break;
	case 7:
		monthname = "July";
		break;
	case 8:
		monthname = "August";
		break;
	case 9:
		monthname = "September";
		break;
	case 10:
		monthname = "October";
		break;
	case 11:
		monthname = "November";
		break;
	case 12:
		monthname = "December";
		break;
	}
	return monthname;
}