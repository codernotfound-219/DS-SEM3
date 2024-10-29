#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
private:
  vector<int> vertex;
  vector<vector<int>> adj_mat;
  vector<list<int>> adj_list;
  vector<pair<int, int>> edge;
  int index;

public:
  Graph(int n) {
    for (int i = 0; i < n; i++)
      vertex.push_back(0);
    for (int i = 0; i < n; i++) {
      vector<int> temp;
      for (int i = 0; i < n; i++)
        temp.push_back(0);
      adj_mat.push_back(temp);
    }
    for (int i = 0; i < n; i++) {
      list<int> temp;
      adj_list.push_back(temp);
    }
    for (int i = 0; i < n; i++) {
      pair<int, int> p(-1, -1);
      edge.push_back(p);
    }
    index = -1;
  }

  bool add_vertex(int v) {
    vertex[++index] = v;
    return true;
  }

private:
  bool add_edge(int v, int i1, int i2) {
    if (i1 >= 0 && i1 < vertex.size() && i2 >= 0 && i2 < vertex.size()) {
      edge[v].first = i1;
      edge[v].second = i2;
      return true;
    }
    return false;
  }

  bool update_matrix(int i1, int i2) {
    adj_mat[i1][i2] = 1;
    adj_mat[i2][i1] = 0;
    return true;
  }

  bool update_list(int i1, int i2) {
    adj_list[i1].push_back(i2);
    adj_list[i2].push_back(i1);
    return true;
  }

public:
  bool add_edge(int i1, int i2) {
    if (!add_edge(i1 - 1, i2 - 1))
      return false;
    if (!update_matrix(i1 - 1, i2 - 1))
      return false;
    if (!update_list(i1 - 1, i2 - 1))
      return false;
    return true;
  }

  void printList() {
    for (int i = 1; i <= adj_list.size(); i++) {
      cout << i << "\t -> ";
      list<int>::iterator it;

      for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
        cout << *it << " -> ";
      }

      cout << endl;
    }
  }

  void printMatrix() {
    cout << "\t";
    for (int i = 0; i < adj_mat.size(); i++)
      cout << i + 1 << " ";
    cout << endl;
    for (int i = 0; i < adj_mat.size(); i++) {
      cout << i + 1 << "\t";
      for (int j = 0; j < adj_mat[i].size(); j++) {
        cout << adj_mat[i][j] << ' ';
      }

      cout << endl;
    }
  }

  void printVertex() {
    for (int i = 0; i < vertex.size(); i++) {
      cout << vertex[i] << " ";
    }
    cout << endl;
  }

  void printEdge() {
    for (int i = 0; i < edge.size(); i++) {
      cout << "(" << edge[i].first << ", " << edge[i].second << ")" << endl;
    }
  }
};

int main() {
  Graph g(5);

  g.add_vertex(1);
  g.add_vertex(2);
  g.add_vertex(3);
  g.add_vertex(4);
  g.add_vertex(5);

  g.printVertex();

  g.add_edge(1, 2);
  g.add_edge(2, 5);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 5);

  g.printEdge();
  cout << "ADJACENCY MATRIX: " << endl;
  g.printMatrix();
  cout << "\nADJACENCY LIST:" << endl;
  g.printList();
}
