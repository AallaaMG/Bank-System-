#pragma once
// UI layer
#include"clScreen.h"
#include"clBankClient.h"
#include"clUSer.h"
#include<iomanip>
class clClientList:protected clScreen
{
private:
	static void _printClientRecordLine(clBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public:
    static void ShowClientList()
    {
        if (!CheckAccessRight(clUser::epListClients))
            return;
        vector<clBankClient> vClients = clBankClient::GetClientsList();
        string title = "\tShow Clients List Screen";
        string subTitle = "\t    (" + to_string(vClients.size())+ ") Client(s).";
        _drawScreenHeader(title, subTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
            cout << setw(8) << left << "\n_______________________________________________________";
            cout << setw(8) << left << "_________________________________________\n" << endl;
        }
        else
        {
            for (clBankClient& C : vClients)
            {
                _printClientRecordLine(C);
                cout << endl;
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

        }
    }
};

