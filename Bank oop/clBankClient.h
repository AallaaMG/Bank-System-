#pragma once
//logic layer
#include<iostream>
#include"clDate.h"
#include<string>
#include"clString.h"
#include"clPerson.h"
#include<fstream>
#include"clUser.h"
#include"global.h"
using namespace std;

class clBankClient :public clPerson
{
private:
	enum enMode { update = 1, empty = 0 ,addNew=2};
	enMode _mode;
	string _accountNumber;//read only
	string _pinCode;
	double _accountBalance;
	bool _markForDelete = false;
	struct transferRecord;
	static clBankClient _convertLineToClient(string line, string separator = "#//#")
	{
		vector<string> vWords = clString::split(line, separator);
		return clBankClient(enMode::update, vWords[0], vWords[1], vWords[2], vWords[3], vWords[4], vWords[5], stod(vWords[6]));
	}
	static string _convertClientToLine(clBankClient client, string separator = "#//#")
	{
		string record = "";
		record = client.FirstName +separator ;
		record += client.LastName +separator;
		record += client.Email + separator;
		record += client.Phone + separator;
		record += client.AccountNumber() + separator;
		record += client.PinCode + separator;
		record += to_string(client.AccountBalance);
		return record;
	}
	static vector<clBankClient> _loadDataFromFile()
	{
		vector<clBankClient> vClients;
		string Line;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clBankClient client = _convertLineToClient(Line);
				vClients.push_back(client);
			}
			MyFile.close();
		}
		return vClients;
	}
	static void _saveDataClientsToFile(vector<clBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite mode
		if (MyFile.is_open())
		{
			for (clBankClient& c : vClients)
			{
				if (!c.MarkForDelete)
				{
					string line = _convertClientToLine(c);
					MyFile << line << endl;
				}
			}
			MyFile.close();
		}
	}
	void _addDataLineToFile(string  DataLine,string fileName)
	{
		fstream MyFile;
		MyFile.open(fileName, ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}

	}
	string _createTransferLogLine(double amount, clBankClient Client2,string username,string separator="#//#") {
		string DataLine = "";
		DataLine = clDate::GetSystemDateTimeString()+separator;
		DataLine+= this->AccountNumber() + separator;
		DataLine+= Client2.AccountNumber() + separator;
		DataLine+=to_string(amount) + separator;
		DataLine += to_string(this->AccountBalance) + separator;
		DataLine += to_string(Client2.AccountBalance) + separator;
		DataLine += username;
		return DataLine;
	}
	static transferRecord _convertLineToTransferRecord(string line) {
		vector<string> vWords = clString::split(line, "#//#");
		transferRecord record;
		record.date = vWords[0];
		record.sourceAccNo = vWords[1];
		record.distinationAccNo = vWords[2];
		record.amount = vWords[3];
		record.sourceAccBalance = vWords[4];
		record.distinationAccBalance = vWords[5];
		record.username = vWords[6];
		return record;
	}
	void _update()
	{
		vector<clBankClient> vClients = _loadDataFromFile();//old data
		for (clBankClient& c : vClients)
		{
			if (c.AccountNumber() == this->AccountNumber())
				c = *this;//c old data(in file) / *this new data (current obj) //update in vector
		}
		_saveDataClientsToFile(vClients);// update in file
	}
	void _addNew() {
		_addDataLineToFile(_convertClientToLine(*this), "Clients.txt");
	}
	
	static clBankClient _getEmptyClient()
	{
		return clBankClient(enMode::empty, "","","", "","","",0);
	}
