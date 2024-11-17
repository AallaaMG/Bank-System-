#pragma once
// UI layer
#include"clScreen.h"
#include"InputValidate.h"
#include"clUser.h"
class clDeleteUserScreen :protected clScreen
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
	static void Delete()
	{
        _drawScreenHeader("\tDelete User Screen");
        cout << "Enter Username: ";
        string username = InputValidate::ReadString();
        while (!clUser::isExist(username))
        {
            cout << "This Username does not exist,Enter another Username: ";
            username = InputValidate::ReadString();
        }
        clUser user = clUser::Find(username);
        _printUserInfo(user);
        char ans = 'n';
        cout << "Are you sure to delete this user?y/n?";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            if (user.Delete())
            {
                cout << "Deleted successfully :)\n";
                _printUserInfo(user);
            }
            else
            {
                cout << "Error have not been deleted, you can not delete the Admin!.\n";
            }
        }
	}
};

