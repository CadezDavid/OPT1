#include "ford_fulkerson.h"
#include <fstream>

const char in[]{"graph.in"};

int main() {
  ifstream ifs(in);
  int size;
  ifs >> size;
  int u, v, w;
  ifs >> u >> v >> w;

  int **adj_matrix = new int *[2 * size + 1];
  for (int row = 0; row < 2 * size + 1; row++)
    adj_matrix[row] = new int[2 * size + 1];

  int x, y;
  while (ifs >> x >> y) {
    adj_matrix[2 * x + 1][2 * y] = 1;
    adj_matrix[2 * y + 1][2 * x] = 1;
  }

  for (int i = 0; i < size; i++)
    adj_matrix[2 * i][2 * i + 1] = 1;

  adj_matrix[2 * size][2 * u] = 1;
  adj_matrix[2 * size][2 * v] = 1;

  int **flow = ford_fulkerson(adj_matrix, 2 * size + 1, 2 * size, 2 * w);

  int flow_sum = 0;
  for (int i = 0; i < 2 * size + 1; i++)
    flow_sum += flow[2 * size][i];

  if (flow_sum == 2)
    printf("Obstaja pot med u (%i) in v (%i), ki gre skozi w (%i)\n", u, v, w);
  else
    printf("Ni poti med u (%i) in v (%i), ki gre skozi w (%i)\n", u, v, w);

  return 0;
}
