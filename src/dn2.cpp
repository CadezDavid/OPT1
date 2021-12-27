#include "ford_fulkerson.h"
#include <fstream>

const char in[]{"graph.in"};

int main() {
  ifstream ifs(in);
  int size;
  ifs >> size;
  int u, v, w;
  ifs >> u >> v >> w;

  vector<vector<int>> adj_matrix(2 * size, vector<int>(2 * size, 0));
  int x, y, c;
  while (ifs >> x >> y) {
    adj_matrix[2 * x + 1][2 * y] = 1;
    adj_matrix[2 * y + 1][2 * x] = 1;
  }

  for (int i = 0; i < size; i++)
    adj_matrix[2 * i][2 * i + 1] = 1;

  for (int i = 0; i < 2 * size; i++)
    adj_matrix[i].push_back(0);
  adj_matrix.push_back(vector<int>(2 * size + 1));
  adj_matrix[2 * size][2 * u] = 1;
  adj_matrix[2 * size][2 * v] = 1;

  int max_flow = ford_fulkerson(adj_matrix, 2 * size, 2 * w);
  if (max_flow == 2)
    cout << "Obstaja pot med u (" << u << ") in v (" << v
         << "), ki gre skozi w (" << w << ")" << endl;
  else
    cout << "Ni poti med u (" << u << ") in v (" << v << "), ki gre skozi w ("
         << w << ")" << endl;

  return 0;
}
