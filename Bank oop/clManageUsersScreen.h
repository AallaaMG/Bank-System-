#pragma once
// UI layer
#include"clScreen.h"
#include"clUserListScreen.h"
#include"clAddNewUserScreen.h"
#include"clDeleteUserScreen.h"
#include"clUpdateUserScreen.h"
#include"clFindUserScreen.h"
#include"InputValidate.h"
#include<iomanip>
class clManageUsersScreen :protected clScreen
{
private:
	enum enManageUsersOption {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};
	static enManageUsersOption _readManageUsersOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		int choice = InputValidate::ReadIntBetween(1,6,"Please Enter number between 1 and 4...");
		return enManageUsersOption(choice);
	}
	static void _showListUsersScreen() {
		clUserListScreen::ShowUsersList();
	}
	static void _showAddNewUserScreen() {
		clAddNewUserScreen::AddNew();
	}
	static void _showDeleteUserScreen() {
		clDeleteUserScreen::Delete();
	}
	static void _showUpdateUserScreen() {
		clUpdateUserScreen::Update();
	}
	static void _showFindUserScreen() {
		clFindUserScreen::FindScreen();
	}
	static void _goBackToManageUsersMenu() {
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUsersMenu();
	}
	static void _performManageUsersOption(enManageUsersOption option)
	{
		
			switch (option)
			{
			case clManageUsersScreen::eListUsers:
			{
				system("cls");
				_showListUsersScreen();
				_goBackToManageUsersMenu();
				break;
			}
			case clManageUsersScreen::eAddNewUser:
			{
				system("cls");
				_showAddNewUserScreen();
				_goBackToManageUsersMenu();
				break;
			}
			case clManageUsersScreen::eDeleteUser:
			{
				system("cls");
				_showDeleteUserScreen();
				_goBackToManageUsersMenu();
				break;
			}
			case clManageUsersScreen::eUpdateUser:
			{
				system("cls");
				_showUpdateUserScreen();
				_goBackToManageUsersMenu();
				break;
			}
			case clManageUsersScreen::eFindUser:
			{
				system("cls");
				_showFindUserScreen();
				_goBackToManageUsersMenu();
				break;
			}
			case clManageUsersScreen::eMainMenu:
			{
			
			}
			}
	}
public:
	static void ShowManageUsersMenu() {
		if (!CheckAccessRight(clUser::pManageUsers))
			return;
		system("cls");
		_drawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performManageUsersOption(_readManageUsersOption());
	}
};

