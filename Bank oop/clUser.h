#pragma once
//logic layer
#include<iostream>
#include"clDate.h"
#include<string>
#include"clString.h"
#include"clPerson.h"
#include<fstream>
#include"clUtil.h"
using namespace std;
class clUser :public clPerson
{
private:
	enum enMode { update = 1, empty = 0, addNew = 2 };
	enMode _mode;
	string _userName;//read only
	string _password;
	int _Permissions;
	bool _markForDelete = false;
    struct registerRecord;
   
    string _prepareUserLoginRecordLine(string separator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord=clDate::GetSystemDateTimeString();
        LoginRecord+=separator+ UserName + separator;
        LoginRecord+=clUtil::EncryptText(Password) + separator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    }
    static registerRecord _convertLineToRegisterRecord(string line)
    {
        vector<string> vWords = clString::split(line, "#//#");
        registerRecord record;
        record.date = vWords[0];
        record.username = vWords[1];
        record.password = clUtil::DecryptText(vWords[2]);
        record.permossions = vWords[3];
        return record;
    }
    
    static clUser _convertLineToUser(string line, string separator = "#//#")
    {
        vector<string> vWords = clString::split(line, separator);
        return clUser(enMode::update, vWords[0], vWords[1],vWords[2], vWords[3], vWords[4], clUtil::DecryptText(vWords[5]), stoi(vWords[6]));
    }
    static string _convertUserToLine(clUser user, string separator = "#//#")
    {
        string record = "";
        record = user.FirstName + separator;
        record += user.LastName + separator;
        record += user.Email + separator;
        record += user.Phone + separator;
        record += user.UserName + separator;
        record += clUtil::EncryptText(user.Password) + separator;
        record += to_string(user.Permissions);
        return record;
    }
    static vector<clUser> _loadDataFromFile()
    {
        vector<clUser> vUsers;
        string Line;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read mode
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                clUser user = _convertLineToUser(Line);
                vUsers.push_back(user);
            }
            MyFile.close();
        }
        return vUsers;
    }
    static void _saveDataToFile(vector<clUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite mode
        if (MyFile.is_open())
        {
            for (clUser& u: vUsers)
            {
                if (!u.isMarkedForDeleted())
                {
                    string line = _convertUserToLine(u);
                    MyFile << line << endl;
                }
            }
            MyFile.close();
        }
    }
   void _addDataLineToFile(string  DataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << DataLine << endl;

            MyFile.close();
        }
    }
     void _update()
    {
        vector<clUser> vUsers = _loadDataFromFile();
        for (clUser& u : vUsers)
        {
            if (u.UserName == this->UserName)
            {
                u = *this;
                break;
            }
        }
        _saveDataToFile(vUsers);
    }
     void _addNew()
     {
         _addDataLineToFile(_convertUserToLine(*this));
     }
     static clUser _getEmptyUserObject()
     {
         return clUser(enMode::empty, "", "", "", "", "", "", 0);
     }

public:
    enum enPermissions {
        pAll=-1,epListClients=1,pAddNewClient=2,pDeleteClient=4,pUpdateClient=8,pFindClient=16,
        pTransactions=32,pManageUsers=64,pRegisterLogin=128,pCurrencyExchange=256
    };
    struct registerRecord {
        string date, username, password, permossions;
    };
  
	clUser(enMode mode, string first, string last, string email, string phone, string userName, string password, int Permissions)
		:clPerson(first, last, email, phone)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_Permissions = Permissions;
	}
    bool isEmpty()
    {
        return (_mode == enMode::empty);
    }

    bool isMarkedForDeleted()
    {
        return _markForDelete;
    }

    string GetUserName()
    {
        return _userName;
    }

    void SetUserName(string UserName)
    {
        _userName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _password = Password;
    }

    string GetPassword()
    {
        return _password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    static clUser Find(string userName)
    {
        vector<clUser> vUsers = _loadDataFromFile();
        for (clUser& u : vUsers)
            if (u.UserName == userName)
                return u;
        return _getEmptyUserObject();
    }
    static clUser Find(string userName,string password)
    {
        vector<clUser> vUsers = _loadDataFromFile();
        for (clUser& u : vUsers)
            if (u.UserName == userName && u.Password==password)
                return u;
        return _getEmptyUserObject();
    }
   static bool isExist(string userName)
    {
        clUser User =Find(userName);
        return !User.isEmpty();
    }
    enum enSaveRes { failedEmpty = 0, failedInUse = 1, succ = 2 };
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
            if (clUser::isExist(this->UserName))
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

    bool Delete()
    {
        if (this->UserName == "Admin")
            return false;
        vector <clUser> _vUsers;
        _vUsers = _loadDataFromFile();
        for (clUser& U : _vUsers)
        {
            if (U.UserName == this->UserName)
            {
                U._markForDelete = true;
                break;
            }

        }
        _saveDataToFile(_vUsers);

        *this = _getEmptyUserObject();

        return true;

    }

    static clUser GetAddNewUserObject(string UserName)
    {
        return clUser(enMode::addNew, "", "", "", "", UserName, "", 0);
    }

    static vector <clUser> GetUsersList()
    {
        return _loadDataFromFile();
    }
    bool CheckPermission(enPermissions permission)
    {
        if (this->Permissions == enPermissions::pAll)
            return true;
        if ((this->Permissions & permission) == permission)//is permission included in this->permissions?
            return true;
        else
            return false;
    }
    void RegisterLogin()
    {
        string RegisterLoginRecord = _prepareUserLoginRecordLine();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << RegisterLoginRecord << endl;

            MyFile.close();
        }
    }
    static vector<registerRecord> GetRegisterLoginList()
    {
        vector<registerRecord> vRecords;
        string DataLine;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);
        if (MyFile.is_open())
        {
            while (getline(MyFile, DataLine))
            {
                vRecords.push_back(_convertLineToRegisterRecord(DataLine));
            }
            MyFile.close();
        }
        return vRecords;
    }
    
};

