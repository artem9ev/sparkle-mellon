#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

int sortAr(int *a, int n) {
	int temp, count = 0;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			if (a[i] < a[k]) {
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
	for (int i = 0; i < n; i++) {
		a[i] = value--;
	}
	return sortAr(a, n);
}
int createMin(int n) {
	int value = 0;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		a[i] = value++;
	}
	return sortAr(a, n);
}
int	createRandom(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}
	return sortAr(a, n);
}

int main()
{
	srand(time(0));

	int resultMin[10];
	int resultMax[10];
	long long resultR[10];
	ofstream file("result.txt");

	for (int i = 0; i < 10; i++) {
		resultR[i] = 0;
	}
	
	cout << "n:\t\t" << "T-min:\t\t" << "T-max:\t\t" << "T-mean:" << endl;
	file << "n:\t\t" << "T-min:\t\t" << "T-max:\t\t" << "T-mean:" << endl;
	for (int i = 0, n = 100; i < 10; i++, n += 100) {
		resultMin[i] = createMin(n);
		resultMax[i] = createMax(n);
		for (int k = 0; k < 1000; k++) {
			resultR[i] += createRandom(n);
		}
		double sred = resultR[i] / 1000.0;
		cout << fixed << n << "\t\t" << resultMin[i] << "\t\t" << resultMax[i] << "\t\t" << sred << endl;
		file << fixed << n << "\t\t" << resultMin[i] << "\t\t" << resultMax[i] << "\t\t" << sred << endl;
	}
	file.close();
}
