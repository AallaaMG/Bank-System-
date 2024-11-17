#pragma once
// UI layer
#include"InputValidate.h"
#include"clScreen.h"
#include"clBankClient.h"
class clTransferScreen:protected clScreen
{
private:
	static void _printClientInfo(clBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";
	}
	static string _readAccountNumber(string message) {
		cout << message << endl;
		string accNo;
		getline(cin >> ws, accNo);
		while (!clBankClient::isExist(accNo)) {
			cout << "Not exist, enter again...";
			getline(cin >> ws, accNo);
		}
		return accNo;
	}
	static double _readAmount(clBankClient sourceClient) {
		double amount = 0;
		amount = InputValidate::ReadDouble("Enetr amount to transfer:");
		while (amount > sourceClient.AccountBalance - 5)
		{
			cout << "Amount excceds balance, enter again...\n";
			amount = InputValidate::ReadDouble("Enetr amount to transfer:");
		}
		return amount;
	}
public:
	static void ShowTransferScreen() {
		string Title = "\tTransfer Screen";
		_drawScreenHeader(Title);
		string accNo1, accNo2;
		accNo1 = _readAccountNumber("Enetr account number to transfer from:");
		clBankClient Client1 = clBankClient::Find(accNo1);
		_printClientInfo(Client1);
		accNo2 = _readAccountNumber("Enetr account number to transfer To:");
		clBankClient Client2 = clBankClient::Find(accNo2);
		_printClientInfo(Client2);
		double amount = _readAmount(Client1);
		char ans = 'n';
		cout << "Are you sure you want to perform this operation?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			if(Client1.TransferTo(amount, Client2,CurrentUser.UserName))
			{
				cout << "Done successfully :)\n";
				_printClientInfo(Client1);
				_printClientInfo(Client2);
				string Title = "Transfer Operation";
				string Subject = "Our dear Client, ";
				Subject += Client1.FirstName;
				Subject += ",\n We inform you that there a transfer opertion that have been done from your account,";
				Subject += "in time: " + clDate::GetSystemDateTimeString();
				Subject += "\nand amount " + to_string(amount);
				Subject += "and to account " + Client2.AccountNumber();
				Subject += ",\n your new balance is " + to_string(Client1.AccountBalance);
				Subject += ".\nThanks for using our Bank's Services, if you have any inquires contact our customer services on this number: ";
				Subject += "123456789.";
				cout << "Message and Email have been sent.\n";
				Client1.SendSMS(Title, Subject);
				Client1.SendEmail(Title, Subject);
				Title = "Transfer Operation";
				Subject = "Our dear Client, ";
				Subject += Client2.FirstName;
				Subject += ",\nWe inform you that there a transfer opertion that have been done to your account,";
				Subject += "in time: " + clDate::GetSystemDateTimeString();
				Subject += "\nand amount " + to_string(amount);
				Subject += "and from account " + Client1.AccountNumber();
				Subject += ",\n your new balance is " + to_string(Client2.AccountBalance);
				Subject += ".\nThanks for using our Bank's Services, if you have any inquires contact our customer services on this number: ";
				Subject += "123456789.";
				Client2.SendSMS(Title, Subject);
				Client2.SendEmail(Title, Subject);
			}
			else cout << "Cancelled\n";
		}
		else cout << "Cancelled\n";
	}
};

