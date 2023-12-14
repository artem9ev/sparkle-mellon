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

int steps = 0;

void nextSym() {
	steps++;
	if (cursor < knf_s.size())
	{
		steps += 2;
		cursor++;
	}
}

bool letter() {
	steps += 2;
	if (knf_s[cursor] == 'x' || knf_s[cursor] == 'X')
	{
		steps++;
		nextSym();
		return true;
	}
	else
	{
		steps++;
		cout << "не символ X - " << cursor << endl;
		return false;
	}
}

void sign() {
	steps++;
	if (knf_s[cursor] == '-')
	{
		steps++;
		xSign = -1;
		nextSym();
	}
}

// получает слагаемое
bool getTerm() {
	sign();
	steps++;
	if (letter()) {
		steps += 8;
		int start = cursor;
		while (knf_s[cursor] >= '0' && knf_s[cursor] <= '9')
		{
			steps += 2;
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
		steps++;
		return false;
	}
}

void skipKon() {
	steps++;
	if (knf_s[cursor] == '&')
	{
		nextSym();
	}
}
void skipDij() {
	steps += 2;
	if (knf_s[cursor] == '\\' && knf_s[cursor + 1] == '/')
	{
		nextSym();
		nextSym();
	}
}

bool openBracket() {
	steps += 2;
	if (knf_s[cursor] == '(')
	{
		steps += 4;
		nextSym();
		knf.push_back(vector<int>());
		currentDij++;
		while (knf_s[cursor] != ')')
		{
			steps += 3;
			if (!getTerm()) {
				cout << "не слагаемое - " << cursor << endl;
				steps++;
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
	steps += 2;
	for (int i = 0; i < knf_s.size(); ) {// удалил пробелы
		steps++;
		if (knf_s[i] == ' ')
			knf_s.erase(i, 1);
		else
			i++;
	}
	cursor = 0;
	while (cursor < knf_s.size())
	{
		steps++;
		if (!openBracket()) {
			steps++;
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

// проверяет кнф на наличие дизъюнкта
bool hasDij(vector<int> d) {
	for (int i = 0; i < knf.size(); i++)
	{
		steps++;
		if (d.size() == knf[i].size())
		{
			steps += 2;
			bool flag = true;
			for (int k = 0; k < knf[i].size(); k++)
			{
				steps++;
				if (d[k] != knf[i][k])
				{
					steps++;
					flag = false;
				}
			}
			if (flag)
			{
				steps++;
				return true;
			}
		}
	}
	steps++;
	return false;
}
// проверяет является ли дизъюнкт тождественно верно
bool isTrueDij(vector<int> d) {
	for (int i = 0; i < d.size(); i++)
	{
		for (int k = i; k < d.size(); k++)
		{
			steps += 2;
			if (i != k && d[i] == -d[k])
			{
				steps++;
				return true;
			}
		}
	}
	steps++;
	return false;
}


vector<int> getResolvent(int i, int j, int x) {
	vector<int> res;
	for (int k = 0; k < knf[i].size(); k++)
	{
		steps++;
		if (abs(knf[i][k]) != x)
		{
			steps += 2;
			bool flag = true;
			for (int u = 0; u < res.size(); u++)
			{
				steps++;
				if (res[u] == knf[i][k])
				{
					steps++;
					flag = false;
					break;
				}
			}
			if (flag)
			{
				steps++;
				res.push_back(knf[i][k]);
			}
		}
	}
	for (int g = 0; g < knf[j].size(); g++)
	{
		steps++;
		if (abs(knf[j][g]) != x)
		{
			steps += 2;
			bool flag = true;
			for (int u = 0; u < res.size(); u++)
			{
				steps++;
				if (res[u] == knf[j][g])
				{
					steps++;
					flag = false;
					break;
				}
			}
			if (flag)
			{
				steps++;
				res.push_back(knf[j][g]);
			}
		}
	}
	steps++;
	return res;
}

// применяет принцип резолюции
bool resolution() {
	vector<int> res;
	for (int i = 0; i < knf.size(); i++)
	{
		for (int k = 0; k < knf[i].size(); k++)
		{
			for (int j = 0; j < knf.size(); j++)
			{
				steps++;
				if (i == j)
				{
					continue;
				}
				for (int g = 0; g < knf[j].size(); g++)
				{
					steps++;
					if (knf[i][k] == -knf[j][g])
					{
						steps += 3;
						res = getResolvent(i, j, abs(knf[i][k]));
						for (int i = 0; i < res.size(); i++)
						{
							for (int k = 0; k < res.size(); k++)
							{
								if (abs(res[i]) < abs(res[k]))
								{
									int t = res[k];
									res[k] = res[i];
									res[i] = t;
								}
							}
						}
						// если резольвента не тождественная еденица и в кнф нет похожего дизъюнкта
						if (!isTrueDij(res) && !hasDij(res)) 
						{
							steps += 2;
							knf.push_back(res);
							if (res.size() == 0) // резольвента оказалась пустой
							{
								steps++;
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

// 2:
// (x1\/-x2)&(x1\/x2)
// (x1\/-x2)&(x1\/x2)&(-x1\/x2)&(-x1\/-x2)
//
// 3:
// (x1\/x2)&(-x3\/x2)&(-x1\/x3)
// (x1\/x2)&(x1\/x3)&(x2\/x3)&(-x1\/-x2)&(-x1\/-x3)&(-x2\/-x3)
// 
// 4:
// (x1\/x2\/x3)&(-x2\/-x3\/-x4)&(-x1\/x4)
// (x3\/-x4)&(x1\/x2)&(x1\/x3)&(x2\/x3)&(-x1\/-x2)&(-x1\/-x3)&(-x2\/-x3)
// 
// 5:
// (x1\/x3\/x4)&(-x1\/x3)&(-x4\/x5)&(-x5\/x2)&(-x2)
// (x4\/x5)&(x1\/x2)&(x1\/x3)&(x2\/x3)&(-x1\/-x2)&(-x1\/-x3)&(-x2\/-x3)
// 
// 6:
// (x1\/x2\/x3)&(-x3\/x4\/x5)&(-x4\/x6)
// (x1\/x2\/x3)&(-x3\/x4\/x5)&(-x4\/x6)&(x1\/-x2)&(x1\/x2)&(-x1\/x2)&(-x1\/-x2)
//

int main()
{
	setlocale(LC_ALL, "RUS");
	
	bool isKnf = false;
	while (!isKnf)
	{
		cout << "knf: ";
		getline(cin, knf_s);
		if (!parse()) {
			cout << "это не правильная кнф" << endl;
			knf_s.clear();
			knf.clear();
			lit.clear();
			currentDij = -1;
			cursor = 0;
			xSign = 1;
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
	cout << "кол-во выполненных элементарных операций: " << steps  << endl << endl;

}