#pragma once
// UI layer
#include"clScreen.h"
#include"clCurrency.h"
#include"InputValidate.h"
#include<iomanip>
#include"clCurrencyListScreen.h"
#include "clFindCurrencyScreen.h"
#include"clUpdateCurrencyRateScreen.h"
#include"clCurrencyCalculatorScreen.h"

class clCurrencyExchangeMainMenu :protected clScreen
{
private:
	enum eCurrencyOption {
		eListCurrencies=1,eFindCurrency=2,eUpdateRate=3,eCalculator=4,eMainMenu=5
	};
	static eCurrencyOption _readCurrencyMainMenuOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		int choice = InputValidate::ReadIntBetween(1, 5, "Enter from 1 to 5...");
		return eCurrencyOption(choice);
	}
	static void _goBackToCurrencyMainMenu() {
		cout << setw(37) << left << "" << "\t Press any key to go back to currency main menu...";
		system("pause>0");
		ShowCurrencyMainMenu();
	}
	static void _showCurrenciesList() {
		clCurrencyListScreen::ShowCurrenciesListScreen();
	}
	static void _findCurrency() {
		clFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _updateRate() {
		clUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _currencyCalculator() {
		clCurrencyCalculatorScreen::ShowCurrencyCalcSreen();
	}
	static void _performCurrencyMainMenuOp(eCurrencyOption option) {
		switch (option)
		{
		case clCurrencyExchangeMainMenu::eListCurrencies:
		{
			system("cls");
			_showCurrenciesList();
			_goBackToCurrencyMainMenu();
			break;
		}
		case clCurrencyExchangeMainMenu::eFindCurrency:
		{
			system("cls");
			_findCurrency();
			_goBackToCurrencyMainMenu();
			break;
		}
		case clCurrencyExchangeMainMenu::eUpdateRate:
		{
			system("cls");
			_updateRate();
			_goBackToCurrencyMainMenu();
			break;
		}
		case clCurrencyExchangeMainMenu::eCalculator:
		{
			system("cls");
			_currencyCalculator();
			_goBackToCurrencyMainMenu();
			break;
		}
		case clCurrencyExchangeMainMenu::eMainMenu:
		{

		}

		}
	}
public:
	static void ShowCurrencyMainMenu() {
		if (!CheckAccessRight(clUser::enPermissions::pCurrencyExchange))
			return;
		system("cls");
		_drawScreenHeader("Currency Exchange Main Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t     Currency Exchange Main Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Currencies List.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Exchange Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performCurrencyMainMenuOp(_readCurrencyMainMenuOption());
	}
};

