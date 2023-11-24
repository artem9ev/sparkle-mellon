#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int N = 16777216;

int h(char* url)
{
    int k = 0;
    for (int i = 0; url[i]; i++)
    {
        k = (31 * k + url[i]) % N;
    }
    return k;
}

int rang(long long a)
{
    int k = 0;
    for (long long x = a; x > 0;)
    {
        if (x % 2 == 1) break;
        x = x >> 1;
        k++;
    }
    return k;
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
        elem = new char* [m];
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
    // дает случайный URL из текущего множества
    char* get()
    {
        return elem[rand() % size];
    }
    double F_M(int s, int m) 
    {
        int B[64];
        for (int i = 0; i < 64; i++) B[i] = 0;
        for (int i = 0; i < s; i++)
        {
            char* x = get();
            int index = rang(h(x));
            B[index] = 1;
        }
        int R = 0;
        for (int i = 0; i < 64; i++)
        {
            if (!B[i])
            {
                R = i;
                break;
            }
        }
        return (pow(2, R) / 0.77351); // me
    }
} URL;

int main()
{
    int valueM[] = { 10, 20, 30, 40, 50, 100, 500, 1000 };
    int valueS[] = { 2, 5, 10, 100 };
    ofstream res("res.txt");
    cout << "m=\ts=\tme=\tE=\tD=\n";
    res << "m=\ts=\tme=\tE=\tD=\n";
    for (int i = 0; i < 8; i++)
    {
        for (int y = 0; y < 4; y++)
        {
            int m = valueM[i];
            int s = valueS[y] * m;
            double me_cr = 0;
            for (int l = 0; l < 1000; l++)
            {
                URL.create(m);
                me_cr += URL.F_M(s, m);

            }
            me_cr /= 1000.0; // среднее me
            double E = abs(m - me_cr);
            double D = E / m;
            cout << fixed << m << "\t" << s << "\t" << me_cr << "\t" << E << "\t" << D << "\n";
            res << fixed << m << "\t" << s << "\t" << me_cr << "\t" << E << "\t" << D << "\n";
        }
    }
    return 0;
}
