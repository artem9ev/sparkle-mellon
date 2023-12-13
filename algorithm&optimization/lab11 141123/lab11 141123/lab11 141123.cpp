#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<vector<int> > knf;
set<int> lit;
int currentDij = -1;

int cursor = 0;
int xSign = 1;
string knf_s;

void nextSym() {
	if (cursor < knf_s.size())
	{
		cursor++;
	}
}

bool letter() {
	if (knf_s[cursor] == 'x' || knf_s[cursor] == 'X')
	{
		nextSym();
		return true;
	}
	else
	{
		cout << "не символ X - " << cursor << endl;
		return false;
	}
}

void sign() {
	if (knf_s[cursor] == '-')
	{
		xSign = -1;
		nextSym();
	}
}

// получает слагаемое
bool getTerm() {
	sign();
	if (letter()) {
		int start = cursor;
		while (knf_s[cursor] >= '0' && knf_s[cursor] <= '9')
		{
			nextSym();
		}
		int end = cursor;
		string subStr = knf_s.substr(start, end - start);
		knf[currentDij].push_back(xSign * stoi(subStr));
		lit.insert(stoi(subStr));
		return true;
	}
	else
	{
		return false;
	}
}

void skipKon() {
	if (knf_s[cursor] == '&')
	{
		nextSym();
	}
}
void skipDij() {
	if (knf_s[cursor] == '\\' && knf_s[cursor + 1] == '/')
	{
		nextSym();
		nextSym();
	}
}

bool openBracket() {
	if (knf_s[cursor] == '(')
	{
		nextSym();
		knf.push_back(vector<int>());
		currentDij++;
		while (knf_s[cursor] != ')')
		{
			if (!getTerm()) {
				cout << "не слагаемое - " << cursor << endl;
				return false;
			}
			skipDij();
			xSign = 1;
		}
		nextSym(); // пропускаю ')'
		return true;
	}
	cout << "не открывающая скобка - " << cursor << endl;
	return false;
}

bool parse()
{
	for (int i = 0; i < knf_s.size(); ) // удалил пробельчики
		if (knf_s[i] == ' ')
			knf_s.erase(i, 1);
		else
			i++;
	cursor = 0;
	while (cursor < knf_s.size())
	{
		if (!openBracket()) {
			
			return false;
		}
		skipKon();
	}
	
	return true;
}
// выписывает в консоль кнф представленную в виде матрицы
void print() {
	for (int i = 0; i < knf.size(); i++)
	{
		cout << "(";
		for (int k = 0; k < knf[i].size(); k++)
		{
			if (knf[i][k] / abs(knf[i][k]) == -1)
			{
				cout << "-";
			}
			cout << "X" << abs(knf[i][k]);
			if (k + 1 < knf[i].size())
			{
				cout << "\\/";
			}
		}
		cout << ")";
		if (i + 1 < knf.size())
		{
			cout << "&";
		}
	}
	cout << endl;
}

vector<int> getResolvent(int i, int j, int x) {
	vector<int> res;
	for (int k = 0; k < knf[i].size(); k++)
	{
		if (abs(knf[i][k]) != x)
		{
			bool flag = true;
			for (int u = 0; u < res.size(); u++)
			{
				if (res[u] == knf[i][k])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				res.push_back(knf[i][k]);
			}
		}
	}
	for (int g = 0; g < knf[j].size(); g++)
	{
		if (abs(knf[j][g]) != x)
		{
			bool flag = true;
			for (int u = 0; u < res.size(); u++)
			{
				if (res[u] == knf[j][g])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				res.push_back(knf[j][g]);
			}
		}
	}
	return res;
}
// проверяет кнф на наличие дизъюнкта
bool hasDij(vector<int> d) {
	for (int i = 0; i < knf.size(); i++)
	{
		if (d.size() == knf[i].size())
		{
			bool flag = true;
			for (int k = 0; k < knf[i].size(); k++)
			{
				if (d[k] != knf[i][k])
				{
					flag = false;
				}
			}
			if (flag)
			{
				return true;
			}
		}
	}
	return false;
}
// проверяет является ли дизъюнкт тождественно верно
bool isTrueDij(vector<int> d) {
	for (int i = 0; i < d.size(); i++)
	{
		for (int k = i; k < d.size(); k++)
		{
			if (i != k && d[i] == -d[k])
			{
				return true;
			}
		}
	}
	return false;
}

// применяет принцип резолюции
bool resolution() {
	int dij_1 = -1;
	int dij_2 = -1;
	vector<int> res;
	for (int i = 0; i < knf.size(); i++)
	{
		for (int k = 0; k < knf[i].size(); k++)
		{
			for (int j = 0; j < knf.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				for (int g = 0; g < knf[j].size(); g++)
				{
					if (knf[i][k] == -knf[j][g])
					{
						res = getResolvent(i, j, abs(knf[i][k]));
						if (!isTrueDij(res) && !hasDij(res))
						{
							knf.push_back(res);
							if (res.size() == 0)
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
 
// (-X8\/X5)&(-X5\/X4)&(-X5)
// (-x8\/x5)&(-x5\/x4)&(x8\/-x4)&(-x5) --- вып
// (X5\/X4)&(-X5)&(X5\/-X4) --- не выполнима
// (-X1\/-X2)&(X2\/X1) --- вып

// 1-выполнимая: (X1\/X2)&(-X2\/X3)&(-X1\/X3)
// 2-выполнимая: (X1\/X2\/X4)&(-X1\/X3)&(-X2\/X3)
// 3-выполнимая: (X1\/X2)&(X3\/-X4)
// 4-выполнимая: (X1\/X2\/X3)&(X2\/-X4)&(X4\/X5)
// 5-выполнимая: (X1\/X2)&(-X2\/X3\/-X4)&(X4\/-X5)

int main()
{
	setlocale(LC_ALL, "RUS");
	
	bool isKnf = false;
	while (!isKnf)
	{
		cout << "knf: ";
		getline(cin, knf_s);
		if (!parse()) {
			cout << "это не правильная кнф";
		}
		else
		{
			isKnf = true;
		}
	}
	cout << endl << "введена КНФ: " << endl;
	
	print();

	int countDij = knf.size();
	
	bool r = resolution();
	cout << " <=>" << endl;
	print();
	cout << endl;
	if (!r)
	{
		cout << "В ней есть пустая резольвента => она не выполнима" << endl;
	}
	else
	{
		cout << "Она выполнима" << endl;
	}
	cout << "кол-во различных переменных в КНФ: " << lit.size() << endl;
	cout << "кол-во дизъюнктов: " << countDij << endl;

}