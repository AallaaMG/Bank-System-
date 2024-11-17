#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include"global.h"
#include"clUSer.h"
#include"clDate.h"
using namespace std;
class clScreen
{
protected:
	static void _drawScreenHeader(string title,string subTitle="")
	{
        clDate date = clDate::GetSystemDate();
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;
        if (subTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        cout << "\t\t\t\t\t User: " << CurrentUser.UserName;
        cout << "\n\t\t\t\t\t Name: " << CurrentUser.FullName();
        cout << "\n\t\t\t\t\t " <<clDate::GetSystemDateTimeString();
        cout << "\n\t\t\t\t\t______________________________________\n\n";
	}
    static bool CheckAccessRight(clUser::enPermissions permission)
    {
        if (!CurrentUser.CheckPermission(permission))
        {
            cout << "\t\t\t\t\t______________________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied!, contact with your Admin.\n";
            cout << "\t\t\t\t\t______________________________________________";
            return false;
        }
        else
            return true;
    }
};

