#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
class clFindClientScreen:protected clScreen
{
private:
	static void _printClientInfo(clBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << client.FirstName;
		cout << "\nLastName    : " << client.LastName;
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nEmail       : " << client.Email;
		cout << "\nPhone       : " << client.Phone;
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nPassword    : " << client.PinCode;
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";
	}
public:
	static void FindScreen()
	{
		if (!CheckAccessRight(clUser::pFindClient))
			return;
		_drawScreenHeader("\tFind Client Screen");
		cout << "Enter Account Number: ";
		string accNo = InputValidate::ReadString();
		while (!clBankClient::isExist(accNo))
		{
			cout << "This Account Number does not exist,Enter another Account Number: ";
			accNo = InputValidate::ReadString();
		}
		clBankClient Client = clBankClient::Find(accNo);
		if (Client.isEmpty())
		{
			cout << "\nClient is not found.\n";
		}
		else
		{
			cout << "\nClient is found :)\n";
			_printClientInfo(Client);
		}
		
	}
};

