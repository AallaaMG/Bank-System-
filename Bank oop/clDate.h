#pragma warning(disable : 4996)
#pragma once
#include<iostream>
#include"clString.h"
#include<string>
#include<vector>
using namespace std;
class clDate
{
private:
	int _day;
	int _month;
	int _year;

public:
	clDate()
	{
		//get system date
		time_t t = time(0);
		tm* now = localtime(&t);
		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_day = now->tm_mday;
	}
	clDate(string date)
	{
		vector <string> vDate = clString::split(date, "/");
		_day = stoi(vDate[0]);
		_month = stoi(vDate[1]);
		_year = stoi(vDate[2]);
	}
	clDate(int day, int month, int year)
	{
		_day = day;
		_month = month;
		_year = year;
	}
	void setDay(int day)
	{
		_day = day;
	}
	int getDay()
	{
		return _day;
	}
	__declspec(property(get = getDay, put = setDay)) int day;

	void setMonth(int month)
	{
		_month = month;
	}
	int getMonth()
	{
		return _month;
	}
	__declspec(property(get = getMonth, put = setMonth)) int month;

	void setYear(int year)
	{
		_year = year;
	}
	int getYear()
	{
		return _year;
	}
	__declspec(property(get = getYear, put = setYear)) int year;

	void print()
	{
		cout << DateToString() << endl;
	}

	static bool isValidDate(clDate date)
	{
		if (date.day < 1 || date.day>31)
			return false;
		if (date.month < 1 || date.month >12)
			return false;
		int MonthDays = numberOFDaysInMonth(date.month, date.year);
		if (date.day > MonthDays)
			return false;
		return true;
	}
	bool isValidDate()
	{
		return isValidDate(*this);
	}

	static bool isLeapYear(int year)
	{
		return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));

	}
	bool isLeapYear()
	{
		return isLeapYear(_year);
	}

	static int numberOFDaysInYear(int year)
	{
		return (isLeapYear(year) ? 366 : 365);
	}
	static int numberOFHoursInYear(int year)
	{
		return numberOFDaysInYear(year) * 24;

	}
	static int numberOFMinsInYear(int year)
	{
		return numberOFHoursInYear(year) * 60;

	}
	static int numberOFSecsInYear(int year)
	{
		return numberOFMinsInYear(year) * 60;

	}

	static int numberOFDaysInMonth(int month, int year)
	{
		if (month < 1 || month>12)
			return 0;

		short numberOfDays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		return (month == 2 && isLeapYear(year)) ? 29 : numberOfDays[month];

	}
	static int numberOFHoursInMonth(int month, int year)
	{
		return numberOFDaysInMonth(month, year) * 24;

	}
	static int numberOFMinInMonth(int month, int year)
	{
		return numberOFHoursInMonth(month, year) * 60;

	}
	static int  numberOFSecsInMonth(int month, int year)
	{
		return numberOFMinInMonth(month, year) * 60;

	}
	static clDate GetSystemDate()
	{
		int year, month, day;
		time_t t = time(0);
		tm* now = localtime(&t);
		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
		return clDate(day, month, year);
	}
	static string DateToString(clDate date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	string DateToString() {
		return DateToString(*this);
	}
	static string GetSystemDateTimeString()
	{
		//get system date
		time_t t = time(0);
		tm* now = localtime(&t);
		int year = now->tm_year + 1900;
		int month = now->tm_mon + 1;
		int day = now->tm_mday;
		int hour = now->tm_hour;
		int min = now->tm_min;
		int sec = now->tm_sec;
		return (to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " - " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec));
	}
};


