#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clString.h"
class clCurrency
{
private:
	enum mode{ empty=0,update=1};
	mode _mode;
	string _counrtyName;
	string _currencyCode;
	string _currencyName;
	double _rate;
	static clCurrency _convertLineToCurrencyObj(string line) {
		vector<string> vWords = clString::split(line, "#//#");
		return clCurrency(mode::update, vWords[0], vWords[1], vWords[2], stod(vWords[3]));
	}
	static string _converCurrencyObjectToLine(clCurrency Currency, string Seperator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;

	}
	static vector<clCurrency> _loadDataCurrenciesFromFile() {
		vector<clCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		string line;
		if (MyFile.is_open()) {
			while (getline(MyFile, line)) {
				clCurrency currency = _convertLineToCurrencyObj(line);
				vCurrencies.push_back(currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	static void _saveCurrenciesToFile(vector<clCurrency> vCurrencies) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		string line;
		if (MyFile.is_open()) {
			for (clCurrency& C : vCurrencies) {
				line = _converCurrencyObjectToLine(C);
				MyFile << line << endl;
			}
			MyFile.close();
		}
	}
	void _update() {
		vector<clCurrency> vCurrencies=_loadDataCurrenciesFromFile();
			for (clCurrency& C : vCurrencies) {
				if (C.CurrencyCode() == this->CurrencyCode())
				{
					C = *this;
					break;
				}
			}
			_saveCurrenciesToFile(vCurrencies);
	}
	static clCurrency _getEmptyCurrencyObject()
	{
		return clCurrency(mode::empty, "", "", "", 0);
	}
public:
	bool isEmpty() {
		return _mode == mode::empty;
	}
	string Country() {
		return _counrtyName;
	}
	string CurrencyCode() {
		return _currencyCode;
	}
	string CurrencyName() {
		return _currencyName;
	}
	double Rate() {
		return _rate;
	}
	void UpdateRate(double newRate) {
		_rate = newRate;
		_update();
	}
	clCurrency(mode Mode, string CountryName, string CurrencyCode, string CurrencyName, double Rate) {
		_mode=Mode;
		 _counrtyName=CountryName;
		 _currencyCode=CurrencyCode;
		 _currencyName=CountryName;
		 _rate=Rate;
	}
	static clCurrency FindByCode(string Code) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		string line;
		Code = clString::AllStringUpper(Code);
		if (MyFile.is_open()) {
			while (getline(MyFile, line)) {
				clCurrency currency = _convertLineToCurrencyObj(line);
				if (currency.CurrencyCode() == Code)
				{
					MyFile.close();
					return currency;
				}
			 }
			MyFile.close();
			
		}
		return _getEmptyCurrencyObject();
	}
	static clCurrency FindByCountry(string Country) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		Country = clString::AllStringUpper(Country);
		string line;
		if (MyFile.is_open()) {
			while (getline(MyFile, line)) {
				clCurrency currency = _convertLineToCurrencyObj(line);
				if (clString::AllStringUpper(currency.Country()) == Country)
				{
					MyFile.close();
					return currency;
				}
			}
			MyFile.close();

		}
		return _getEmptyCurrencyObject();
	}
	static bool isExist(string CurrencyCode)
	{
		clCurrency C1 = clCurrency::FindByCode(CurrencyCode);
		return (!C1.isEmpty());

	}
	static vector<clCurrency> GetCurrenciesList() {
		return _loadDataCurrenciesFromFile();
	}
	double ToUSD(double amount) {
		return amount / Rate();
	}
	double ToAnotherCurrency(double amount, clCurrency currency) {
		return ToUSD(amount) * currency.Rate();

	}
};

