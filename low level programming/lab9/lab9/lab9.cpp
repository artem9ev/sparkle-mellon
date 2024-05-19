#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

// создает случайный граф g1
void G1(int** g1, int n) {
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
void G2(int** g1, int** g2, int n) {
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

void printG(int** g, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << " " << g[i][k];
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	srand(time(NULL));
	int n = 10000;
	int** g1 = new int* [n], ** g2 = new int* [n];
	G1(g1, n);
	G2(g1, g2, n);
	printG(g1, n);
	printG(g2, n);
	auto t0 = chrono::high_resolution_clock::now();
	printG(g1, n);
	printG(g2, n);
	auto t1 = chrono::high_resolution_clock::now();

	cout << "2 th -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl;


}