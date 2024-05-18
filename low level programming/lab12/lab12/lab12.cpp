#include <iostream>
#include <ppl.h>

using namespace std;

int** generateMatr(int size) {
    int** C = new int* [size];
    for (int i = 0; i < size; i++)
    {
        C[i] = new int[size];
        for (int k = 0; k < size; k++)
        {
            C[i][k] = rand() % 10;
        }
    }
    return C;
}

void printMatr(int** A, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
            cout << " " << A[i][k];
        }
        cout << endl;
    }
    cout << endl;
}

int** multMatr(int** A, int** B, int size) {
    int** C = new int*[size];
    for (int i = 0; i < size; i++)
    {
        C[i] = new int[size];
        for (int k = 0; k < size; k++)
        {
            C[i][k] = 0;
            for (int j = 0; j < size; j++)
            {
                C[i][k] += A[i][j] * B[j][k];
            }
        }
    }
    return C;
}

int** parMultMatr(int** A, int** B, int size) {
    int** C = new int* [size];
    concurrency::parallel_for(0, size, [=](int i) {
        C[i] = new int[size];
        for (int k = 0; k < size; k++)
        {
            C[i][k] = 0;
            for (int j = 0; j < size; j++)
            {
                C[i][k] += A[i][j] * B[j][k];
            }
        }
        });
    return C;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "n = "; cin >> n;
    int** A = generateMatr(n);
    int** B = generateMatr(n);

    auto t0 = chrono::high_resolution_clock::now();
    int** R = multMatr(A, B, n);
    auto t1 = chrono::high_resolution_clock::now();
    cout << "1 поток -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl;

    t0 = chrono::high_resolution_clock::now();
    int** P = parMultMatr(A, B, n);
    t1 = chrono::high_resolution_clock::now();

    cout << "много потоков -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl;
}