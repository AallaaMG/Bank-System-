#pragma once
#include<iostream>
#include"Interface_communication.h"
using namespace std;
class clPerson :public Interface_communication
{
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;
public:
	clPerson(string first, string last, string email, string phone)
	{
		_firstName = first;
	    _lastName=last;
		_email=email;
		_phone=phone;
	}
	void setFirstName(string first)
	{
		_firstName = first;
	}
	string getFirstName()
	{
		return _firstName;
	}
	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	void setLastName(string last)
	{
		_lastName = last;
	}
	string getLastName()
	{
		return _lastName;
	}
	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	void setEmail(string email)
	{
		_email = email;
	}
	string getEmail()
	{
		return _email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string Email;

	void setPhone(string phone)
	{
		_phone = phone;
	}
	string getPhone()
	{
		return _phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string Phone;
	string FullName()
	{
		return _firstName + " " + _lastName;
	}
	void SendSMS(string Title, string Body) {
		cout << "________________________________________________\n";
		cout << "Send to number: " << _phone << "\n";
		cout << "Title: " << Title << "\n";
		cout << "Sublect: " << flush<<Body << "\n";
		cout << "________________________________________________\n\n";
	}
	void SendEmail(string Title, string Body) {
		cout << "________________________________________________\n";
		cout << "Send to email: " << _email << "\n";
		cout << "________________________________\n";
		cout << "Title: " << Title << "\n";
		cout << "________________________________\n";
		cout << "Sublect: " << flush<<Body << "\n";
		cout << "________________________________________________\n\n";
	}
};

