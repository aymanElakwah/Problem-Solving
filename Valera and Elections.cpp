//http://codeforces.com/contest/369/problem/C
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

vector<vii> adjList;
vector<int> es;
vector<int> visited;
int road = -1;

void dfs(int u, bool problem) {
	visited[u] = 1;
	if (problem)
		road = u;
	const vii &list = adjList[u];
	for (int i = 0; i < list.size(); i++)
	{
		if (visited[list[i].first])
			continue;
		dfs(list[i].first, list[i].second == 2);
		if (road != -1 && list[i].second == 2)
		{
			es.push_back(road);
			road = -1;
		}
	}
}

int main() {
	int n;
	cin >> n;
	adjList.assign(n, vector<ii>());
	visited.assign(n, 0);
	for (int i = 0; i < n - 1; i++)
	{
		int x, y, t;
		cin >> x >> y >> t;
		x--; y--;
		adjList[x].push_back(ii(y, t));
		adjList[y].push_back(ii(x, t));
	}
	dfs(0, false);
	cout << es.size() << endl;
	for (int i = 0; i < es.size(); i++)
	{
		cout << es[i] + 1 << (i != es.size() - 1  ? " " : "");
	}
	return 0;
}
