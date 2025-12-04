#include <iostream>
#include "Utils.h"

using namespace std;

void readDate(Date& d) {
	cout << "Please enter day,month,year respectively (dd mm yy)";
	cin >> d.day >> d.month >> d.year;
}

void printDate(const Date d) {
	cout << d.day << "//" << d.month << "//" << d.year << endl;
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
	int isGreaterOrEqual = compareDate(from,d);
	int isLessOrEqual = compareDate(d, to);
	if (isGreaterOrEqual != -1 && isLessOrEqual != -1) return true;
	else return false;
}

bool isSameMonthYear(Date d, int m, int y) {
	return (d.month == m && d.year == y);
}