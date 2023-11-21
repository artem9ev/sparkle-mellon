#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <time.h>

using namespace std;

int steps = 0;

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
		steps += n;
	}
	state(vector<int> v) {
		synonym = v;
		steps++;
	}
	bool isSetted() {
		steps++;
		for (int i = 0; i < synonym.size(); i++) {
			steps++;
			if (synonym[i] == -1)
				return false;
		}
		return true;
	}
	bool hasSyn(int node_2) {
		steps++;
		for (int i = 0; i < synonym.size(); i++)
		{
			steps++;
			if (synonym[i] == node_2)
				return true;
		}
		return false;
	}
	void set(int node_1, int node_2) {
		steps++;
		synonym[node_1] = node_2;
	}
	int get(int node_1) {
		steps++;
		return synonym[node_1];
	}
	int pos(int node_2) {
		steps++;
		for (int i = 0; i < n; i++)
		{
			steps++;
			if (synonym[i] == node_2)
				return i;
		}
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
}

// проверяет на соответствие вершины по степеням вершин их соседей
bool isEqualNodes(int node_1, int node_2)
{
	steps += 2;
	steps++; // отдельно считаю вызов хотя бы одного из return
	if (degs.first[node_1] == n - 1) { // очевидно, что если вершины идут во все остальные, то их можно назвать одинаковыми
		return true;
	}
	bool isEqual = true;
	int toFind; // степень вершины для нахождения в графе g2
	vector<bool> isVisited(n, false);
	steps += 1 + n;
	for (int i = 0; i < n; i++) {
		steps++;
		if (g1[node_1][i]) { // нашел ребро к i вершине в первом графе
			steps += 4;
			toFind = degs.first[i]; // записал степень вершины, которую хочу найти в графе g2
			int k = 0;
			while (k < n) {
				if (g2[node_2][k] && !isVisited[k] && toFind == degs.second[k]) {
					isVisited[k] = true;
					steps++;
					break;
				}
				k++;
				steps += 5;
			}
			if (k == n) { // если не получилось найти соответсвующую вершину, то конец
				return false;
			}
		}
	}
	return isEqual;
}

bool canPasteNode(state& st, int node_1, int node_2, string s) {
	steps++;
	for (int i = 0; i < n; i++) {
		if (st.pos(i) != -1 && g2[node_2][i] == 1 && g1[node_1][st.pos(i)] == 0) {
			return false;
		}
		steps += 3;
	}
	return true;
}

bool iso(map<int, set<int> >::reverse_iterator map_1, map<int, set<int> >::reverse_iterator map_2, set<int>::iterator it_node_1, state current_st = state(), string s = "")
{
	steps++;
	bool isIso = false;
	steps++; // отдельно считаю вызов хотя бы одного из return
	for (set<int>::iterator node_2 = (*map_2).second.begin(); node_2 != (*map_2).second.end(); node_2++) {
		steps += 3;
		if (isEqualNodes(*it_node_1, *node_2) && current_st.pos(*node_2) == -1 && canPasteNode(current_st, *it_node_1, *node_2, s)) {
			set<int>::iterator node_1 = it_node_1;
			state st = current_st;
			map<int, set<int> >::reverse_iterator next_map_1 = map_1;
			map<int, set<int> >::reverse_iterator next_map_2 = map_2;
			st.set(*node_1, *node_2); // задаю соответствие node_1 -> node_2
			steps += 11;
			if (*node_1 != *--(*next_map_1).second.end()) {
				node_1++;
			}
			else if (next_map_1 != --list.first.rend()) { // перехожу следующую степень вершины
				next_map_2++;
				next_map_1++;
				node_1 = (*next_map_1).second.begin();
			}
			if (st.isSetted()) { // дно рекурсии
				return true; // найдено переименование вершин графа g2 именами вершин графа g1
			}
			else { // иначе дальше погружаюсь в рекурсию
				steps += 2;
				isIso = isIso || iso(next_map_1, next_map_2, node_1, st, s + "    ");
			}
		}
	}
	return isIso; // если не найдет хотя бы одной подходящей вершины в g2, то вернет false, иначе вернет результат след шага рекурсии
}

// проверяет являются ли графы g1 и g2 изоморфными
bool startIso(int** g1, int** g2, int n) {
	degs = pair<vector<int>, vector<int> >(vector<int>(n, 0), vector<int>(n, 0));
	steps += 2 + 2 * n;
	list = pair< map<int, set<int> >, map<int, set<int> > >();
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			steps += 4;
			degs.first[i] += g1[i][k];
			degs.second[i] += g2[i][k];
		}
		list.first[degs.first[i]].insert(i);
		list.second[degs.second[i]].insert(i);
		steps += 2;
	}
	maxDeg = (*--list.first.end()).first;
	minDeg = (*list.first.begin()).first;
	steps += 4;

	steps++;
	return iso(list.first.rbegin(), list.second.rbegin(), list.first[maxDeg].begin());
}

int main()
{
	srand(time(NULL));
	ofstream file("res.txt");
	long* sum = new long[20];
	for (n = 1; n <= 50; n++)
	{
		sum[n] = 0;
		for (int k = 0; k < 1000; k++)
		{
			steps = 0;
			G1();
			G2();

			bool flag = startIso(g1, g2, n);
			//cout << (flag ? "iso " : "not iso ") << steps << endl << endl;
			sum[n] += steps;
		}
		cout << fixed << n << "\t" << sum[n] / (float)1000 / 46<< endl;
		file << fixed << n << "\t" << sum[n] / (float)1000 << endl;
	}
}