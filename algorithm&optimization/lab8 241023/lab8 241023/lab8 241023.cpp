#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void inputGraph(vector<vector<int> > &g) {
	for (int i = 0; i < g.size(); i++)
		for (int k = 0; k < g.size(); k++)
			cin >> g[i][k];
}

bool isTree(vector<vector<int> >& graph) {
	int n = graph.size();
	vector<int> parent(n, -1);
	vector<bool> isVisited(n, false);
	queue<int> q;
	q.push(0);
	isVisited[0] = true;
	bool isSvyaz = true;
	bool hasCycle = false;
	while (q.size() > 0 && !hasCycle) {
		int index = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (!isVisited[i] && graph[index][i] == 1)
			{
				q.push(i);
				parent[i] = index;
				isVisited[i] = true;
			}
			else if (isVisited[i] && i != parent[index] && graph[index][i] == 1) {
				hasCycle = true;
				break;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		isSvyaz = isSvyaz && isVisited[i];
		isVisited[i] = false;
	}
	return isSvyaz && !hasCycle;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "n = ";
    int n; cin >> n;
	vector<vector<int> > graph(n, vector<int>(n));
	inputGraph(graph);

	
	if (isTree(graph))
		cout << "это дерево!";
	else
		cout << "это не дерево!";
}
