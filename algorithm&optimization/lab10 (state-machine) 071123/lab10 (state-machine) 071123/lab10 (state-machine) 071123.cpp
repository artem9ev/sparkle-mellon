#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>;
#include <string>
#include <time.h>

using namespace std;

int n;
int minDeg;
int** g1;
int** g2;

struct state {
	bool isDead = false;
	vector<int> synonym;
	state() {
		synonym = vector<int>(n, -1);
	}
	state(vector<int> v) {
		synonym = v;
	}
	bool isSetted() {
		for (int i = 0; i < synonym.size(); i++)
		{
			if (synonym[i] == -1)
			{
				return false;
			}
		}return true;
	}
	bool hasSyn(int node_2) {
		for (int i = 0; i < synonym.size(); i++)
		{
			if (synonym[i] == node_2)
			{
				return true;
			}
		}
		return false;
	}
	void set(int node_1, int node_2) {
		synonym[node_1] = node_2;
	}
	int get(int node_1) {
		return synonym[node_1];
	}
	int pos(int node_2) {
		for (int i = 0; i < n; i++)
		{
			if (synonym[i] == node_2)
			{
				return i;
			}
		}
		return -1;
	}
};

// создает случайный граф g1
void G1() {
	g1 = new int* [n];
	for (int i = 0; i < n; i++)
	{
		g1[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (i == k)
			{
				g1[i][k] = 0;
			}
			else if (k > i)
			{
				g1[i][k] = rand() % 2;
				g1[k][i] = g1[i][k];
			}
		}
	}
}

