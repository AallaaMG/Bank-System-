#pragma once
// UI layer
#include<iostream>
#include <iomanip>
#include"global.h"
#include"clUser.h"
#include"clScreen.h"
using namespace std;
class clRegisterLoginScreen :protected clScreen
{
private:
	static void _printRecordDataLine(clUser::registerRecord record)
	{
		cout << setw(8) << left << "" << "|";
		cout << setw(35) << left << record.date<<"|";
		cout << setw(20) << left << record.username << "|";
		cout << setw(20) << left << record.password << "|";
		cout << setw(20) << left << record.permossions<< "|";
	}
public:
	static void ShowRegisterLoginScreen()
	{
		if (!CheckAccessRight(clUser::enPermissions::pRegisterLogin))
			return;
		vector<clUser::registerRecord> vRecords = clUser::GetRegisterLoginList();
		string title = "\tLogin Register List Screen";
		string subTitle ="\t\t" +to_string(vRecords.size()) + " Record(s)";
		_drawScreenHeader(title,subTitle);
		cout << "\n\t __________________________________________________________________________________________________\n";
		cout << setw(8) << left << "" << "|";
		cout << setw(35) << left << "Date\Time" << "|";
		cout << setw(20) << left << "Username" << "|";
		cout << setw(20) << left <<"Passowrd" << "|";
		cout << setw(20) << left << "Permissions" << "|";
		cout << "\n\t __________________________________________________________________________________________________\n";
		if(vRecords.size()==0)
			cout << setw(8) << left << "" << "No Records available\n";
		for (int i = 0; i < vRecords.size(); i++)
		{
			_printRecordDataLine(vRecords[i]);
			cout << "\n";
		}
		cout << "\n\t __________________________________________________________________________________________________\n";
	}
};

