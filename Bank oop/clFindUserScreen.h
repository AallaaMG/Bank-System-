#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clUser.h"
class clFindUserScreen :protected clScreen
{
private:
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
public:
	static void FindScreen()
	{
		_drawScreenHeader("\tFind User Screen");
		cout << "Enter username:";
		string username = InputValidate::ReadString();
		while (!clUser::isExist(username))
		{
			cout << "Username not found, Enter another username:";
			username = InputValidate::ReadString();

		}
		clUser user = clUser::Find(username);
		if (user.isEmpty())
			cout << "\nError it's empty user!.";
		else
		{
			cout << "\nFound successfully :)\n";
			_printUserInfo(user);
		}
	}
};

