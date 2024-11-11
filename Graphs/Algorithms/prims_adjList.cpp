#include <iostream>
#include <queue>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)

class Graph {
private:
  struct Node {
    int val;
    int weight;
    Node *next;
    Node(int v, int w) : val(v), weight(w), next(NULL) {}
  };

  Node **arr;
  int size;

public:
  Graph(int s) : size(s) {
    arr = new Node *[size];

    loop(i, size) arr[i] = NULL;
  }

  bool checkUnfit(int i1, int i2) { return i1 >= size && i2 >= size; }

  bool checkUnfit(int i) { return i >= size; }

public:
  // PRIMARY
  bool addEdge(int i1, int i2, int w) {
    if (checkUnfit(i1, i2))
      return false;

    Node *nn1 = new Node(i2, w);
    Node *nn2 = new Node(i1, w);

    nn1->next = arr[i1];
    arr[i1] = nn1;

    nn2->next = arr[i2];
    arr[i2] = nn2;

    return true;
  }

  bool checkExistence(int i1, int i2) {
    Node *tmp = arr[i1];

    while (tmp) {
      if (tmp->val == i2)
        return true;
      tmp = tmp->next;
    }

    return false;
  }

  bool removeVertex(int i1, int i2) {
    Node *tmp = arr[i1];

    if (tmp == NULL)
      return false;
    if (tmp->val == i2) {
      arr[i1] = tmp->next;
      delete tmp;
      return true;
    }

    while (tmp->next->val != i2)
      tmp = tmp->next;
    Node *del = tmp->next;
    tmp->next = del->next;
    delete del;
    return true;
  }

  bool removeEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;
    if (!checkExistence(i1, i2) || !checkExistence(i2, i1))
      return false;

    return removeVertex(i1, i2) && removeVertex(i2, i1);
  }

public:
  // TRAVERSAL
  void bfs(int s) {
    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;

    queue<int> q;

    visited[s] = true;
    q.push(s);

    cout << "BFS: ";

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";

      Node *tmp = arr[vertex];
      while (tmp) {
        if (!visited[tmp->val]) {
          visited[tmp->val] = true;
          q.push(tmp->val);
        }
        tmp = tmp->next;
      }
    }

    cout << endl;
    delete[] visited;
  }

  void dfs(int s) {
    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;
    ;

    cout << "DFS: ";
    dfsUtil(visited, s);
    cout << endl;
    delete[] visited;
  }

private:
  void dfsUtil(bool visited[], int s) {
    visited[s] = true;
    cout << s << " ";

    Node *tmp = arr[s];
    while (tmp) {
      if (!visited[tmp->val])
        dfsUtil(visited, tmp->val);
      tmp = tmp->next;
    }
  }

public:
  // PRIMS
  void prim(int start) {
    bool *visited = new bool[size];
    int *parent = new int[size];
    int *key = new int[size];

    loop(i, size) visited[i] = false, key[i] = INT_MAX, parent[i] = -1;

    int cost = 0;
    key[start] = 0;

    cout << "\nPRIMS MST:" << endl;
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
        cout << parent[u] << " - " << u << "\t" << key[u] << endl;
      }

      Node *tmp = arr[u];
      while (tmp) {
        int dest = tmp->val;
        int weight = tmp->weight;

        if (!visited[dest] && weight < key[dest]) {
          key[dest] = weight;
          parent[dest] = u;
        }

        tmp = tmp->next;
      }
    }

    cout << "\nCOST: " << cost << endl;
  }
};

int main() {
  int size = 5;
  Graph g(size);

  g.addEdge(0, 1, 2);
  g.addEdge(0, 3, 6);
  g.addEdge(1, 2, 3);
  g.addEdge(1, 3, 8);
  g.addEdge(1, 4, 5);
  g.addEdge(2, 4, 7);
  g.addEdge(3, 4, 9);

  g.bfs(0);
  g.dfs(0);

  g.prim(0);

  return 0;
}
