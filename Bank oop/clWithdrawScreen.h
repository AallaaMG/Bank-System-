#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
class clWithdrawScreen :protected clScreen
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
	static void ShowWithdrawScreen()
	{
		_drawScreenHeader("\t   Withdraw Screen");
		cout << "Enter account number:";
		string AccNo = InputValidate::ReadString();
		while (!clBankClient::isExist(AccNo))
		{
			cout << "Does not exist, Enter another account number:";
			AccNo = InputValidate::ReadString();
		}
		clBankClient client = clBankClient::Find(AccNo);
		_printClientInfo(client);
		double amount = InputValidate::ReadPositiveDouble("Enter the amount to withdraw:");
		cout << "\nAre you sure to perform this operation?y/n?";
		char ans = 'n';
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			if (client.Withdraw(amount))
			{
				cout << "\nDone successfully, new balance is " << client.AccountBalance << endl;
				string Title = "Transaction Operation";
				string Subject = "Our dear Client, ";
				Subject += client.FirstName;
				Subject += ",\n We inform you that there a withdraw opertion that have been done with your account,";
				Subject += "in time: "+clDate::GetSystemDateTimeString();
				Subject += "\nand amount " + to_string(amount);
				Subject += ", your new balance is "+to_string(client.AccountBalance);
				Subject +=".\nThanks for using our Bank's Services, if you have any inquires contact our customer services on this number: ";
				Subject += "123456789.";
				cout << "Message and Email have been sent.\n";
				client.SendSMS(Title,Subject);
				client.SendEmail(Title, Subject);
			}

			else
				cout << "\nAmount exceeds the balance, you can withdraw up to" << client.AccountBalance - 5 << endl;
		}
		else
		{
			cout << "\nCancelled.\n";
		}
	}
};

