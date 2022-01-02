#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#define MAX(x, y) (x < y ? y : x)
#define MIN(x, y) (x > y ? y : x)

typedef struct {
  int length;
  int *path;
  int value;
} path;

path find_path(int **adj_matrix, const int size, int start, int target) {
  queue<int> q;

  bool *visited = new bool[size]{};

  int *ancestor = new int[size]{};
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
        if (nb == target)
          goto find_path;
      }
    }
  }

find_path:
  path p;
  stack<int> s;

  if (ancestor[target] == -1) {
    p.length = 0;
    return p;
  }

  while (target != start) {
    s.push(target);
    target = ancestor[target];
  }
  s.push(start);

  p.path = new int[s.size()]{};
  p.length = s.size();
  int i = 0;
  int value = INT16_MAX;
  while (!s.empty()) {
    p.path[i] = s.top();
    s.pop();
    if (0 < i) {
      int a = p.path[i - 1];
      int b = p.path[i];
      value = MIN(value, adj_matrix[a][b]);
    }
    i++;
  }
  p.value = value;

  return p;
}

int **ford_fulkerson(int **adj_matrix, const int size, int s, int t) {
  int **flow = new int *[size] {};
  for (int i = 0; i < size; i++)
    flow[i] = new int[size]{};

  path p = find_path(adj_matrix, size, s, t);
  while (p.length > 0) {
    for (int i = 0; i < p.length - 1; i++) {
      int a = p.path[i];
      int b = p.path[i + 1];
      adj_matrix[a][b] -= p.value;
      adj_matrix[b][a] += p.value;
      flow[a][b] += p.value;
    }
    p = find_path(adj_matrix, size, s, t);
  }

  return flow;
}
