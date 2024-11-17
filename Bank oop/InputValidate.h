#pragma once
#include <iostream>
#include<iomanip>
#include<string>
using namespace std;
class InputValidate
{
public:
	static bool isNumberBetween(int num, int from, int to)
	{
		return (num >= from && num <= to);
	}
	static bool isNumberBetween(double num, double from, double to)
	{
		return (num >= from && num <= to);
	}
	static int ReadInt(string message)
	{
		int num = 0;

		while (!(cin >> num))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << setw(37) << left << "" << message;
		}
		return num;
	}
	static double ReadDouble(string message)
	{
		double num = 0;
		cout << message;
		while (!(cin >> num))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout <<"Enter a valid input...";
		}
		return num;
	}
	static double ReadPositiveDouble(string message)
	{
		double num = 0;
		num = ReadDouble(message);
		while (num < 0)
		{
			num = ReadDouble("Enter a positive number...");
		}
		return num;
	}
	static int ReadIntBetween(int from, int to, string message)
	{
		int n = 0;
		n = ReadInt("Invalid input,enter again...");
		while (!isNumberBetween(n, from, to))
		{
			cout << setw(37) << left << "" << message;
			n = ReadInt("Invalid input,enter again...");
		}
		return n;

	}
	static int ReadDoubleBetween(double from, double to, string message)
	{
		double n = 0;
		n = ReadInt("Invalid input,enter again...");
		while (!isNumberBetween(n, from, to))
		{
			cout << setw(37) << left << "" << message ;
			n = ReadInt("Invalid input,enter again...");
		}(n<from || n>to);
		return n;

	}
	static string ReadString() {
		string s = "";
		getline(cin >> ws, s);
		return s;
	}
	
};

