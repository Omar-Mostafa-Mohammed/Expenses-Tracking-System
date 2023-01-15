#include "user.h"
void main()
{
	system("color 17");
	string name;
	wallet wal;
	int month, year;
	cout << "*******************************************************************************" << endl << endl;
	cout << setw(40) << "Your Information" << endl << endl;
	cout << "*******************************************************************************" << endl << endl;
	cout << "Enter Your Name: ";
	cin >> name;
	cout << "Enter Your cash Money: ";
	wal.cash = checkamount();
	cout << "Enter Your Money in Credit card: ";
	wal.credit = checkamount();
	cout << "Enter Month or Enter 0 for current Month: ";
	month = enterMonth();
	cout << "Enter Year or Enter 0 for current Year: ";
	year = enterYear();
	user myuser(name, wal, month, year);
	int ch;
	int day;
	float amount;
	string category, wallet;
	expensedata myexpen;
	ArrList<expensedata> expenses;
	while (true)
	{
		system("CLS");
		myuser.userinterface(expenses);
		ch = myuser.Mainmenu();
		switch (ch)
		{
		case 1:
			system("CLS");
			cout << "*******************************************************************************" << endl << endl;
			cout << setw(45) << "Expens's Information" << endl << endl;
			cout << "*******************************************************************************" << endl << endl;
			cout << "Enter Cost of Expens: ";
			amount = checkamount();
			cout << "Enter Category of Expens: ";
			cin >> category;
			cout << "Enter Wallet of Expens (cash or credit): ";
			wallet = checkenteredwallet();
			cout << "Enter Day of Expens 0 for today or Enter day: ";
			day = enterDay(month, year);
			transform(category.begin(), category.end(), category.begin(), ::tolower);
			myexpen = expensedata(amount, category, day, month, year, wallet);
			expenses.Append(myexpen);
			cout << setw(45) << "Expens Added !!!" << endl << endl;
			myuser.continuemsg();
			break;
		case 2:
			myuser.Displaymenu(expenses);
			break;
		case 3:
			myuser.RemMoneymenu(expenses);
			myuser.continuemsg();
			break;
		case 4:
			myuser.Caldebtsaving(expenses);
			myuser.continuemsg();
			break;
		case 5:
			myuser.writetxtfile(expenses);
			myuser.continuemsg();
			break;
		case 6:
			exit(0);
			break;
		}
	}
	system("pause");
}