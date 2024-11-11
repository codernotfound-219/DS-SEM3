#include <iostream>
using namespace std;

#define loop(i, n) for(int i=0; i<n; i++)

class Graph {
private:
  int **arr;
  int size;
public:
  Graph(int s) : size(s) {
    arr = new int*[size];
    loop(i, size) arr[i] = new int[size];
    loop(i, size) loop(j, size) arr[i][j] = 0;
  }

  bool checkUnfit(int i1, int i2) {
    return i1 >= size || i2 >= size;
  }

  bool addEdge(int i1, int i2, int w) {
    if (checkUnfit(i1, i2)) return false;
    arr[i1][i2] = w;
    return true;
  }

public:
  void dijkstra(int start) {
    int *dist = new int[size];
    bool *visited = new bool[size];
    
    loop(i, size) dist[i] = INT_MAX, visited[i] = false;

    dist[start] = 0;

    loop(count, size-1) {
      int u = minIndex(dist, visited);
      visited[u] = true;
      
      loop(v, size) {
        if (!visited[v] && arr[u][v] != 0 && dist[u] != INT_MAX
            && dist[u] + arr[u][v] < dist[v]) {
          dist[v] = dist[u] + arr[u][v];
        }
      }
    }

    printSolution(dist);
    cout << endl;
    delete[] dist;
    delete[] visited;
  }

private:
  int minIndex(int dist[], bool visited[]) {
    int minimum = INT_MAX, min_index = -1;

    loop(v, size) {
      if (!visited[v] && dist[v] <= minimum) {
        minimum = dist[v];
        min_index = v;
      }
    }
    return min_index;
  }

  void printSolution(int dist[]) {
    cout << "VERTEX\tDIST. FROM SOURCE" << endl;
    loop(i, size) {
      cout << "  " << i << "\t\t";
      if (dist[i] == INT_MAX) {
        cout << "-INF-" << endl;
      } else {
        cout << dist[i] << endl;
      }
    }
  }
};

int main() {
  Graph g(5);

  g.addEdge(0, 1, 10);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 2);
  g.addEdge(1, 2, 1);
  g.addEdge(2, 1, 4);
  g.addEdge(2, 3, 8);
  g.addEdge(2, 4, 2);
  g.addEdge(3, 4, 7);
  g.addEdge(4, 3, 9);

  g.dijkstra(0);

  return 0;
}
