#include <iostream>
#include <queue>
using namespace std;

#define loop(i, n) for(int i = 0; i < n; i++)

class Graph {
private:
  struct Node {
    int val;
    Node* next;
  };
  int size;
  Node **adjList;
public:
  Graph(int s) : size(s) {
    adjList = new Node*[size];
    loop(i, size) adjList[i] = NULL;
  }

public:
  // LINKED LIST FUNCT

public:
  // GRAPH PRIMARY FUNCTIONS
  bool unfitCheck(int i1, int i2) {
    return (i1 >= size && i2 >= size);
  }

  bool add_edge(int i1, int i2) {
    if (unfitCheck(i1, i2)) return false;
    Node* nn = new Node;
    nn->val = i2;
    nn->next = adjList[i1];
    adjList[i1] = nn;

    Node* nn_ = new Node;
    nn_->val = i1;
    nn_->next = adjList[i2];
    adjList[i2] = nn;

    return true;
  }


public:
  // GRAPH TRAVERSALS
  bool unfitCheck(int i) {
    return  i>=size;
  }

  void bfs(int start) {
    if (unfitCheck(start)) {
      cout << "INVALID VERTEX" << endl;
      return;
    }

    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      cout << vertex << " ";

      Node* tmp = adjList[vertex];
      while (tmp) {
        if (!visited[tmp->val]) {
          q.push(tmp->val);
          visited[tmp->val] = true;
        }

        tmp = tmp->next;
      }
    }
    cout << endl;
    delete[] visited;
  }

  void dfs(int start) {
    if (unfitCheck(start)) {
      cout << "INVALID INDEX" << endl;
      return;
    }

    bool *visited = new bool[size];
    loop(i, size) visited[i] = false;

    dfsUtil(visited, start);
    cout << endl;

    delete[] visited;
  }

private:
  void dfsUtil(bool visited[], int s) {
    visited[s] = true;
    cout << s << " ";

    Node* tmp = adjList[s];
    while (tmp) {
      if (!visited[tmp->val]) {
        dfsUtil(visited, tmp->val);
      }
      tmp = tmp->next;
    }
  }

public:
  // DISPLAY
  void printList() {
    loop(i, size) {
      cout << i << " -> ";
      Node* tmp = adjList[i];
      while (tmp) {
        cout << tmp->val <<  " ";
        tmp = tmp->next;
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  Graph g(8);

  g.add_edge(0, 2);  
  g.add_edge(0, 1);
  g.add_edge(1, 4);
  g.add_edge(1, 3); 
  g.add_edge(2, 6);
  g.add_edge(2, 5);
  g.add_edge(6, 7);
  g.add_edge(5, 7);
  g.add_edge(4, 7);
  g.add_edge(3, 7);
  
  cout << "BFS: ";
  g.bfs(0);
  cout << "DFS: ";
  g.dfs(0);
  cout << "\nADJACENCY LIST: " << endl;
  g.printList();

  return 0;
}
