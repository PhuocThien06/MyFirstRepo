#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
using namespace std;
vector<vector<int>> convertMatrixToList(const string& filename) {
	fstream fin(filename);
	int n;
	fin >> n;
	vector < vector<int>> adjList(n);
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			int val;
			fin >> val;
			if (val == 1)
				adjList[i].push_back(j);
		}
	}
	fin.close();
	return adjList;
}
vector<vector<int>> convertListToMatrix(const string& filename) {
	fstream fin(filename);
	int n;
	fin >> n;
	vector<vector<int>> adjMatrix(n, vector<int>(0));
	for (int i = 0;i < n;i++) {
		string line;
		getline(fin >> ws, line);
		istringstream iss(line);
		int u;
		while (iss >> u) {
			adjMatrix[i][u] = 1;
		}
	}
	fin.close();
	return adjMatrix;
}
bool isDirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i])
				return true;
		}
	}
	return false;
}
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix) {
	int dem = 0;
	int n = adjMatrix.size();
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (adjMatrix[i][j] == 1)
				dem++;
		}
	}
	if (!isDirected(adjMatrix)) return dem /= 2;
	return dem;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> isolated;
	int n = adjMatrix.size();
	for (int i = 0;i < n;i++) {
		bool hasEdge = false;
		for (int j = 0;j < n;j++) {
			if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
				hasEdge = true;
				break;
			}
		}
		if (!hasEdge)
			isolated.push_back(i);
	}
	return isolated;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	if (!isDirected(adjMatrix)) {
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				if (i == j) {
					if (adjMatrix[i][j] == 1)
						return false;
				}
				else {
					if (adjMatrix[i][j] != 1 || adjMatrix[j][i] != 1)
						return false;
				}
			}
		}
	}
	return true;
}
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix){
	int n = adjMatrix.size();
	vector<int> color(n, -1);// -1: ch?a tô màu, 0 và 1 là 2 nhóm
	for (int start = 0;start < n;start++) {
		if (color[start] == -1) {
			queue<int> q;
			q.push(start);
			color[start] = 0;
			while (q.empty()) {
				int u = q.front();
				q.pop();
				for (int v = 0;v < n;v++) {
					if (adjMatrix[u][v]) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
						}
						else if (color[u] == color[v])
							return false;
					}
				}
			}
		}
	}
	return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1); // -1: ch?a tô màu, 0 và 1 là 2 nhóm
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		if (color[i] == -1) {
			color[i] = 0;
			q.push(i);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int v = 0; v < n; ++v) {
					if (adjMatrix[u][v]) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[v] == color[u]) {
							return false; 
						}
					}
				}
			}
		}
	}
	int groupA = 0, groupB = 0;
	for (int c : color) {
		if (c == 0) groupA++;
		else groupB++;
	}
	int edgeCount = 0;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (adjMatrix[i][j]) edgeCount++;
	return edgeCount == groupA * groupB;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> undirectedMatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
				undirectedMatrix[i][j] = 1;
				undirectedMatrix[j][i] = 1;
			}
		}
	}
	return undirectedMatrix;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> complement(n, vector<int>(n, 0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j && adjMatrix[i][j] == 0) {
				complement[i][j] = 1;
			}
		}
	}
	return complement;
}
void dfs(int u, const vector<vector<int>>& graph, vector<bool>& visited) {
	visited[u] = true;
	int n = graph.size();
	for (int v = 0; v < n; ++v) {
		if (graph[u][v] > 0 && !visited[v]) {
			dfs(v, graph, visited);
		}
	}
}
bool isGraphConnected(const vector<vector<int>>& graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	int start = -1;
	for (int i = 0; i < n; ++i) {
		int deg = 0;
		for (int j = 0; j < n; ++j) deg += graph[i][j];
		if (deg > 0) {
			start = i;
			break;
		}
	}
	if (start == -1) return true; 
	dfs(start, graph, visited);
	for (int i = 0; i < n; ++i) {
		int deg = 0;
		for (int j = 0; j < n; ++j) deg += graph[i][j];
		if (deg > 0 && !visited[i]) return false;
	}
	return true;
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	vector<int> eulerCycle;
	stack<int> currPath;
	for (int i = 0; i < n; ++i) {
		int deg = 0;
		for (int j = 0; j < n; ++j) deg += graph[i][j];
		if (deg % 2 != 0) return {}; 
	}
	if (!isGraphConnected(graph)) return {};
	currPath.push(0); 
	while (!currPath.empty()) {
		int v = currPath.top();
		int i;
		for (i = 0; i < n; ++i) {
			if (graph[v][i] > 0) break;
		}
		if (i == n) {
			eulerCycle.push_back(v);
			currPath.pop();
		}
		else {
			currPath.push(i);
			graph[v][i]--;
			graph[i][v]--;
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (graph[i][j] > 0)
				return {}; 
	reverse(eulerCycle.begin(), eulerCycle.end());
	return eulerCycle;
}
void dfsUtil(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& tree) {
	visited[u] = true;
	int n = adjMatrix.size();
	for (int v = 0; v < n; ++v) {
		if (adjMatrix[u][v] == 1 && !visited[v]) {
			tree[u][v] = 1;
			tree[v][u] = 1;
			dfsUtil(v, adjMatrix, visited, tree);
		}
	}
}
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	dfsUtil(start, adjMatrix, visited, tree);
	return tree;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] == 1 && !visited[v]) {
				visited[v] = true;
				tree[u][v] = 1;
				tree[v][u] = 1;
				q.push(v);
			}
		}
	}
	return tree;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;
	q.push(u);
	visited[u] = true;
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		if (curr == v) return true;
		for (int i = 0; i < n; ++i) {
			if (adjMatrix[curr][i] == 1 && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return false;
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	const int INF = std::numeric_limits<int>::max();
	vector<int> dist(n, INF);
	vector<int> parent(n, -1);
	vector<bool> visited(n, false);
	dist[start] = 0;
	for (int i = 0; i < n; ++i) {
		int u = -1;
		int minDist = INF;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && dist[j] < minDist) {
				minDist = dist[j];
				u = j;
			}
		}
		if (u == -1) break;
		visited[u] = true;

		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] > 0 && !visited[v]) {
				int alt = dist[u] + adjMatrix[u][v];
				if (alt < dist[v]) {
					dist[v] = alt;
					parent[v] = u;
				}
			}
		}
	}
	vector<int> path;
	if (dist[end] == INF) return path; 
	for (int v = end; v != -1; v = parent[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	const int INF = std::numeric_limits<int>::max();
	vector<int> dist(n, INF);
	vector<int> parent(n, -1);
	dist[start] = 0;
	for (int k = 0; k < n - 1; ++k) {
		for (int u = 0; u < n; ++u) {
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v] != 0 && dist[u] != INF) {
					int alt = dist[u] + adjMatrix[u][v];
					if (alt < dist[v]) {
						dist[v] = alt;
						parent[v] = u;
					}
				}
			}
		}
	}
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] != 0 && dist[u] != INF) {
				if (dist[u] + adjMatrix[u][v] < dist[v]) {
					return {};
				}
			}
		}
	}
	vector<int> path;
	if (dist[end] == INF) return path;
	for (int v = end; v != -1; v = parent[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}

