#include <iostream>
#include <time.h>

using namespace std;

int N = 0;
int L = 0;

// на сайт отправляется поток запросов с адресов этого мн-ва
// с одного адреса мб отправленно неограниченное число запросов
// на сайте исп программа с алгоритмом Флажоле-Мартина, подсчитывающая кол-во различных адресов, с которых приходят запросы
//
// найти зависмость
int hesh(char* url);
int rang(int y);

void printBin(int  y) {
    for (int i = y, l = 0; l < L; i /= 2, l++)
    {
        if (i % 2 == 0)
        {
            cout << '0';
        }
        else
        {
            cout << '1';
        }
    }
    cout << "  -  ";
}

void generateURL(char* a) {
    for (int i = 0; a[i]; i++)
    {
        a[i] = rand() % 2 == 0 ? rand() % ('z' - 'a') + 'a' : rand() % ('9' - '0') + '0';
    }
}

struct {
    int size = 0;
    int urlLength = 30;
    char** elem = nullptr;
    void create(int m) {
        for (int i = 0; i < size; i++)
        {
            delete[] elem[i];
        }
        delete[] elem;
        elem = new char*[m];
        size = m;
        for (int i = 0; i < m; i++)
        {
            elem[i] = new char[urlLength];
            elem[i][urlLength - 1] = '\0';
            bool isGoodURL = false;
            while (!isGoodURL)
            {
                isGoodURL = true;
                generateURL(elem[i]);
                for (int k = 0; k < i; k++)
                {
                    bool isEqual = true;
                    for (int j = 0; elem[i]; j++)
                    {
                        if (elem[i][j] != elem[k][j])
                        {
                            isEqual = false;
                            break;
                        }
                    }
                    if (isEqual == true)
                    {
                        isGoodURL = false;
                        break;
                    }
                }
            }
        }
    }
    void print() {
        for (int i = 0; i < size; i++)
        {
            cout << (i + 1) << ":\t";
            for (int k = 0; elem[i][k]; k++)
            {
                cout << elem[i][k];
            }
            int h = hesh(elem[i]);
            cout << "\th: " << h << "\trang: ";
            printBin(h);
            cout << rang(h) << endl;
        }
    }
} URL;

// возвращает значение от 0 до N-1  (m < N)
//
int hesh(char* url) {
    int k = 0;
    for (int i = 0; url[i]; i++)
    {
        k += url[i];
    }
    return k;
}

int rang(int y) {
    int r = 0;
    for (int i = y, l = 0; l < L; i /= 2, l++)
    {
        if (i % 2 == 0)
        {
            r++;
        }
        else
        {
            break;
        }
    }
    return r;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    cout << "m = ";
    int m; cin >> m;
    N = 5 * m;
    for (int i = N; i > 0; i /= 2)
    {
        L++;
    }
    cout << "N = " << N << "\tL = " << L << endl;
    URL.create(m);
    URL.print();
}
