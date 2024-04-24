#include <iostream>
#include <omp.h>

using namespace std;

int** CreateMatr(int n) {
	int** A = new int*[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
		for (int k = 0; k < n; k++)
		{
			A[i][k] = rand() % 10;
		}
	}
	return A;
}

int DetA(int** A, int n) {
	int res = 0;
	int* per = new int[n];

	for (int i = 0; i < n; i++)
	{
		
	}
	return res;
}

int main()
{
	int n = 4;
	int** matr = CreateMatr(n);
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << matr[i][k] << " ";
		}
		cout << endl;
	}
	cout << "Det A = " << DetA(matr, n) << endl;
}