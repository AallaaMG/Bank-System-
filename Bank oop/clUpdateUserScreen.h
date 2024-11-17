#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clUser.h"
class clUpdateUserScreen :protected clScreen

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
	static void _printUserInfo(clUser user)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName       : " << user.FirstName;
		cout << "\nLastName        : " << user.LastName;
		cout << "\nFull Name       : " << user.FullName();
		cout << "\nEmail           : " << user.Email;
		cout << "\nPhone           : " << user.Phone;
		cout << "\nUsername        : " << user.UserName;
		cout << "\nPassword        : " << user.Password;
		cout << "\nPermissions     : " << user.Permissions;
		cout << "\n___________________\n";
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
	static void Update()
	{
		_drawScreenHeader("\tUpdate User Screen");
		cout << "Enter username:";
		string username = InputValidate::ReadString();
		while (!clUser::isExist(username))
		{
			cout << "Username not found, Enter another username:";
			username = InputValidate::ReadString();

		}
		clUser user = clUser::Find(username);
		_printUserInfo(user);
		cout << "Enter Updates: \n";
		_readUserInfo(user);
		cout << "\nAre you sure you want to save these updates?y/n?";
		char ans = 'n';
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			clUser::enSaveRes Result = user.Save();
			switch (Result)
			{
			case clUser::failedEmpty:
			{
				cout << "\nError! it's empty.\n";
				break;
			}
			case clUser::failedInUse:
			{
				cout << "\nError! username in use.\n";
				break;
			}
			case clUser::succ:
			{
				_printUserInfo(user);
				cout << "\nUpdated successfully :)\n";
				break;
			}
			}
		}
		else
			cout << "Operation cancelled.\n";


	}

};

