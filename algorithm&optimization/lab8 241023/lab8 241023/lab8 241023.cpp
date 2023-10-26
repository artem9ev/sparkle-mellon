#include <iostream>

using namespace std;

void inputGraph(bool** g, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int k = i; k < n; k++)
		{
			cin >> g[i][k];
			g[k][i] = g[i][k];
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");

    int n; cin >> n;
	bool** graph = new bool*[n];
	int* mark = new int[n];
	int countVisited = 0;
	bool* isVisited = new bool[n];
	for (int i = 0; i < n; i++)
	{
		graph[i] = new bool[n];
		mark[i] = i;
		isVisited[i] = false;
	}
	inputGraph(graph, n);
	// является ли граф связным
	bool isSvyaz = true;
	for (int i = 0; i < n; i++)
	{
		bool v = false;
		for (int k = 0; k < n; k++)
		{
			if (i != k)
			{
				v = v || graph[i][k];
			}
		}
		if (v == false)
		{
			isSvyaz = false;
			break;
		}
	}
	if (!isSvyaz)
	{
		cout << "граф не является связным!" << endl;
	}
	else
	{
		bool isTree = true;
		int index = 0;
		isVisited[0] = true;
		countVisited++;
		do // что я блин делаю...
		{
			cout << "AAA" << countVisited << endl;
			for (int k = 0; k < n; k++)
			{
				if (graph[index][k] && !isVisited[k])
				{
					if (mark[k] == 0)
					{
						countVisited = n;
						isTree = false;
						break;
					}
					mark[k] = 0;
				}
			}
			for (int i = 0; i < n; i++)
			{
				if (mark[i] == 0 && !isVisited[i])
				{
					index = i;
					isVisited[i] = true;
					countVisited++;
					break;
				}
			}
		} while (countVisited < n);

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
