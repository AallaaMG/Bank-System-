#pragma once
// UI layer
#include"clScreen.h"
#include"clCurrency.h"
#include"InputValidate.h"
#include<iomanip>
class clFindCurrencyScreen : protected clScreen
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
    static void _showResults(clCurrency currency) {
        if (!currency.isEmpty()) {
            cout << "Currency found :)\n";
            _printCurrency(currency);
        }
        else
        {
            cout << "Currency not found :(\n";
        }
    }
public:
    static void ShowFindCurrencyScreen()
    {

        _drawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = InputValidate::ReadString();
            clCurrency Currency = clCurrency::FindByCode(CurrencyCode);
            _showResults(Currency);
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = InputValidate::ReadString();
            clCurrency Currency = clCurrency::FindByCountry(Country);
            _showResults(Currency);
        }
    }

};

