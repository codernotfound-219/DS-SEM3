#include <iostream>
using namespace std;

#define loop(i, n) for(int i = 0; i<n; i++)

struct Edge {
  int src,  dest,  weight;
  Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class disJointSet {
private:
  int *arr;
  int size;
public:
  disJointSet(int s) : size(s) {
    arr = new int[size];
    loop(i, size) arr[i] = -1;
  }
  
  int find(int v) {
    int pos = v;
    while (arr[pos] > 0) pos = arr[pos];
    return pos;
  }

  bool isConnected(int u, int v) {
    return find(u) == find(v) ? true : false;
  }

  void weightedUnion(int u, int v) {
    int par_u = find(u);
    int par_v = find(v);;

    if (arr[par_u] < arr[par_v]) {
      arr[par_u] += arr[par_v];
      arr[par_v] = u;
    } else {
      arr[par_v] += arr[par_u];
      arr[par_u] = v;
    }
  }
};

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
    return i1>=size || i1>=size;
  }

  bool addEdge(int i1, int i2, int w) {
    if (checkUnfit(i1, i2)) return false;
    arr[i1][i2] = w;
    arr[i2][i1] = w;

    return true;
  }

public:
  // KRUSKAL:
  void Kruskal() {
    int edgeCNT = edgeCount();
    Edge **edges = new Edge*[edgeCNT];
    generateEdgeList(edges, edgeCNT);

    disJointSet s(size);

    int cost = 0;
    int edgeAdded = 0;

    cout << "\nKRUSKAL MST:" << endl;
    cout << "EDGE\tWEIGHT" << endl;
    
    for (int i = 0; i < edgeCNT && edgeAdded < size-1; i++) {
      int src = edges[i]->src;
      int dest = edges[i]->dest;

      if (!s.isConnected(src, dest)) {
        cost += edges[i]->weight;
        cout << src << " - " << dest << "\t" << edges[i]->weight << endl;
        s.weightedUnion(src, dest);
        ++edgeAdded;
      }
    }
    
    cout << "\nCOST: " << cost << endl;
    loop(i, edgeCNT) delete edges[i];
    delete[] edges;
  }
private:
  int edgeCount() {
    int cnt = 0;
    loop(i, size) loop(j, size) if (arr[i][j] != 0) cnt++;
    return cnt;
  }

  void generateEdgeList(Edge **edges, int cnt) {
    int idx = 0;
    loop(i, size) {
      loop(j, size) {
        if (arr[i][j] != 0) {
          edges[idx++] = new Edge(i, j, arr[i][j]);
        }
      }
    }

    sorter(edges, cnt);
  }

  void sorter(Edge **edges, int n) {
    loop(i, n) {
      Edge *cur = edges[i];
      int j = i-1;
      while (j >= 0 && edges[j]->weight > cur->weight) {
        edges[j+1] = edges[j];
        j--;
      }
      edges[++j] = cur;
    }
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

  g.Kruskal();

  return 0;
}
