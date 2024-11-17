#pragma once
// UI layer
#include"clScreen.h"
#include"clCurrency.h"
#include"InputValidate.h"
#include<iomanip>
class clCurrencyCalculatorScreen :protected clScreen
{
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
    static clCurrency _getCurrency(string message) {
        string currencyCode;
        cout << message;
        currencyCode = InputValidate::ReadString();
        while (!clCurrency::isExist(currencyCode))
        {
            cout << "Not exist, enter another currency code: ";
            currencyCode = InputValidate::ReadString();
        }
        clCurrency currency = clCurrency::FindByCode(currencyCode);
        return currency;
    }
    static void _printResults(clCurrency currency1, clCurrency currency2, double amount) {
        cout << "Convert From:\n";
        _printCurrency(currency1);
        cout << amount << " " << currency1.CurrencyCode() << " = " << currency1.ToUSD(amount) << " USD \n";
        cout << "\n_____________________________\n";
        if (currency2.CurrencyCode() == "USD")
            return;
        cout << "Convert To:\n";
        _printCurrency(currency2);
        cout << amount << " " << currency1.CurrencyCode() << " = " << currency1.ToAnotherCurrency(amount, currency2) << 
            currency2.CurrencyCode()<<endl;
        cout << "\n_____________________________\n";
    }
public:
    static void ShowCurrencyCalcSreen() {
        char ans = 'n';
        do
        {
            system("cls");
            _drawScreenHeader("Currency Calculator Screen");
            clCurrency currency1 = _getCurrency("Enter currency code 1: ");
            clCurrency currency2 = _getCurrency("Enter currency code 2: ");
            double amount = 0;
            amount = InputValidate::ReadPositiveDouble("Enter amount to exchange: ");
            _printResults(currency1, currency2, amount);
            cout << "Do you want to perform another calculation?y/n?";
                cin >> ans;
        } while (tolower(ans) == 'y');
    }
};

