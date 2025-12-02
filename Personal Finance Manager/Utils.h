#pragma once
#include <iostream>
struct Date {
	int day;
	int month;
	int year;
};

void readDate(Date& d);
void printDate(const Date d);
int compareDate(Date a, Date b); //a s?m h?n b là 1,-1 là ng??c l?i và a trùng b là 1
bool isDateInRange(Date d, Date from, Date to);
bool isSameMonthYear(Date d, int m, int y);