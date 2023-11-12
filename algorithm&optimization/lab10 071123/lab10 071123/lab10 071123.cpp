#include <iostream>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

// создает случайный граф
int** G1(int n) {
    int** g = new int* [n];
	for (int i = 0; i < n; i++) {
		g[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			if (i == k) {
				g[i][k] = 1;
			}
			else if (k > i) {
				g[i][k] = rand() % 2;
				g[k][i] = g[i][k];
			}
		}
	}
	return g;
}

// создает случайный граф изоморфный данному
int** G2(int** g1, int n) {
	int** g2 = new int* [n];
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
	}cout << endl;
	return g2;
}

// проверяет являются ли графы g1 и g2 изоморфными
bool iso(int** g1, int** g2, int n) {

	return false;
}

int main()
{
	srand(time(NULL));

	cout << "n = ";
	int n; cin >> n;


	/*int** g1 = G1(n);
	int** g2 = G2(g1, n);
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
	}*/
}