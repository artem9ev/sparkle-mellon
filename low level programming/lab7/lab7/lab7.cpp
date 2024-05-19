#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <time.h>

using namespace std;

void multiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int strS, int strE, int colS, int colE, int n) {
    for (int i = strS; i < strE; ++i) {
        for (int j = colS; j < colE; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));

    int n = 1000;
    int size = n / 2;
    vector<vector<int>> A(n, vector<int>(n)), B(n, vector<int>(n)), C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = rand() % 50;
            B[i][j] = rand() % 50;
        }
    }

    auto t0 = chrono::high_resolution_clock::now();
    thread th1(multiply, cref(A), cref(B), ref(C), 0, size, 0, size, n);
    thread th2(multiply, cref(A), cref(B), ref(C), 0, size, size, n, n);
    thread th3(multiply, cref(A), cref(B), ref(C), size, n, 0, size, n);
    thread th4(multiply, cref(A), cref(B), ref(C), size, n, size, n, n);

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    auto t1 = chrono::high_resolution_clock::now();

    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec\n";
}


//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <time.h>
//
//using namespace std;
//
//void sumMas(int* a, long &summ, int s, int e) {
//	for (int i = s; i < e; i++)
//	{
//		summ += a[i];
//	}
//}
//
//int main()
//{
//	srand(time(NULL));
//	long n = 100000000;
//	int* a = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		a[i] = rand() % 100;
//	}
//
//	long summ = 0;
//	auto t0 = chrono::high_resolution_clock::now();
//    sumMas(a, summ, 0, n);
//	auto t1 = chrono::high_resolution_clock::now();
//	cout << "summ = " << summ << endl;
//	cout << "1 th -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl << endl;
//
//	summ = 0;
//	long summ1 = 0, summ2 = 0, summ3 = 0, summ4 = 0;
//	long n1 = n / 4;
//	long n2 = n / 2;
//	long n3 = n / 4 * 3;
//	t0 = chrono::high_resolution_clock::now();
//	thread th1(sumMas, a, ref(summ1), 0, n1);
//	thread th2(sumMas, a, ref(summ2), n1, n2);
//	thread th3(sumMas, a, ref(summ3), n2, n3);
//	thread th4(sumMas, a, ref(summ4), n3, n);
//	th1.join();
//	summ += summ1;
//	th2.join();
//	summ += summ2;
//	th3.join();
//	summ += summ3;
//	th4.join();
//	summ += summ4;
//	t1 = chrono::high_resolution_clock::now();
//	cout << "summ = " << summ << endl;
//
//	cout << "4 th -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl;
//}

