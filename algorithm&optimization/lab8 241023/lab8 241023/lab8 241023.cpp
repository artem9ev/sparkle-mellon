#include <iostream>
#include <queue>

using namespace std;

void inputGraph(int** g, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cin >> g[i][k];
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

	cout << "n = ";
    int n; cin >> n;
	int** graph = new int*[n];
	int* mark = new int[n];
	bool* isVisited = new bool[n];
	for (int i = 0; i < n; i++)
	{
		graph[i] = new int[n];
		mark[i] = i;
		isVisited[i] = false;
	}
	inputGraph(graph, n);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << graph[i][k] << ' ';
		}
		cout << endl;
	}
	// является ли граф связным
	bool isSvyaz = true;
	queue<int> q;
	q.push(0);
	isVisited[0] = true;
	while (q.size() > 0) {
		int index = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (isVisited[i] != true && graph[index][i] == 1)
			{
				q.push(i);
				isVisited[i] = true;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		isSvyaz = isSvyaz && isVisited[i];
		isVisited[i] = false;
	}
	cout << "svyaz: " << isSvyaz << endl;
	// 0 1 1 1 0 1 0 0 0 1 1 0 0 0 0 1 0 0 0 0 0 1 0 0 0
	// 0 0 1 0 0 0 0 0 1 1 1 0 0 0 0 0 1 0 0 1 0 1 0 1 0
	
	// проверяем на наличие циклов
	if (!isSvyaz)
	{
		cout << "граф не является связным!" << endl;
	}
	else
	{
		int countVisited = 0;
		bool isTree = true;
		q.push(0);
		while (countVisited < n)
		{
			int index = q.front();
			q.pop();
			isVisited[index] = true;
			countVisited++;
			cout << index << endl;
			for (int i = 0; i < n; i++)
			{
				if (graph[index][i] == 1 && !isVisited[i])
				{
					if (mark[i] == 0) // нашли цикл
					{
						isTree = false;
						countVisited = n;
						break;
					}
					mark[i] = 0;
					q.push(i);
				}
			}
		}

		if (isTree)
		{
			cout << "это дерево!";
		}
		else
		{
			cout << "это не дерево!!!";
		}
	}
	
}
