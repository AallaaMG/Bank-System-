#pragma once
// UI layer
#include"clScreen.h"
#include"clCurrency.h"
#include"InputValidate.h"
#include<iomanip>

class clUpdateCurrencyRateScreen : protected clScreen
{
private:
    static void _printCurrency(clCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
public:
    static void ShowUpdateCurrencyRateScreen() {

        _drawScreenHeader("\t  Update Currency Rate Screen");
        string CurrencyCode;
        cout << "\nPlease Enter CurrencyCode: ";
        CurrencyCode = InputValidate::ReadString();
        while (!clCurrency::isExist(CurrencyCode)) {
            cout << "\nNot found, Please Enter another CurrencyCode: ";
            CurrencyCode = InputValidate::ReadString();
        }
        clCurrency Currency = clCurrency::FindByCode(CurrencyCode);
        _printCurrency(Currency);
        cout << "\nUpdating Currency Rate:\n";
        cout << "____________________________\n";
        double newRate;
        newRate = InputValidate::ReadPositiveDouble("Enter new rate: ");
        char ans = 'n';
        cout << "Are you sure you want to perform this operation?y/n?";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            Currency.UpdateRate(newRate);
            cout << "\nUpdateed Successfully :)\n";
        }
        else
            cout << "\nOperation Cancelled.\n";
    }
};

