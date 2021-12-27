#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs(vector<vector<int>> adj_matrix, int start, int target) {
  const int size = adj_matrix.size();
  queue<int> q;
  vector<bool> visited(size, false);
  vector<int> ancestor(size);
  for (int i = 0; i < size; i++)
    ancestor[i] = -1;

  int curr;
  q.push(start);
  while (!q.empty()) {
    curr = q.front();
    q.pop();
    visited[curr] = true;
    for (int nb = 0; nb < size; nb++) {
      if (!visited[nb] && adj_matrix[curr][nb] > 0) {
        q.push(nb);
        ancestor[nb] = curr;
      }
    }
  }

  if (!visited[target])
    return {};

  vector<int> path;
  while (target != start) {
    path.push_back(target);
    target = ancestor[target];
  }
  path.push_back(start);
  reverse(path.begin(), path.end());
  return path;
}

int ford_fulkerson(vector<vector<int>> adj_matrix, int s, int t) {
  int flow = 0;
  int size = adj_matrix.size();

  vector<int> path = bfs(adj_matrix, s, t);
  while (!path.empty()) {
    for (int i = 0; i < path.size() - 1; i++) {
      adj_matrix[path[i]][path[i + 1]]--;
      adj_matrix[path[i + 1]][path[i]]++;
    }
    flow++;
    path = bfs(adj_matrix, s, t);
  }

  return flow;
}
