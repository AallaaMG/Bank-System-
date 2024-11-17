#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
class clAddNewClientScreen:protected clScreen
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

		client.AccountBalance = InputValidate::ReadDouble("\nEnter Account Balance : ");
	}
public:
	static void AddNew()
	{
		if (!CheckAccessRight(clUser::pAddNewClient))
			return;
		_drawScreenHeader("\tAdd New Client Screen");
		cout << "Enter Account Number: ";
		string accNo = InputValidate::ReadString();
		while (clBankClient::isExist(accNo))
		{
			cout << "This Account Number in use, Enter another Account Number: ";
			accNo = InputValidate::ReadString();
		}
		clBankClient newClient = clBankClient::GetNewClient(accNo);//empty obj at add new mode
		_readClientInfo(newClient);
		clBankClient::enSaveRes Result = newClient.Save();
		switch (Result)
		{
		case clBankClient::enSaveRes::failedEmpty:
		{
			cout << "\nError account was not saved because it's Empty!.\n";
			break;

		}
		case clBankClient::enSaveRes::failedInUse:
		{
			cout << "\nError account number in use!.\n";
			break;
		}
		case clBankClient::enSaveRes::succ:
		{
			cout << "Added successfully :)\n";
			break;
		}
		}

	}
};

