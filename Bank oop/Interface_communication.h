#pragma once
#include<iostream>
#include<string>
//abstract class
using namespace std;
class Interface_communication
{
public:
	virtual void SendSMS(string Title,string Body) = 0;
	virtual void SendEmail(string Title, string Body) = 0;
};

