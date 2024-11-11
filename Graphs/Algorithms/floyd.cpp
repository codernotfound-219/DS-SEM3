#include <iostream>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)

class Graph {
private:
  int **arr;
  int size;

public:
  Graph(int s) : size(s) {
    arr = new int *[size];
    loop(i, size) arr[i] = new int[size];
    loop(i, size) loop(j, size) arr[i][j] = 0;
  }

  bool checkUnfit(int i1, int i2) { return i1 >= size || i2 >= size; }

  bool addEdge(int i1, int i2, int w) {
    if (checkUnfit(i1, i2))
      return false;
    arr[i1][i2] = w;
    return true;
  }

public:
  void floydWarshall() {
    int **dist = new int *[size];
    loop(i, size) dist[i] = new int[size];
    loop(i, size) loop(j, size) dist[i][j] = arr[i][j]; // COPY ADJACENT MATRIX

    loop(i, size) loop(j, size) {
      if (dist[i][j] == 0)
        dist[i][j] = INT_MAX;
    }

    loop(k, size) loop(i, size) loop(j, size) {
      if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
          dist[i][k] + dist[k][j] < dist[i][j])
        dist[i][j] = dist[i][k] + dist[k][j];
    }

    printSolution(dist);
    cout << endl;

    loop(i, size) delete[] dist[i];
    delete[] dist;
  }

private:
  void printSolution(int **dist) {
    cout << "FLOYD WARSHALL : All pairs shortest path\n" << endl;
    cout << "\t";

    loop(i, size) cout << i << "\t";
    cout << "\n" << endl;

    loop(i, size) {
      cout << i << "\t";

      loop(j, size) {
        if (i == j) {
          cout << " " << "\t";
          continue;
        }

        if (dist[i][j] == INT_MAX)
          cout << "-" << "\t";
        else
          cout << dist[i][j] << "\t";
      }

      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  Graph g(8);

  g.addEdge(0, 2, 3);
  g.addEdge(1, 0, 9);
  g.addEdge(1, 6, 2);
  g.addEdge(2, 0, 4);
  g.addEdge(2, 5, 1);
  g.addEdge(3, 7, 2);
  g.addEdge(4, 7, 8);
  g.addEdge(5, 3, 4);
  g.addEdge(5, 7, 6);
  g.addEdge(6, 2, 3);
  g.addEdge(6, 4, 5);
  g.addEdge(7, 6, 1);

  g.floydWarshall();

  return 0;
}