// создает случайный граф g2 изоморфный g1
void G2() {
	g2 = new int* [n];
	bool* isSetted = new bool[n];
	for (int i = 0; i < n; i++) {
		g2[i] = new int[n];
		isSetted[i] = false;
		for (int k = 0; k < n; k++)
		{
			g2[i][k] = 9;
		}
	}
	int v2, v1 = 0;
	int* rename = new int[n];
	while (v1 < n) // переименование вершин
	{
		v2 = rand() % n;
		while (isSetted[v2])
		{
			v2 = (v2 + 1) % n;
		}
		rename[v1] = v2;
		isSetted[v2] = true;
		v1++;
	}
	for (int i = 0; i < n; i++) // заполнение g2 с учетом переименованых вершин
	{
		for (int k = 0; k < n; k++)
		{
			if (k >= i) {
				g2[i][k] = g1[rename[i]][rename[k]];
				g2[k][i] = g1[rename[i]][rename[k]];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << i << " ";
	}cout << "       ";
	for (int i = 0; i < n; i++)
	{
		cout << rename[i] << " ";
	}cout << endl << endl;
}

// проверяет на соответствие вершины по степеням вершин их соседей
bool isEqualNodes(pair<vector<int>, vector<int> >& degs, int node_1, int node_2)
{
	if (degs.first[node_1] == n - 1) // очевидно, что если вершины идут во все остальные, то их можно назвать одинаковыми
	{
		return true;
	}
	bool isEqual = true;
	int toFind; // степень вершины для нахождения в графе g2
	vector<bool> isVisited(n, false);
	for (int i = 0; i < n; i++)
	{
		if (!g1[node_1][i]) // нашел ребро к i вершине в первом графе
		{
			continue; // если нет ребра, то пропускаем проверку
		}
		toFind = degs.first[i]; // записал степень вершины, которую хочу найти в графе g2
		int k = 0;
		while (k < n)
		{
			if (g2[node_2][k] && !isVisited[k] && toFind == degs.second[k])
			{
				isVisited[k] = true;
				break;
			}
			k++;
		}
		if (k == n) // если не получилось найти соответсвующую вершину, то конец
		{
			return false;
		}
	}
	return isEqual;
}

bool iso(int deg, pair<vector<int>, vector<int> >& degs, pair< map<int, set<int> >, map<int, set<int> > >& list, state current_st = state(), string s = "")
{
	// дно рекурсии
	if (deg == minDeg - 1)
	{
		if (current_st.isSetted())
		{
			cout << s << "POBEDA !!! POBEDA !!! POBEDA !!!" << endl << endl;
			return true;
		}
		else
		{
			cout << s << "WTF??? WTF??? WTF???" << endl << endl;
			return false;
		}
	}
	cout << endl << s << "recursion: " << deg << endl;
	vector<state> states;
	states.push_back(state(current_st));
	int id = 0;
	// перебираю вершины текущей степени (deg)...
	for (set<int>::iterator node_1 = list.first[deg].begin(); node_1 != list.first[deg].end(); node_1++)
	{
		bool hasSyn = false; // для проверки: смогли ли мы найти соответствие node_1 и node_2
		for (set<int>::iterator node_2 = list.second[deg].begin(); node_2 != list.second[deg].end(); node_2++)
		{
			// если есть соответствие node_1 -> node_2, то...
			if (isEqualNodes(degs, *node_1, *node_2))
			{
				cout << s << "is equal: " << *node_1 << " | " << *node_2 << endl;
				id = 0;
				while (id < states.size() && (states[id].get(*node_1) != -1 || states[id].hasSyn(*node_2)))
				{
					id++; // ищу состояние в котором для node_1 нет соответсвующей node_2
				}
				if (id == states.size())
				{
					cout << s << "created new state: " << id << endl;
					states.push_back(state(states[id - 1])); // добавляю новое состояние, если в остальных уже задано соответствие node_1 -> node_2
				}
				states[id].set(*node_1, *node_2); // задаю соответствие node_1 -> node_2
				states[id].isDead = false;

				for (int i = 0; i < n; i++)
				{
					if (states[id].get(i) != -1 && g2[*node_2][i] == 1 && g1[*node_1][states[id].pos(i)] == 0)
					{
						cout << s << "try to equal: " << *node_1 << " -> " << *node_2 << " | g2: " << *node_2 << " " << i << " = 1 | g1: " << *node_1 << " " << states[id].pos(i) << " = 0" << endl;
						cout << s << "PIZDEC!!! PIZDEC!!! PIZDEC!!! " << id << endl;
						states[id].isDead = true;
					}
				}
				hasSyn = hasSyn || !states[id].isDead;
			}
		}
		if (!hasSyn)
		{
			cout << s << "ERROR! THERE'S node_1 WITHOUT SYNONYMIC node_2" << endl;
			//return false;
		}
		/* ЗДЕСЬ СДЕЛАТЬ ПРОВЕРКУ НА НАЛИЧИЕ СОТОЯНИЯ для node_1 -> node_2
		return false;
		*/
	}
	cout << s << "states: " << endl;
	bool isIso = false;
	string s1 = s + "\t";
	for (vector<state>::iterator st = states.begin(); st != states.end(); st++)
	{
		cout << s << "[" << (st - states.begin()) << "] : ";
		for (int k = 0; k < n; k++)
		{
			cout << (*st).synonym[k] << "    ";
		}
		cout << ((*st).isDead ? "is dead" : "ok") << endl;
		if ((*st).isDead == false)
		{
			isIso = iso(deg - 1, degs, list, *st, s1) || isIso;
		}
	}

	return isIso;
}

// проверяет являются ли графы g1 и g2 изоморфными
bool startIso(int** g1, int** g2, int n) {
	// сравнивать вершины по их степеням?
	pair<vector<int>, vector<int> > degs(vector<int>(n, 0), vector<int>(n, 0));
	pair< map<int, set<int> >, map<int, set<int> > > list;
	int maxDeg = -1;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			degs.first[i] += g1[i][k];
			degs.second[i] += g2[i][k];
		}
		list.first[degs.first[i]].insert(i);
		list.second[degs.second[i]].insert(i);
	}
	maxDeg = (*--list.first.end()).first;
	minDeg = (*list.first.begin()).first;
	for (map<int, set<int> >::iterator map1_it = list.first.begin(), map2_it = list.second.begin();
		map1_it != list.first.end() && map2_it != list.second.end(); map1_it++, map2_it++)
	{
		cout << (*map1_it).first << ": ";
		for (set<int>::iterator it = (*map1_it).second.begin(); it != (*map1_it).second.end(); it++)
		{
			cout << *it << " ";
		}
		cout << " | ";
		for (set<int>::iterator it = (*map2_it).second.begin(); it != (*map2_it).second.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << minDeg << "!  " << maxDeg << '!' << endl;

	// выбираю вершину и смотрю что и куда идет...
	return iso(maxDeg, degs, list);
}

int main()
{
	cout << "key: ";
	int key; cin >> key;
	srand(key);

	cout << "n = ";
	cin >> n;

	G1();
	G2();
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << g1[i][k] << " ";
		}
		cout << "   |   ";
		for (int k = 0; k < n; k++)
		{
			cout << g2[i][k] << " ";
		}
		cout << endl;
	}
	cout << endl;

	startIso(g1, g2, n);
}