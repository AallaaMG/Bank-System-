#pragma once
// UI layer
#include"clScreen.h"
#include"clUser.h"
#include<iomanip>
class clUserListScreen: protected clScreen
{
private:
    static void _PrintUserRecordLine(clUser User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(12) << left << User.Permissions;
        cout << "| " << left;

    }
public:
    static void ShowUsersList()
    {
        vector <clUser> vUsers = clUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t___________________________________________________________";
        cout << "________________________________" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "| " << left;
        cout << setw(8) << left << "" << "\n\t___________________________________________________________";
        cout << "________________________________" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clUser &User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "_____________________________________________________________";
        cout << "______________________________" << endl;
    }

};

