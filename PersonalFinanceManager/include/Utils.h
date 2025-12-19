#pragma once
#include <iostream>
#include <string>
using namespace std;
struct Date {
	int day;
	int month;
	int year;
};
bool isLeapYear(int y);
int daysInMonth(int m, int y);
bool validDate(const Date& date);
void readDate(Date& d);
void printDate(const Date d);
int compareDate(Date a, Date b); //a sớm hơn là 1,b sớm hơn là -1,bằng là 0
bool isDateInRange(Date d, Date from, Date to);
bool isSameMonthYear(Date d, int m, int y);
int readInt(const string& prompt);
double readDouble(const string& prompt);
string readLine(const string& prompt);
