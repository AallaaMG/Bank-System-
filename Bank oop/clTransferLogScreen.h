#pragma once
// UI layer
#include<iostream>
#include <iomanip>
#include"global.h"
#include"clBankClient.h"
#include"clScreen.h"
using namespace std;
class clTransferLogScreen :protected clScreen
{
private:
	static void _printRecordDataLine(clBankClient::transferRecord record)
	{
		cout << setw(8) << left << "" << "|";
		cout << setw(22) << left << record.date << "|";
		cout << setw(10) << left << record.sourceAccNo << "|";
		cout << setw(10) << left << record.distinationAccNo << "|";
		cout << setw(15) << left << record.amount << "|";
		cout << setw(15) << left << record.sourceAccBalance << "|";
		cout << setw(15) << left << record.distinationAccBalance << "|";
		cout << setw(10) << left << record.username << "|";
	}
public:
	static void ShowTransferLogScreen()
	{
		vector<clBankClient::transferRecord> vRecords =clBankClient::GetTransferLogList();
		string title = "\tTransfer Log List Screen";
		string subTitle = "\t\t" + to_string(vRecords.size()) + "Record(s)";
		_drawScreenHeader(title, subTitle);
		cout << "\n\t _______________________________________________________________________________________________________\n";
		cout << setw(8) << left << "" << "|";
		cout << setw(22) << left << "Date\Time" << "|";
		cout << setw(10) << left <<"S.AccoNo" << "|";
		cout << setw(10) << left << "D.AccoNo" << "|";
		cout << setw(15) << left << "Amount" << "|";
		cout << setw(15) << left << "S.Acc Balance" << "|";
		cout << setw(15) << left << "D.Acc Balance" << "|";
		cout << setw(10) << left << "Username" << "|";
		cout << "\n\t _______________________________________________________________________________________________________\n";
		if (vRecords.size() == 0)
			cout << setw(8) << left << "" << "No Records available\n";
		for (int i = 0; i < vRecords.size(); i++)
		{
			_printRecordDataLine(vRecords[i]);
			cout << "\n";
		}
		cout << "\n\t _______________________________________________________________________________________________________\n";
	}
};

