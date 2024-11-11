#include <iostream>
#include <queue>

using namespace std;

class Graph {
private:
  int **adjMat;
  int size;

public:
  Graph(int s) : size(s) {
    adjMat = new int *[size];
    for (int i = 0; i < size; i++) {
      adjMat[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        adjMat[i][j] = 0;
      }
    }
  }

  void init_matrix() {
    cout << "ENTER ELEMENTS WITH SPACES: ";
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        cin >> adjMat[i][j];
      }
    }
    cout << "MATRIX INTIALIZED!" << endl;
  }

  bool remove_edge(int i1, int i2) {
    if (i1 >= size || i2 >= size)
      return false;
    adjMat[i1][i2] = 0;
    adjMat[i2][i1] = 0;
    return false;
  }

  bool add_edge(int i1, int i2) {
    if (i1 >= size || i2 >= size)
      return false;
    adjMat[i1][i2] = 1;
    adjMat[i2][i1] = 1;
    return true;
  }

  void bfs(int start) {
    bool *visited = new bool[size];
    for (int i = 0; i < size; i++)
      visited[i] = false;

    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";

      for (int j = 0; j < size; j++) {
        if (adjMat[vertex][j] != 0 && !visited[j]) {
          visited[j] = true;
          q.push(j);
        }
      }
    }

    cout << endl;
    delete[] visited;
  }

  void dfs(int start) {
    bool *visited = new bool[size];
    for (int i = 0; i < size; i++)
      visited[i] = false;
    dfsUtil(visited, start);
    cout << endl;
    delete[] visited;
  }

private:
  void dfsUtil(bool visited[], int start) {
    visited[start] = true;
    cout << start << " ";

    for (int j = 0; j < size; j++) {
      if (adjMat[start][j] != 0 && !visited[j]) {
        dfsUtil(visited, j);
      }
    }
  }
};

int main() {
  Graph g(8);
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 3);
  g.add_edge(1, 4);
  g.add_edge(2, 5);
  g.add_edge(2, 6);
  g.add_edge(3, 7);
  g.add_edge(4, 7);
  g.add_edge(5, 7);
  g.add_edge(6, 7);

  g.add_edge(1, 6);
  g.remove_edge(1, 6);

  g.bfs(0);
  g.dfs(0);

  return 0;
}
