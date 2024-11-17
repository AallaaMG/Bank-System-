#pragma once
#include<iostream>
#include<vector>
using namespace std;
class clString
{
private:
	string _value;
public:
	clString() {
		_value = "";
	}
	clString(string value) {
		_value = value;
	}
	void set(string value)
	{
		_value = value;
	}
	string getValue() {
		return _value;
	}
	__declspec(property(get = getValue, put = set)) string value;

	static vector<string> split(string text, string delim = " ")
	{
		vector<string> vWords;
		string word = "";
		int pos = 0;
		while ((pos = text.find(delim)) != std::string::npos)
		{
			word = text.substr(0, pos);
			vWords.push_back(word);
			text.erase(0, pos + delim.length());
		}
		if (text != "")
			vWords.push_back(text);
		return vWords;
	}
	vector<string> split()
	{
		return split(_value);
	}

	static string TrimLeft(string text)
	{
		for (int i = 0; i < text.length(); i++)
			if (text[i] != ' ')
				return text.substr(i, text.length() - i);
		return"";
	}
	void TrimLeft()
	{
		_value = TrimLeft(_value);
	}

	static string TrimRight(string text)
	{
		for (int i = text.length() - 1; i >= 0; i--)
			if (text[i] != ' ')
				return text.substr(0, i + 1);
		return"";
	}
	void TrimRight()
	{
		_value = TrimRight(_value);
	}

	static string Trim(string text)
	{
		text = TrimLeft(text);
		text = TrimRight(text);
		return text;
	}
	void Trim() {
		_value = Trim(_value);
	}

	static string join(string arr[], string delim = " ")
	{
		string text = "";
		int i = 0;
		for (i = 0; i < arr->size() - 1; i++)
			text = text + arr[i] + delim;
		text += arr[i];
		return text;
	}
	static string join(vector<string> vWords, string delim = " ")
	{
		string text = "";
		int i = 0;
		for (i = 0; i < vWords.size() - 1; i++)
			text = text + vWords[i] + delim;
		text += vWords[i];
		return text;
	}
	static string AllStringUpper(string text) {
		for (int i = 0; i < text.length(); i++) {
			text[i] = toupper(text[i]);
		}
		return text;
	}
};


