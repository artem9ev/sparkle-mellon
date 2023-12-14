#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int n;
int** graph;
int steps = 0;
vector<vector<int> > circles;

// создает случайный граф g
void generateG() {
	graph = new int* [n];
	for (int i = 0; i < n; i++)
		graph[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			if (i == k) {
				graph[i][k] = 0;
			}
			else if (k > i) {
				graph[i][k] = rand() % 2;
				graph[k][i] = graph[i][k];
			}
		}
	}
}

void input() {
	graph = new int* [n];
	for (int i = 0; i < n; i++)
		graph[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			
			cin >> graph[i][k];
		}
	}
}

bool hasSameCircle(vector<int> path) {
	steps += 2;
	bool hasSamePath = false;
	for (int j = 0; j < circles.size() && !hasSamePath; j++)
	{
		steps++;
		if (path.size() == circles[j].size())
		{
			steps += 1 + n;
			hasSamePath = true;
			vector<bool> isUsedVert(n, false);
			for (int r = 0; r < circles[j].size(); r++)
			{
				for (int k = 0; k < n; k++)
				{
					steps++;
					if (circles[j][r] == k)
					{
						steps++;
						isUsedVert[k] = true;
						break;
					}
				}
			}
			for (int k = 0; k < path.size(); k++)
			{
				steps++;
				if (isUsedVert[path[k]] == false)
				{
					steps++;
					hasSamePath = false;
				}
			}
		}
	}
	return hasSamePath;
}

void getCircles(int start, int v, int l, vector<bool> isVisited, vector<int> path = vector<int>()) {
	isVisited[v] = true;
	path.push_back(v);
	l++;
	steps += 3;
	for (int i = 0; i < n; i++)
	{
		steps += 6;
		if (i == start && graph[v][i] == 1 && l > 2)
		{
			steps += 4;
			bool hasSamePath = hasSameCircle(path);
			int min = n, id = -1;
			for (int r = 0; r < path.size(); r++)
			{
				steps++;
				if (path[r] < min)
				{
					min = path[r];
					id = r;
				}
			}
			for (int r = 0; r < id; r++)
			{
				steps += 3;
				int t = path[0];
				for (int w = 1; w < path.size(); w++)
				{
					steps += 2;
					path[w - 1] = path[w];
				}
				path[path.size() - 1] = t;
			}
			// нашел цикл
			if (!hasSamePath)
			{
				circles.push_back(path);
			}
		}
		if (v != i && graph[v][i] == 1 && isVisited[i] == false)
		{
			// иду в глубину по смежным вершинам
			getCircles(start, i, l, isVisited, path);
		}
	}
}

int countCircles() {
	circles = vector<vector<int> >();
	for (int i = 0; i < n; i++)
	{  
		// получаю все возможные циклы в графе
		getCircles(i, i, 0, vector<bool>(n, false));
	}
	for (int i = 0; i < circles.size(); i++)
	{
		// сортирую их по длине цепочки вершин
		for (int k = 0; k < circles.size(); k++)
		{
			steps++;
			if (circles[i].size() < circles[k].size())
			{
				steps += 3;
				vector<int> t = circles[i];
				circles[i] = circles[k];
				circles[k] = t;
			}
		}
	}
	// УДАЛИТЬ ЭТОТ ВЫВОД ПОТОМ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int i = 0; i < circles.size(); i++)
	{
		cout << i << " -> circle: ";
		for (int k = 0; k < circles[i].size(); k++)
		{
			cout << " " << circles[i][k];
		}
		cout << endl;
	}
	steps += 2;
	int maxCount = 0;
	// перебор перебор перебор...
	for (int i = 0; i < circles.size(); i++)
	{
		steps++;
		int count = 1; // считаю сколько непересекающихся циклов в графе
		vector<bool> isDeleted(n, false);
		for (int j = 0; j < circles[i].size(); j++)
		{
			steps++;
			isDeleted[circles[i][j]] = true; // "удаляю" вершины i-го цикла
		}
		// перебираю все циклы...
		for (int k = 0; k < circles.size(); k++)
		{
			steps += 3;
			if (circles[i] == circles[k])
			{
				continue;
			}
			bool canPlaceCircle = true;
			for (int j = 0; j < circles[k].size(); j++)
			{
				steps++;
				if (isDeleted[circles[k][j]] == true) // если вершина удалена, то не смогу разместить второй цикл
				{
					steps++;
					canPlaceCircle = false;
					break;
				}
			}
			if (canPlaceCircle == true)
			{
				for (int j = 0; j < circles[k].size(); j++)
				{
					steps++;
					isDeleted[circles[k][j]] = true; // "удаляю" вершины i-го цикла
				}
				steps += 3;
				count++;
				if (maxCount < count)
				{
					steps+= 2;
					maxCount = count;
					if (maxCount > 1)
					{
						return maxCount;
					}
				}
			}
		}
		cout << i << " -> " << count << endl;
	}
	return maxCount;
}

/*
0 1 0 0 1 1
1 0 1 1 0 0
0 1 0 1 0 0
0 1 1 0 1 0
1 0 0 1 0 1
1 0 0 0 1 0
*/

/*
0 1 1 0 1 0 0 1
1 0 1 0 0 0 0 1
1 1 0 1 0 0 0 0
0 0 1 0 1 0 0 0
1 0 0 1 0 1 0 0
0 0 0 0 1 0 1 1
0 0 0 0 0 1 0 1
1 1 0 0 0 1 1 0
*/

int main()
{
	setlocale(LC_ALL, "RUS");
	ofstream res("res.txt");

	cout << "n = "; cin >> n;
	input();

	/*float sum[13];
	int i = 0;
	for (n = 3; n <= 15; n++, i++)
	{
		sum[i] = 0;
		for (int k = 0; k < 2000; k++)
		{
			steps = 0;
			generateG();
			countCircles();
			sum[i] += steps / (float)2000;
		}
		cout << endl << "--- " << n << endl << endl;
		res << fixed << n << "\t" << sum[i] << endl;
	}*/
	
	cout << (countCircles() > 1 ? "да" : "нет");
}