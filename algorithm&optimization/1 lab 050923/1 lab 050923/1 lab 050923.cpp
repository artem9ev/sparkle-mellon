#include <iostream>

using namespace std;

int fastCount(int n) {
    int count = 0;
    int* vector = new int[n];
    int* newVector = new int[n];
    int** matr = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matr[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            matr[i][k] = 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        vector[i] = 1;
        newVector[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            newVector[i] += matr[i][k];
            count += 2;
        }
        newVector[i] *= vector[i];
        count += 2;
    }
    return count;
}

int main()
{
    int counter[15];
    
    setlocale(LC_ALL, "RUS");
    int n = 2;
    for (int c = 0; c < 15; c++, n += 2)
    {
        counter[c] = fastCount(n);
    }

    for (int i = 0; i < 15; i++)
    {
        cout << counter[i] << "\t";
    }
}