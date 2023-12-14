#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

long steps = 0;

int n, m, k; // m - высота, k - длина
int** graph;
int* stepen;

void generateSimpleReshetka() {
    graph = new int*[n];
    stepen = new int[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            graph[i][k] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        stepen[i] = 0;
        for (int k = 0; k < n; k++)
        {
            if (i == k + 1 || k == i + 1)
            {
                graph[i][k] = 1;
            }
            if (graph[i][k] == 1)
            {
                stepen[i]++;
            }
        }
    }
}

void input() {
    graph = new int* [n];
    stepen = new int[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        stepen[i] = 0;
        for (int k = 0; k < n; k++) {
            cin >> graph[i][k];
            if (graph[i][k] == 1)
            {
                stepen[i]++;
            }
        }
    }
}

bool isReshetka() {
    //cout << "n: " << n << endl;
    queue<int> q;
    q.push(0);
    bool* isVisited = new bool[n];
    int vert;
    for (int i = 1; i < n; i++)
    {
        isVisited[i] = false;
        steps++;
    }
    isVisited[0] = true;
    steps += 3;
    while (q.size() > 0) // посещаем вершины помечая их как пройденные
    {
        steps++;
        vert = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            steps += 2;
            if (graph[vert][i] == 1 && isVisited[i] == false)
            {
                steps++;
                isVisited[i] = true;
                q.push(i);
            }
        }
    }
    for (int i = 0; i < n; i++) // проверяем на наличие не пройденных вершин
    {
        steps++;
        if (isVisited[i] == false)
        {
            //cout << "не связный граф! - " << i << endl;
            steps++;
            return false;
        }
    }
    //cout << "связный граф!" << endl;

    int min = 3;
    int start;
    int* color = new int[n];
    int maxColor = 0;
    steps += 3;
    for (int i = 0; i < n; i++)
    {
        steps += 3;
        if (stepen[i] > 4)
        {
            steps++;
            //cout << "stepen > 4 - " << i << endl;
            return false;
        }
        color[i] = 0;
        if (stepen[i] < min)
        {
            steps += 2;
            min = stepen[i];
            start = i;
        }
    }
    steps++;
    if (min > 2)
    {
        steps++;
        //cout << "min > 2!!!" << endl;
        return false;
    }
    
    /*
    Красим граф подобным образом:
    1 2 3 4 5
    2 3 4 5 6
    3 4 5 6 7

    m = максимальному кол-ву встречи одного из цветов графа = 3
    k = кол-во различных цветов вершин - m  + 1 = 7 - 3 + 1 = 5
    */
    q.push(start);
    steps += 1;
    color[start] = 1;
    while (q.size() > 0) // красим по диогонали не связные вершины графа
    {
        steps += 2;
        int vert = q.front();
        q.pop();
        if (color[vert] > maxColor)
        {
            steps++;
            maxColor = color[vert];
        }
        for (int i = 0; i < n; i++)
        {
            if (graph[vert][i] == 1 && color[i] == 0)
            {
                steps += 4;
                q.push(i);
                color[i] = color[vert] + 1;
            }
            else if (graph[vert][i] == 1 && color[i] != color[vert] - 1 && color[i] < color[vert])
            {
                steps += 9;
                //cout << "1 rebro - " << vert << "[" << color[vert] << "] - " << i << "[" << color[i] << "]" << endl;
                return false;
            }
            else if (graph[vert][i] == 1 && color[i] == color[vert])
            {
                steps += 12;
                //cout << "2 rebro - " << vert << "[" << color[vert] << "] - " << i << "[" << color[i] << "]" << endl;
                return false;
            }
        }
    }
    // граф - решетка, вычисляем m и k;
    m = 0;
    steps++;
    for (int c = 0; c < maxColor; c++)
    {
        steps += 2;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            steps++;
            if (color[i] == c)
            {
                steps += 2;
                count++;
            }
        }
        if (m < count)
        {
            steps++;
            m = count;
        }
    }
    steps += 4;
    k = maxColor - m + 1;
    return true;
}
/*
9
0 1 1 0 0 1 0 0 1
1 0 1 0 1 0 1 0 0
1 1 0 0 1 1 1 0 0
0 0 0 0 1 0 1 1 1
0 1 1 1 0 0 0 1 0
1 0 1 0 0 0 1 0 1
0 1 1 1 0 1 0 0 0
0 0 0 1 1 0 0 0 1
1 0 0 1 0 1 0 1 0

9
0  1  0  0  1  0  0  0  0
1  0  0  1  0  0  0  0  0
0  0  0  0  0  0  0  1  1
0  1  0  0  0  0  0  1  0
1  0  0  0  0  1  0  0  0
0  0  0  0  1  0  1  0  0
0  0  0  0  0  1  0  0  1
0  0  1  1  0  0  0  0  0
0  0  1  0  0  0  1  0  0

9
0  1  0  0  0  0  0  0  0
1  0  0  1  0  0  0  0  0
0  0  0  1  0  0  0  0  0
0  1  1  0  0  0  0  1  0
0  0  0  0  0  1  0  0  0
0  0  0  0  1  0  1  0  1
0  0  0  0  0  1  0  0  0
0  0  0  1  0  0  0  0  0
0  0  0  0  0  1  0  0  0

9
0  1  0  0  1  0  0  0  0
1  0  0  1  0  0  0  0  0
0  0  0  1  0  0  0  0  0
0  1  1  0  0  0  0  1  0
1  0  0  0  0  0  0  0  0
0  0  0  0  0  0  1  0  0
0  0  0  0  0  1  0  1  0
0  0  0  1  0  0  1  0  0
0  0  0  0  0  0  0  0  0

8
0  0  1  0  1  0  0  0
0  0  0  1  0  0  0  0
1  0  0  1  0  0  0  1
0  1  1  0  0  0  0  1
1  0  0  0  0  0  0  0
0  0  0  0  0  0  1  0
0  0  0  0  0  1  0  1
0  0  1  1  0  0  1  0
*/

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "тесты с положительным результатом:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "n = ";
        cin >> n;
        input();
        if (isReshetka()) {
            cout << "граф - решетка" << endl << endl;
        }
        else {
            cout << "граф - не решетка" << endl << endl;
        }
    }
    cout << endl << "тесты с отрицательным результатом:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "n = ";
        cin >> n;
        input();
        if (isReshetka()) {
            cout << "граф - решетка" << endl << endl;
        }
        else {
            cout << "граф - не решетка" << endl << endl;
        }
    }
    ofstream file("res.txt");
    for (int i = 4; i <= 20; i++)
    {
        n = i;
        generateSimpleReshetka();
        isReshetka();
        file << fixed << i << "\t" << steps << endl;
    }
    return 0;
}
