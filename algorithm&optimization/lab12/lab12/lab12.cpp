#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long steps = 0;

struct Matr {
    vector<vector<int>> m;

    Matr(int n) {
        m.resize(n);
        for (int i = 0; i < n; i++)
        {
            m[i].resize(n);
            for (int j = 0; j < n; j++)
                m[i][j] = rand() % 900 + 100;
        }
    }
};

Matr Add(Matr A, Matr B)
{
    int n = A.m.size();
    Matr C(n);
    steps++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C.m[i][j] = A.m[i][j] + B.m[i][j];
            steps += 2;
        }
    }
    return C;
}

Matr Sub(Matr A, Matr B)
{
    int n = A.m.size();
    Matr C(n);
    steps++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C.m[i][j] = A.m[i][j] - B.m[i][j];
            steps += 2;
        }
    }
    return C;
}

Matr Mult(Matr A, Matr B) {
    steps++;
    int n = A.m.size();

    steps++;
    if (n == 2) {
        // дно рекурсии
        Matr C(n);
        C.m[0][0] = A.m[0][0] * B.m[0][0] + A.m[0][1] * B.m[1][0];
        C.m[0][1] = A.m[0][0] * B.m[0][1] + A.m[0][1] * B.m[1][1];
        C.m[1][0] = A.m[1][0] * B.m[0][0] + A.m[1][1] * B.m[1][0];
        C.m[1][1] = A.m[1][0] * B.m[0][1] + A.m[1][1] * B.m[1][1];
        steps += 16;
        return C;
    }
    else {
        int h = n / 2;
        steps++;
        // разбиение матрицы на 4
        Matr A11(h), A12(h), A21(h), A22(h);
        Matr B11(h), B12(h), B21(h), B22(h);

        // заполнение этих матриц значениями исходной
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < h; j++) {
                A11.m[i][j] = A.m[i][j];
                A12.m[i][j] = A.m[i][j + h];
                A21.m[i][j] = A.m[i + h][j];
                A22.m[i][j] = A.m[i + h][j + h];

                B11.m[i][j] = B.m[i][j];
                B12.m[i][j] = B.m[i][j + h];
                B21.m[i][j] = B.m[i + h][j];
                B22.m[i][j] = B.m[i + h][j + h];
                steps += 16;
            }
        }

        // вспомогательные матрицы
        Matr M1 = Mult(Sub(A12, A22), Add(B21, B22));
        Matr M2 = Mult(Add(A11, A22), Add(B11, B22));
        Matr M3 = Mult(Sub(A11, A21), Add(B11,B12));
        Matr M4 = Mult(Add(A11, A12), B22);
        Matr M5 = Mult(A11, Sub(B12, B22));
        Matr M6 = Mult(A22, Sub(B21, B11));
        Matr M7 = Mult(Add(A21, A22), B11);
        steps += 7;

        // результирующие матрицы
        Matr C11 = Add(Sub(Add(M2, M6), M4), M1); // M2 + M6 - M4 + M1
        Matr C12 = Add(M4,M5);
        Matr C21 = Add(M6,M7);
        Matr C22 = Sub(Add(Sub(M2, M7), M5), M3); // M2 - M7 + M5 - M3 
        steps += 4;
        Matr C(n);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < h; j++) {
                C.m[i][j] = C11.m[i][j];
                C.m[i][j + h] = C12.m[i][j];
                C.m[i + h][j] = C21.m[i][j];
                C.m[i + h][j + h] = C22.m[i][j];
                steps += 8;
            }
        }
        return C;
    }
}

int main() {
    ofstream res("res.txt");
    res << "n =     k =\n4       398\n8       3778\n16      30318\n32      227618\n64      1654798\n128     11829378\n256     83788718\n512     590453218\n1024    4148901198\n";

    /*cout << "n =\t" << "k = " << endl;
    for (int n = 4; n <= 1024; n *= 2)
    {
        steps = 0;
        Matr A(n);
        Matr B(n);
        Matr C(n);
        C = Mult(A, B);
        cout << n << "\t" << steps << endl;
    }
    return 0;*/
}

