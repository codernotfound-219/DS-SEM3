#include <iostream>
#include <queue>
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

public:
  // PRIMARY
  bool checkUnfit(int i1, int i2) { return i1 >= size && i2 >= size; }

  bool checkUnfit(int i) { return i >= size; }

  bool addEdge(int i1, int i2, int w) {
    if (checkUnfit(i1, i2))
      return false;
    arr[i1][i2] = w;
    arr[i2][i1] = w;
    return true;
  }

  bool removeEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;
    arr[i1][i2] = 0;
    arr[i2][i1] = 0;
    return true;
  }

public:
  // TRAVERSALS
  void bfs(int s) {
    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;
    queue<int> q;

    cout << "BFS: ";
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";

      loop(i, size) {
        if (arr[vertex][i] != 0 && !visited[i]) {
          visited[i] = true;
          q.push(i);
        }
      }
    }

    cout << endl;
    delete[] visited;
  }

  void dfs(int s) {
    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;
    cout << "DFS: ";
    dfsUtil(visited, s);
    cout << endl;
    delete[] visited;
  }

private:
  void dfsUtil(bool visited[], int s) {
    visited[s] = true;
    cout << s << " ";

    loop(i, size) {
      if (arr[s][i] != 0 && !visited[i])
        dfsUtil(visited, i);
    }
  }

public:
  // PRIMS
  void prim(int start) {
    bool *visited = new bool[size];
    int *key = new int[size];
    int *parent = new int[size];

    loop(i, size) visited[i] = false, key[i] = INT_MAX, parent[i] = -1;

    int cost = 0;
    key[start] = 0;

    cout << "\nPRIMS MST: " << endl;
    cout << "EDGE\tWEIGHT" << endl;

    loop(count, size) {
      int u = -1;
      int minKey = INT_MAX;

      loop(v, size) {
        if (!visited[v] && key[v] < minKey)
          u = v, minKey = key[v];
      }

      if (u == -1)
        break;

      visited[u] = true;
      cost += key[u];

      if (parent[u] != -1) {
        cout << parent[u] << " - " << u << "\t" << arr[u][parent[u]] << endl;
      }

      loop(v, size) {
        if (arr[u][v] != 0 && !visited[v] && arr[u][v] < key[v]) {
          parent[v] = u;
          key[v] = arr[u][v];
        }
      }
    }

    cout << "\nCOST: " << cost << endl;
  }

public:
  // DISPLAY
  void printMatrix() {
    cout << "ADJACENCY MATRIX:\n" << endl;
    cout << "\t";
    loop(i, size) cout << i << "\t";
    cout << "\n" << endl;

    loop(i, size) {
      cout << i << "\t";
      loop(j, size) {
        if (arr[i][j] == 0)
          cout << "-" << "\t";
        else
          cout << arr[i][j] << "\t";
      }

      cout << endl;
    }

    cout << endl;
  }
};

int main() {
  Graph g(5);

  g.addEdge(0, 1, 2);
  g.addEdge(0, 2, 3);
  g.addEdge(0, 3, 9);
  g.addEdge(0, 4, 44);
  g.addEdge(1, 3, 21);
  g.addEdge(1, 4, 12);
  g.addEdge(2, 4, 9);

  g.printMatrix();
  g.prim(0);

  return 0;
}
