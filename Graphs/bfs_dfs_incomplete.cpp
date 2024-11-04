#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Graph {
private:
  vector<list<int> > adjList;
  vector<vector<int> > adjMatrix;
  vector<int> vertices;
  vector<pair<int, int> > edges;

public:
  Graph() {}

  void addVertex(int vertex) {
    if (find(vertices.begin(), vertices.end(), vertex) != vertices.end()) {
      cout << "Vertex " << vertex << " already exists." << endl;
      return;
    }

    vertices.push_back(vertex);
    adjList.push_back(list<int>());

    // Resize adjacency matrix
    for (size_t i = 0; i < adjMatrix.size(); ++i) {
      adjMatrix[i].push_back(0);
    }
    adjMatrix.push_back(vector<int>(vertices.size(), 0));
  }

  void addEdge(int from, int to) {
    vector<int>::iterator fromIt =
        find(vertices.begin(), vertices.end(), from);
    vector<int>::iterator toIt =
        find(vertices.begin(), vertices.end(), to);

    if (fromIt == vertices.end() || toIt == vertices.end()) {
      cout << "One or both vertices do not exist." << endl;
      return;
    }

    int fromIndex = distance(vertices.begin(), fromIt);
    int toIndex = distance(vertices.begin(), toIt);

    adjList[fromIndex].push_back(to);
    adjMatrix[fromIndex][toIndex] = 1;

    edges.push_back(make_pair(from, to));
  }

  void deleteVertex(int vertex) {
    vector<int>::iterator vIt =
        find(vertices.begin(), vertices.end(), vertex);
    if (vIt == vertices.end()) {
      cout << "Vertex " << vertex << " does not exist." << endl;
      return;
    }

    int index = distance(vertices.begin(), vIt);

    // Remove edges connected to this vertex
    vector<pair<int, int> >::iterator eIt = edges.begin();
    while (eIt != edges.end()) {
      if (eIt->first == vertex || eIt->second == vertex) {
        eIt = edges.erase(eIt);
      } else {
        ++eIt;
      }
    }

    // Remove vertex from vertices list
    vertices.erase(vIt);

    // Remove from adjacency list
    adjList.erase(adjList.begin() + index);
    for (size_t i = 0; i < adjList.size(); ++i) {
      adjList[i].remove(vertex);
    }

    // Remove from adjacency matrix
    adjMatrix.erase(adjMatrix.begin() + index);
    for (size_t i = 0; i < adjMatrix.size(); ++i) {
      adjMatrix[i].erase(adjMatrix[i].begin() + index);
    }
  }

  void deleteEdge(int from, int to) {
    vector<int>::iterator fromIt =
        find(vertices.begin(), vertices.end(), from);
    vector<int>::iterator toIt =
        find(vertices.begin(), vertices.end(), to);

    if (fromIt == vertices.end() || toIt == vertices.end()) {
      cout << "One or both vertices do not exist." << endl;
      return;
    }

    int fromIndex = distance(vertices.begin(), fromIt);
    int toIndex = distance(vertices.begin(), toIt);

    adjList[fromIndex].remove(to);
    adjMatrix[fromIndex][toIndex] = 0;

    vector<pair<int, int> >::iterator eIt =
        find(edges.begin(), edges.end(), make_pair(from, to));
    if (eIt != edges.end()) {
      edges.erase(eIt);
    }
  }

  void printAdjacencyMatrix() {
    cout << "Adjacency Matrix:" << endl;
    cout << "     ";
    for (size_t i = 0; i < vertices.size(); i++) {
      cout << setw(2) << vertices[i] << " ";
    }
    cout << endl;

    for (size_t i = 0; i < vertices.size(); i++) {
      cout << setw(2) << vertices[i] << " | ";
      for (size_t j = 0; j < vertices.size(); j++) {
        cout << setw(2);
        if (adjMatrix[i][j] == 0) {
          cout << "-" << " ";
        } else {
          cout << adjMatrix[i][j] << " ";
        }
      }
      cout << endl;
    }
  }

  void bfs(int start) {
    vector<int>::iterator startIt = find(vertices.begin(), vertices.end(), start);
    if (startIt == vertices.end()) {
      cout << "Start vertex " << start << " does not exist." << endl;
      return;
    }

    int startIndex = distance(vertices.begin(), startIt);
    vector<bool> visited(vertices.size(), false);
    queue<int> q;

    visited[startIndex] = true;
    q.push(startIndex);

    cout << "BFS traversal starting from vertex " << start << ": ";

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      cout << vertices[v] << " ";

      for (list<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); ++it) {
        int adjVertex = *it;
        int adjIndex = distance(vertices.begin(), find(vertices.begin(), vertices.end(), adjVertex));
        if (adjIndex >= 0 && adjIndex < (int)vertices.size() && !visited[adjIndex]) {
          visited[adjIndex] = true;
          q.push(adjIndex);
        }
      }
    }
    cout << endl;
  }

  void dfsUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << vertices[v] << " ";
    
    for (list<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); ++it) {
      int adjVertex = *it;
      int adjIndex = distance(vertices.begin(), find(vertices.begin(), vertices.end(), adjVertex));
      if (adjIndex >= 0 && adjIndex < (int)vertices.size() && !visited[adjIndex]) {
        dfsUtil(adjIndex, visited);
      }
    }
  }

  void dfs(int start) {
    vector<int>::iterator startIt = find(vertices.begin(), vertices.end(), start);
    if (startIt == vertices.end()) {
      cout << "Start vertex " << start << " does not exist." << endl;
      return;
    }

    int startIndex = distance(vertices.begin(), startIt);
    vector<bool> visited(vertices.size(), false);

    cout << "DFS traversal starting from vertex " << start << ": ";
    dfsUtil(startIndex, visited);
    cout << endl;
  }

  void printAdjacencyList() {
    cout << "Adjacency List:" << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
      cout << vertices[i] << " -> ";
      for (list<int>::const_iterator it = adjList[i].begin();
           it != adjList[i].end(); ++it) {
        cout << *it << " ";
      }
      cout << endl;
    }
  }

  void printVertices() {
    cout << "Vertices: ";
    for (vector<int>::const_iterator it = vertices.begin();
         it != vertices.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }

  void printEdges() {
    cout << "Edges: ";
    for (vector<pair<int, int> >::const_iterator it = edges.begin();
         it != edges.end(); ++it) {
      cout << "(" << it->first << "," << it->second << ") ";
    }
    cout << endl;
  }
};

int main() {
  Graph g;

  // Add vertices
  g.addVertex(1);
  g.addVertex(3);
  g.addVertex(5);
  g.addVertex(7);
  g.addVertex(9);

  // Add edges
  g.addEdge(1, 3);
  g.addEdge(3, 5);
  g.addEdge(5, 7);
  g.addEdge(7, 9);
  g.addEdge(9, 1);
  g.addEdge(1, 5);
  g.addEdge(3, 7);

  // Print initial graph
  cout << "Initial Graph:" << endl;
  g.printVertices();
  g.printEdges();
  g.printAdjacencyMatrix();
  cout << endl;
  g.printAdjacencyList();
  cout << endl;
   
  // Perform BFS and DFS
  g.bfs(1);
  g.dfs(1);
  
  g.bfs(5);
  g.dfs(5);

  return 0;
}
