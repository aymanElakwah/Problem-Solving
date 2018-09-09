#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node {
	int c, w, edgeIndex;
	node(int c, int w, int edgeIndex) : c(c), w(w), edgeIndex(edgeIndex) {
	}
};

vector<int> realW;
vector<int> cycleW;

struct edge {
	int c1, c2;
	bool visited = false;
	int weight = 0;
	bool cycle = false;
	int realWeight = 0;
	edge(int weight) :weight(weight) {}
	bool operator<(const edge &e) {
		return realWeight < e.realWeight;
	}
	void calcRealWeight() {
		if (realW[c1] == weight)
			realWeight = weight + cycleW[c1];
		if (realW[c2] == weight)
			if (realWeight == 0)
				realWeight = weight + cycleW[c2];
			else
				realWeight = min(realWeight, weight + cycleW[c2]);
		if (realWeight == 0)
			realWeight = weight;
	}
};

vector<vector<node>> adjList;
int visited[4];
vector<edge> edges;
int degree[4];
int odd;
int sum;
vector<edge> removeEdges;

void dfs(int u) {
	visited[u] = 1;
	if (degree[u] % 2 == 1) {
		odd++;
	}
	for (int i = 0; i < adjList[u].size(); i++)
	{
		if (!edges[adjList[u][i].edgeIndex].visited) {
			edges[adjList[u][i].edgeIndex].visited = 1;
			sum += adjList[u][i].w;
			edges[adjList[u][i].edgeIndex].calcRealWeight();
			if (!edges[adjList[u][i].edgeIndex].cycle)
				removeEdges.push_back(edges[adjList[u][i].edgeIndex]);
		}
	}
	for (int i = 0; i < adjList[u].size(); i++)
	{
		if (!visited[adjList[u][i].c]) {
			dfs(adjList[u][i].c);
		}
	}
}

int main() {
	int n; cin >> n;
	adjList.assign(4, vector<node>());
	realW.assign(4, 0);
	cycleW.assign(4, 0);
	edges.assign(n, 0);
	for (int i = 0; i < n; i++)
	{
		int c1, w, c2;
		cin >> c1 >> w >> c2;
		c1--;
		c2--;
		degree[c1]++;
		degree[c2]++;
		edges[i].weight = w;
		edges[i].c1 = c1;
		edges[i].c2 = c2;
		if (c1 != c2) {
			realW[c1] += w;
			realW[c2] += w;
			adjList[c1].push_back(node(c2, w, i));
			adjList[c2].push_back(node(c1, w, i));
		}
		else {
			edges[i].cycle = true;
			cycleW[c1] += w;
			adjList[c1].insert(adjList[c1].begin(), node(c2, w, i));
		}
	}
	int ans = 0;
	for (int i = 0; i < adjList.size(); i++)
	{
		if (!visited[i]) {
			removeEdges.clear();
			odd = 0;
			sum = 0;
			dfs(i);
			if (odd <= 2) {
				ans = max(ans, sum);
			}
			else {
				sort(removeEdges.begin(), removeEdges.end());
				ans = max(ans, sum - removeEdges[0].realWeight);
			}
		}
	}
	cout << ans;
	return 0;
}
