﻿#include <iostream>
#include <string>
#include <map>

using namespace std;

struct tree {
	tree* dis, * kon;
	int info;
};
// хуйня
map<int, bool> t; // храним индекс X и  его знак??



bool parse(string &knf) // херь
{
	for (int i = 0; i < knf.size(); i++) // удалил пробельчики
		if (knf[i] == ' ')
			knf.erase(i, 1);
	for (int i = 0; i < knf.size(); i++)
	{
		char a = knf[i];
		if (a == '(' || a == ')' || a == '-' || a == 'X' || a == 'x' || a == '&' || a == '\\' || a == '/' || (a > '0' || a < '9'))
		{
			
		}
		else
		{
			return false; // получен 
		}
	}
	return true;
}
// (-X8\/X5)&(-X5\/X4)&(-X5)
int main()
{
	string knf;
	getline(cin, knf);
	parse(knf);
	cout << knf << endl;
}