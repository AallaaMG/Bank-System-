#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
class clDeleteClientScreen:protected clScreen
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
    static void Delete()
    {
        if (!CheckAccessRight(clUser::pDeleteClient))
            return;
        _drawScreenHeader("\tDelete Client Screen");
        cout << "Enter Account Number: ";
        string accNo = InputValidate::ReadString();
        while (!clBankClient::isExist(accNo))
        {
            cout << "This Account Number does not exist,Enter another Account Number: ";
            accNo = InputValidate::ReadString();
        }
        clBankClient Client = clBankClient::Find(accNo);
        _printClientInfo(Client);
        char ans = 'n';
        cout << "Are you sure to delete this client?y/n?";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            if (Client.Delete())
            {
                cout << "Deleted successfully :)\n";
                _printClientInfo(Client);
            }
            else
            {
                cout << "Error have not been deleted!.\n";
            }
        }

    }
};

