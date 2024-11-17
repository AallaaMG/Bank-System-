#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
class clUpdateClientScreen :protected clScreen
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
		cout << "\nPincode    : " << client.PinCode;
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";
	}
	static void _readClientInfo(clBankClient& client)
	{
		cout << "\nEnter FirstName: ";
		client.FirstName = InputValidate::ReadString();

		cout << "\nEnter LastName: ";
		client.LastName = InputValidate::ReadString();

		cout << "\nEnter Email: ";
		client.Email = InputValidate::ReadString();

		cout << "\nEnter Phone: ";
		client.Phone = InputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		client.PinCode = InputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		client.AccountBalance = InputValidate::ReadDouble("Enter a Validate number");
	}
public:
	static void Update()
	{
		if (!CheckAccessRight(clUser::pUpdateClient))
			return;
		_drawScreenHeader("\tUpdate Client Screen");
		cout << "Enter Account Number: ";
		string accNo = InputValidate::ReadString();
		while (!clBankClient::isExist(accNo))
		{
			cout << "This Account Number does not exist,Enter another Account Number: ";
			accNo = InputValidate::ReadString();
		}
		clBankClient Client = clBankClient::Find(accNo);
		_printClientInfo(Client);
		cout << "\n____________________\n";
		cout << "\nUpdate Client Info:";
		cout << "\n____________________\n";

		_readClientInfo(Client);
		clBankClient::enSaveRes Result = Client.Save();
		switch (Result)
		{
		case clBankClient::enSaveRes::failedEmpty:
		{
			cout << "\nError account was not saved because it's Empty!.";
			break;

		}
		case clBankClient::enSaveRes::succ:
		{
			cout << "Updated successfully :)\n";
			break;
		}
		}
	}
};

