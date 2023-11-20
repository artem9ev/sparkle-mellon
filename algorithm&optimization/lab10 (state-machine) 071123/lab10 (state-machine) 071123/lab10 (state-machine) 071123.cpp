﻿#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <time.h>

using namespace std;

int n;
int minDeg;
int maxDeg = -1;
int** g1;
int** g2;
pair<vector<int>, vector<int> > degs;
pair< map<int, set<int> >, map<int, set<int> > > list;

struct state {
	vector<int> synonym;
	state() {
		synonym = vector<int>(n, -1);
	}
	state(vector<int> v) {
		synonym = v;
	}
	bool isSetted() {
		for (int i = 0; i < synonym.size(); i++)
			if (synonym[i] == -1)
				return false;
		return true;
	}
	bool hasSyn(int node_2) {
		for (int i = 0; i < synonym.size(); i++)
			if (synonym[i] == node_2)
				return true;
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
			if (synonym[i] == node_2)
				return i;
		return -1;
	}
};

// создает случайный граф g1
void G1() {
	g1 = new int* [n];
	for (int i = 0; i < n; i++)
		g1[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			if (i == k) {
				g1[i][k] = 0;
			}
			else if (k > i) {
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
		for (int k = 0; k < n; k++) {
			g2[i][k] = 9;
		}
	}
	int v2, v1 = 0;
	int* rename = new int[n];
	while (v1 < n) // переименование вершин
	{
		v2 = rand() % n;
		while (isSetted[v2]) {
			v2 = (v2 + 1) % n;
		}
		rename[v1] = v2;
		isSetted[v2] = true;
		v1++;
	}
	for (int i = 0; i < n; i++) { // заполнение g2 с учетом переименованых вершин
		for (int k = 0; k < n; k++) {
			if (k >= i) {
				g2[i][k] = g1[rename[i]][rename[k]];
				g2[k][i] = g1[rename[i]][rename[k]];
			}
		}
	}
	/*for (int i = 0; i < n; i++)
	{
		cout << i << " ";
	}cout << "       ";
	for (int i = 0; i < n; i++)
	{
		cout << rename[i] << " ";
	}cout << endl << endl;*/
}

// проверяет на соответствие вершины по степеням вершин их соседей
bool isEqualNodes(int node_1, int node_2)
{
	if (degs.first[node_1] == n - 1) { // очевидно, что если вершины идут во все остальные, то их можно назвать одинаковыми
		return true;
	}
	bool isEqual = true;
	int toFind; // степень вершины для нахождения в графе g2
	vector<bool> isVisited(n, false);
	for (int i = 0; i < n; i++) {
		if (!g1[node_1][i]) { // нашел ребро к i вершине в первом графе
			continue; // если нет ребра, то пропускаем проверку
		}
		toFind = degs.first[i]; // записал степень вершины, которую хочу найти в графе g2
		int k = 0;
		while (k < n) {
			if (g2[node_2][k] && !isVisited[k] && toFind == degs.second[k]) {
				isVisited[k] = true;
				break;
			}
			k++;
		}
		if (k == n) { // если не получилось найти соответсвующую вершину, то конец
			return false;
		}
	}
	return isEqual;
}

bool canPasteNode(state &st, int node_1, int node_2, string s) {
	for (int i = 0; i < n; i++) {
		if (st.pos(i) != -1 && g2[node_2][i] == 1 && g1[node_1][st.pos(i)] == 0) {
			return false;
		}
	}
	return true;
}

bool iso(map<int, set<int> >::reverse_iterator map_1, map<int, set<int> >::reverse_iterator map_2, set<int>::iterator it_node_1, state current_st = state(), string s = "")
{
	/*cout << s << "try " << (*map_1).first << endl;
	if (it_node_1 == ((*map_1).second.end()))
	{
		cout << "SOS" << endl;
	}*/
	// дно рекурсии
	
	//cout<< s << "recursion: " << (*map_1).first << endl;
	// перебираю вершины текущей степени (deg)...
	bool isIso = false;
	for (set<int>::iterator node_2 = (*map_2).second.begin(); node_2 != (*map_2).second.end(); node_2++) {
		// если есть соответствие node_1 -> node_2, то...
		/*cout << s << *it_node_1 << " - " << *node_2 << " ??? " << degs.first[*it_node_1] << " - " << degs.second[*node_2];
		cout << " = " << isEqualNodes(*it_node_1, *node_2) << " " << (current_st.pos(*node_2) == -1);
		cout << " " << canPasteNode(current_st, *it_node_1, *node_2, s) << endl;*/
		if (isEqualNodes(*it_node_1, *node_2) && current_st.pos(*node_2) == -1 && canPasteNode(current_st, *it_node_1, *node_2, s)) {
			set<int>::iterator node_1 = it_node_1;
			state st = current_st;
			map<int, set<int> >::reverse_iterator next_map_1 = map_1;
			map<int, set<int> >::reverse_iterator next_map_2 = map_2;
			st.set(*node_1, *node_2); // задаю соответствие node_1 -> node_2

			/*cout << s << "equal: " << *node_1 << " - " << *node_2 << " | state :   []     ";
			for (int k = 0; k < n; k++)
			{
				cout << st.synonym[k] << "    ";
			}
			cout << "[]" << endl;
			cout << s << "B " << *node_1 << " " << *--(*next_map_1).second.end() << endl;*/

			if (*node_1 != *--(*next_map_1).second.end()) {
				node_1++;
			}
			else if(next_map_1 != --list.first.rend()) {
				//cout << s << "PONIZHENIE!" << endl;
				next_map_2++;
				next_map_1++;
				node_1 = (*next_map_1).second.begin();
			}
			if (st.isSetted()) {
				//cout << s << "POBEDA !!! POBEDA !!! POBEDA !!!" << endl << s << "return true" << endl;
				return true;
			}
			else {
				isIso = isIso || iso(next_map_1, next_map_2, node_1, st, s + "    ");
			}
		}
	}
	//cout  << s << "end" << endl;
	return isIso;
}

// проверяет являются ли графы g1 и g2 изоморфными
bool startIso(int** g1, int** g2, int n) {
	// сравнивать вершины по их степеням?
	degs = pair<vector<int>, vector<int> >(vector<int>(n, 0), vector<int>(n, 0));
	list;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			degs.first[i] += g1[i][k];
			degs.second[i] += g2[i][k];
		}
		list.first[degs.first[i]].insert(i);
		list.second[degs.second[i]].insert(i);
	}
	maxDeg = (*--list.first.end()).first;
	minDeg = (*list.first.begin()).first;
	for (map<int, set<int> >::iterator map1_it = list.first.begin(), map2_it = list.second.begin();
		map1_it != list.first.end() && map2_it != list.second.end(); map1_it++, map2_it++) {
		cout << (*map1_it).first << ": ";
		for (set<int>::iterator it = (*map1_it).second.begin(); it != (*map1_it).second.end(); it++) {
			cout << *it << " ";
		}
		cout << " | ";
		for (set<int>::iterator it = (*map2_it).second.begin(); it != (*map2_it).second.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	//cout << minDeg << "!  " << maxDeg << '!' << endl << endl;

	// выбираю вершину и смотрю что и куда идет...
	return iso(list.first.rbegin(), list.second.rbegin(), list.first[maxDeg].begin());
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
	/*for (int i = 0; i < n; i++)
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
	cout << endl;*/

	bool flag = startIso(g1, g2, n);
	cout << endl << (flag ? "iso" : "not iso") << endl;
}