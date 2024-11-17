#pragma once
// UI layer
#include"InputValidate.h"
#include"global.h"
#include"clUSer.h"
#include"clScreen.h"
#include"clShowMainMenuScreen.h"
class clLoginScreen :protected clScreen
{
private:
	static bool _login()
	{
		bool loginFailed =false;
		string password, username;
		int tries =2;
		do
		{
			cout << "Enter username: ";
			username = InputValidate::ReadString();
			cout << "Enter password: ";
			password = InputValidate::ReadString();
			CurrentUser = clUser::Find(username, password);
			loginFailed = CurrentUser.isEmpty();
			if (tries == 0)
			{
				cout << "You have been blocked from the system after 3 failed trials!\n";
				return false;
			}
			if (loginFailed)
			{
				
				cout << "Invalid username / password!, you have " << tries << " trial(s) left...\n";
				tries--;

			}

		} while (loginFailed);
		CurrentUser.RegisterLogin();
		clShowMainMenuScreen::ShowMainMenu();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_drawScreenHeader("\tLogin Screen");
		return _login();
	}
};

