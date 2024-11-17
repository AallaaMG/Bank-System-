#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clUser.h"
#include<iomanip>
class clAddNewUserScreen :protected clScreen
{
private:
	static void _readUserInfo(clUser& user)
	{
		cout << "\nEnter FirstName: ";
		user.FirstName = InputValidate::ReadString();

		cout << "\nEnter LastName: ";
		user.LastName = InputValidate::ReadString();

		cout << "\nEnter Email: ";
		user.Email = InputValidate::ReadString();

		cout << "\nEnter Phone: ";
		user.Phone = InputValidate::ReadString();

		cout << "\nEnter Password: ";
		user.Password = InputValidate::ReadString();
		cout << "\nEnter Permissions: ";
		user.Permissions = _readPermissions();

	
	}
	static int _readPermissions()
	{
		int permissions = 0;
		char ans = 'n';
		cout << "Do you want to give this user full access?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			return -1;

		cout << "Do you want to give this user access to show client list?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::epListClients;

		cout << "Do you want to give this user access to add new client?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pAddNewClient;

		cout << "Do you want to give this user access to delete client?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pDeleteClient;

		cout << "Do you want to give this user access to update client?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pUpdateClient;

		cout << "Do you want to give this user access to find client?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pFindClient;

		cout << "Do you want to give this user access to Transactions menu?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pTransactions;

		cout << "Do you want to give this user access to Manage Users menu?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pManageUsers;
		cout << "Do you want to give this user access to Register Login List?y/n?";
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
			permissions += clUser::enPermissions::pRegisterLogin;
		if (permissions == 255)
			permissions = -1;
		return permissions;
	
	}
public:
	static void AddNew()
	{
		_drawScreenHeader("\tAdd New User Screen");
		cout << "Enter Username: ";
		string username = InputValidate::ReadString();
		while (clUser::isExist(username))
		{
			cout << "This username exists, Enter another username:";
			username = InputValidate::ReadString();
		}
		clUser NewUser = clUser::GetAddNewUserObject(username);
	    _readUserInfo(NewUser);
		clUser::enSaveRes Result = NewUser.Save();
		switch (Result)
		{
		case clUser::enSaveRes::failedEmpty:
		{
			cout << "\nError user was not saved because it's Empty!.\n";
			break;

		}
		case clUser::enSaveRes::failedInUse:
		{
			cout << "\nError username in use!.\n";
			break;
		}
		case clUser::enSaveRes::succ:
		{
			cout << "Added successfully :)\n";
			break;
		}
		}
	}
};

