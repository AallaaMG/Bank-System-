#pragma once
// UI layer
#include"global.h"
#include"clUser.h"
#include"clScreen.h"
#include"clCleintListScreen.h"
#include"clAddNewClientScreen.h"
#include"clDeleteClientScreen.h"
#include"clUpdateClientScreen.h"
#include"clFindClientScreen.h"
#include"clTransactionsScreen.h"
#include"clManageUsersScreen.h"
#include"clRegisterLoginScreen.h"
#include"clCurrencyExchangeMainMenu.h"
#include <iomanip>

class clShowMainMenuScreen :protected clScreen
{
private:
	enum enMainMenuOption{eCleintsList=1,eAddNewClient=2,eDeleteClient=3,
		eUpdateClient=4,eFindClient=5,eShowTransactionMenu=6,eManageUsers=7,eShowRegisterLogin=8,eCurrencyExchange,eExit=10};
	static enMainMenuOption _readMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		int choice = InputValidate::ReadIntBetween(1, 10,"Enter from 1 to 10...");
		return enMainMenuOption(choice);
	}
	static void _goBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\t Press any key to go back to main menu...";
		system("pause>0");
		ShowMainMenu();

	}
	static void _showClientsListScreen()
	{
		clClientList::ShowClientList();
	}
	static void _showAddNewClientScreen()
	{
		clAddNewClientScreen::AddNew();
	}
	static void _showDeleteClientScreen()
	{
		clDeleteClientScreen::Delete();
	}
	static void _showUpdateClientScreen()
	{
		clUpdateClientScreen::Update();
	}
	static void _showFindClientScreen()
	{
		clFindClientScreen::FindScreen();
	}
	static void _showTransactionsScreen()
	{
		clTransactionsScreen::ShowTransactionsMenu();
	}
	static void _showManageUsersScreen()
	{
		clManageUsersScreen::ShowManageUsersMenu();
	}
	static void _showRegisterLoginScreen()
	{
		clRegisterLoginScreen::ShowRegisterLoginScreen();
	}
	static void _showCurrencyExchangeScreen()
	{
		clCurrencyExchangeMainMenu::ShowCurrencyMainMenu();
	}
	static void _logout()
	{
		CurrentUser = clUser::Find("", "");
	}
	static void _performMainMenuOption(enMainMenuOption option)
	{
		switch (option)
		{
		case enMainMenuOption::eCleintsList:
		{
			system("cls");
			_showClientsListScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eAddNewClient:
		{
			system("cls");
			_showAddNewClientScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eDeleteClient:
		{
			system("cls");
			_showDeleteClientScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eFindClient:
		{
			system("cls");
			_showFindClientScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eUpdateClient:
		{
			system("cls");
			_showUpdateClientScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eShowTransactionMenu:
		{
			system("cls");
			_showTransactionsScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eManageUsers:
		{
			system("cls");
			_showManageUsersScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eShowRegisterLogin:
		{
			system("cls");
			_showRegisterLoginScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eCurrencyExchange:
		{
			system("cls");
			_showCurrencyExchangeScreen();
			_goBackToMainMenu();
			break;
		}
		case enMainMenuOption::eExit:
		{
			system("cls");
			_logout();
			break;
		}
		}
	}
public:
	static void ShowMainMenu()
	{
		system("cls");
		_drawScreenHeader("\t\tMain Screen");//from base class

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Register Login.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performMainMenuOption(_readMainMenuOption());
	}
};

