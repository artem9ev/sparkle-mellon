#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

int sortAr(int *a, int n) {
	int temp, count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (a[i] < a[k])
			{
				temp = a[k];
				a[k] = a[i];
				a[i] = temp;
				count += 3;
			}
			count++;
		}
	}
	return count;
}

int createMax(int n) {
	int value = n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = value--;
	}
	return sortAr(a, n);
}
int createMin(int n) {
	int value = 0;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = value++;
	}
	return sortAr(a, n);
}
int	createRandom(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand();
	}
	return sortAr(a, n);
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	int resultMin[10];
	int resultMax[10];
	long long resultR[10];
	for (int i = 0; i < 10; i++)
	{
		resultR[i] = 0;
	}
	
	for (int i = 0, n = 100; i < 10; i++, n += 100)
	{
		resultMin[i] = createMin(n);
		resultMax[i] = createMax(n);
		for (int k = 0; k < 1000; k++)
		{
			resultR[i] += createRandom(n);
		}
	}
	cout << "T-min: ";
	for (int i = 0; i < 10; i++)
	{
		cout << resultMin[i] << "\t";
	}
	cout << "\nT-max: ";
	for (int i = 0; i < 10; i++)
	{
		cout << resultMax[i] << "\t";
	}
	cout << "\nT-mean: ";
	for (int i = 0; i < 10; i++)
	{
		resultR[i] /= 1000;
		cout << resultR[i] << "\t";
	}
}
