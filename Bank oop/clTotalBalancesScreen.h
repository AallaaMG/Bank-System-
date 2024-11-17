#pragma once
// UI layer
#include"clScreen.h"
#include"clBankClient.h"
#include"clUtil.h"
#include<iomanip>
class clTotalBalancesScreen :protected clScreen
{
private:
   static void _printClientRecordBalanceLine(clBankClient Client)
    {

       cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
       cout << "| " << setw(40) << left << Client.FullName();
       cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public:
   static void ShowTotalBalanceList()
    {
        vector<clBankClient> vClients = clBankClient::GetClientsList();
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
        _drawScreenHeader(Title, SubTitle);
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clBankClient& C : vClients)
            {
                _printClientRecordBalanceLine(C);
                cout << endl;
            }
            cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
            cout << "__________________________\n" << endl;
            double total = clBankClient::TotalBalances();
            cout << setw(8) << left << "" << "\t\t\t\t\t     Total Balances = " << total << endl;
            cout << setw(8) << left << "" << "\t\t\t  ( " << clUtil::NumberToText(total) << ")";

        }
    }
};

