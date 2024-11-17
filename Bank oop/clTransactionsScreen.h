#pragma once
// UI layer
#include"clScreen.h"
#include"clDepositScreen.h"
#include"clWithdrawScreen.h"
#include"clTotalBalancesScreen.h"
#include"InputValidate.h"
#include"clBankClient.h"
#include"clShowMainMenuScreen.h"
#include"clTransferScreen.h"
#include"clTransferLogScreen.h"
class clTransactionsScreen :protected clScreen
{
private:
	enum enTransactionOption {
		eDeposit=1,eWithdraw=2,eShowTotalBalances=3,eTransfer=4,eTransferLog=5,eShowMainMenu=6
	};
	static enTransactionOption _readTransactionOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		int choice = InputValidate::ReadIntBetween(1, 6,"please enter number from 1 to 6 ...");
		return enTransactionOption(choice);
	}
	static void _goBackToTransactionMenu()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}
	static void _showDepositScreen()
	{
		clDepositScreen::ShowDepositScreen();
	}
	static void _showWithdrawScreen()
	{
		clWithdrawScreen::ShowWithdrawScreen();
	}
	static void _showTotalBalancesScreen()
	{
		clTotalBalancesScreen::ShowTotalBalanceList();
	}
	static void _showTransferScreen()
	{
		clTransferScreen::ShowTransferScreen();
	}
	static void _showTransferLogScreen()
	{
		clTransferLogScreen::ShowTransferLogScreen();
	}
	static void _performTransactionsMenuOption(enTransactionOption option)
	{
		switch (option)
		{
		case enTransactionOption::eDeposit:
		{
			system("cls");
			_showDepositScreen();
			_goBackToTransactionMenu();
			break;
		}
		case enTransactionOption::eWithdraw:
		{
			system("cls");
			_showWithdrawScreen();
			_goBackToTransactionMenu();
			break;
		}
		case enTransactionOption::eShowTotalBalances:
		{
			system("cls");
			_showTotalBalancesScreen();
			_goBackToTransactionMenu();
			break;
		}
		case enTransactionOption::eTransfer:
		{
			system("cls");
			_showTransferScreen();
			_goBackToTransactionMenu();
			break;
		}
		case enTransactionOption::eTransferLog:
		{
			system("cls");
			_showTransferLogScreen();
			_goBackToTransactionMenu();
			break;
		}
		case enTransactionOption::eShowMainMenu:
		{
			
		}
		}
	}
public:
	static void ShowTransactionsMenu()
	{
		if (!CheckAccessRight(clUser::pTransactions))
			return;
		system("cls");
		_drawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log List.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performTransactionsMenuOption(_readTransactionOption());
	}
};

