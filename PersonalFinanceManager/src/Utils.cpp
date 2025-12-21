#include <iostream>
#include <string>
#include <limits>

#include "Utils.h"

using namespace std;


bool isLeapYear(int y) {
    if (y < 1) return false;
    return (y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0));
}

int daysInMonth(int m, int y) {
    if (m < 1 || m > 12) return 0;
    switch (m) {
    case 1:  return 31;
    case 2:  return isLeapYear(y) ? 29 : 28;
    case 3:  return 31;
    case 4:  return 30;
    case 5:  return 31;
    case 6:  return 30;
    case 7:  return 31;
    case 8:  return 31;
    case 9:  return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: return 0;
    }
}

bool validDate(const Date& date) {
    if (date.year < 1) return false;     
    if (date.month < 1 || date.month > 12) return false;
    int dim = daysInMonth(date.month, date.year);
    if (dim == 0) return false;   
    if (date.day < 1 || date.day > dim) return false;
    return true;
}


void readDate(Date& d) {
    while (true) {
        cout << "Please enter day, month, year respectively (dd mm yyyy): ";
        cin >> d.day >> d.month >> d.year;

        if (cin.fail()) {
            cout << "Invalid input format! Please enter integers (e.g., 31 12 2025).\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        if (!validDate(d)) {
            cout << "The date is not valid! Please try again.\n";
            continue;
        }
        break;

    }
}

void printDate(const Date d) {
	cout << d.day << "/" << d.month << "/" << d.year << endl;
}

int compareDate(Date a, Date b) { //a sớm hơn b là 1,-1 là ngược lại và a trùng b là 1
	if (a.year > b.year) return -1;
	else if (a.year < b.year) return 1;
	else {
		if (a.month > b.month) return -1;
		else if (a.month < b.month) return 1;
		else {
			if (a.day > b.day) return -1;
			else if (a.day < b.day)  return 1;
			else return 0;
		}
	}
}

bool isDateInRange(Date d, Date from, Date to) {
	int isGreaterOrEqual = compareDate(from, d);
	int isLessOrEqual = compareDate(d, to);
	if (isGreaterOrEqual != -1 && isLessOrEqual != -1) return true;
	else return false;
}

bool isSameMonthYear(Date d, int m, int y) {
	return (d.month == m && d.year == y);
}
int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        else {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double readDouble(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        else {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}