public:
	struct transferRecord {
		string date, sourceAccNo, distinationAccNo, amount, sourceAccBalance, distinationAccBalance, username;
	};
	clBankClient(enMode mode, string first, string last, string email, string phone, string accountNum, string pinCode, double accountBalance)
		:clPerson(first, last, email, phone)

	{
		_mode=mode;
		_accountNumber=accountNum;
		_pinCode=pinCode;
		_accountBalance=accountBalance;
	}
	bool isEmpty()
	{
		return _mode == enMode::empty;
	}
	string AccountNumber() {
		return _accountNumber;
	}
	void setPinCode(string pinCode)
	{
		_pinCode = pinCode;
	}
	string GetPinCode() {
		return _pinCode;
	}
	__declspec(property(get = GetPinCode, put = setPinCode))string PinCode;
	void setMarkForDelete(bool mark)
	{
		_markForDelete =mark;
	}
	bool GetMarkForDelete() {
		return _markForDelete;
	}
	__declspec(property(get = GetMarkForDelete, put = setMarkForDelete))bool MarkForDelete;

	void setAccountBalance(double accountBalance)
	{
		_accountBalance = accountBalance;
	}
	double GetAccountBalance() {
		return _accountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = setAccountBalance))double AccountBalance;
	static clBankClient Find(string accNo)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clBankClient client = _convertLineToClient(line);
				if (client.AccountNumber() == accNo)
				{
					MyFile.close();
					return client;
				}
			}
		    MyFile.close();
		}
		return _getEmptyClient();
	}
	static clBankClient Find(string accNo,string pinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clBankClient client = _convertLineToClient(line);
				if (client.AccountNumber() == accNo && client.PinCode==pinCode)
				{
					MyFile.close();
					return client;//_mode update
				}
			}
			MyFile.close();
		}
		return _getEmptyClient();//_mode empty
	}
	enum enSaveRes{failedEmpty=0,failedInUse=1,succ=2};
	enSaveRes Save()
	{
		if (_mode == enMode::empty)
			return enSaveRes::failedEmpty;
		if (_mode == enMode::update)
		{
			_update();
			return enSaveRes::succ;
		}
		if (_mode == enMode::addNew)
		{
			if (clBankClient::isExist(this->AccountNumber()))
			{
				return enSaveRes::failedInUse;
			}
			else
			{
				_addNew();
				_mode = enMode::update;
				return enSaveRes::succ;
			}
		}
	}
	static bool isExist(string accNo)
	{
		clBankClient client = Find(accNo);
		return (!client.isEmpty());
	}
	static clBankClient GetNewClient(string accountNo)
	{
		return clBankClient(enMode::addNew, "", "", "", "", accountNo, "", 0);
	}
	 bool Delete()
	{
		vector <clBankClient> vClients = _loadDataFromFile();
		for (clBankClient& c : vClients)
		{
			if (c.AccountNumber() == this->AccountNumber())
			{
				c.MarkForDelete = true;

			}
		}
		_saveDataClientsToFile(vClients);
		*this = _getEmptyClient();
		return true;
	}
	 static vector<clBankClient> GetClientsList()
	 {
		 return _loadDataFromFile();
	 }
	 static double TotalBalances()
	 {
		 vector <clBankClient> vClients = _loadDataFromFile();
		 double total = 0;
		 for (clBankClient& c : vClients)
		 {
			 total += c.AccountBalance;
		 }
		 return total;
	 }
	 void Deposit(double amount)
	 {
		_accountBalance += amount;
		Save();
	 }
	 bool Withdraw(double amount)
	 {
		 if (amount <= (_accountBalance - 5))
		 {
			 _accountBalance -= amount;
			 Save();
			 return true;
		 }
		 else
			 return false;
	 }
	 bool TransferTo(double amount, clBankClient &Client2,string username)
	 {
		 if (Withdraw(amount))//from client1(current object)which called this method
		 {
			 Client2.Deposit(amount);
			 _addDataLineToFile(_createTransferLogLine(amount, Client2,username), "TransferLog.txt");
			 return true;
		 }
		 return false;
	 }
	 static vector<transferRecord> GetTransferLogList()
	 {
		 vector<transferRecord> vRecords;
		 string DataLine;
		 fstream MyFile;
		 MyFile.open("TransferLog.txt", ios::in);
		 if (MyFile.is_open())
		 {
			 while (getline(MyFile, DataLine))
			 {
				 vRecords.push_back(_convertLineToTransferRecord(DataLine));
			 }
			 MyFile.close();
		 }
		 return vRecords;
	 }
};