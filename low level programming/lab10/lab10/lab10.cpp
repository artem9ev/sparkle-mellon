#include <iostream>
#include <time.h>
#include <chrono>
#include <omp.h>
#include <vector>

using namespace std;

bool TryGetObratMatr(vector <vector<double>>& arr)
{
    int size = arr.size();
    vector <vector<double>> EdMatr(size, vector<double>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j) EdMatr[i][j] = 1;
            else EdMatr[i][j] = 0;
        }
    }

    for (int k = 0; k < size; k++)
    {
        if (abs(arr[k][k]) < 1e-8)
        {
            bool fl = false;

            for (int i = k + 1; i < size; i++)
            {
                if (abs(arr[i][k]) > 1e-8)
                {
                    swap(arr[k], arr[i]);
                    swap(EdMatr[k], EdMatr[i]);
                    fl = true;
                    break;
                }
            }

            if (!fl)
                return false;
        }

        double div = arr[k][k];

#pragma omp parallel
        {
#pragma omp for
            for (int j = 0; j < size; j++)
            {
                arr[k][j] /= div;
                EdMatr[k][j] /= div;
            }
        }

#pragma omp parallel
        {
#pragma omp for
            for (int i = k + 1; i < size; i++)
            {
                double multi = arr[i][k];


                for (int j = 0; j < size; j++)
                {
                    arr[i][j] -= multi * arr[k][j];
                    EdMatr[i][j] -= multi * EdMatr[k][j];
                }
            }
        }
    }

    for (int k = size - 1; k > 0; k--)
    {
#pragma omp parallel
        {
#pragma omp for
            for (int i = k - 1; i > -1; i--)
            {
                double multi = arr[i][k];

                for (int j = 0; j < size; j++)
                {
                    arr[i][j] -= multi * arr[k][j];
                    EdMatr[i][j] -= multi * EdMatr[k][j];
                }
            }
        }
    }
    arr = EdMatr;
    return true;
}

double randd(const int min, const int max)
{
    if (min == max)
        return min;
    return min + rand() % (max - min);
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    int n;
    cout << "Количество уравнений: ";
    cin >> n;

    vector<vector<double>> arr(n, vector<double>(n));
    vector<double> freeC(n);

    // Заполняем матрицу
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            arr[i][j] = randd(0, 100);
        freeC[i] = randd(0, 100);
    }

    auto s = std::chrono::high_resolution_clock::now();

    // получение обратной матрицы
    if (!TryGetObratMatr(arr))
    {
        cout << "\nНевозможно найти обратную матрицу!\n";
        exit(1);
    }

    // столбец неизвестных x и вычисление результата
    vector<double> x(n);
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < n; i++)
        {
            x[i] = 0;
            for (int j = 0; j < n; j++)
                x[i] += arr[i][j] * freeC[j];
        }
    }
    auto e = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(e - s);
    std::cout << "Время вычисления: " << time.count() << " мс" << std::endl;
    return 0;
}