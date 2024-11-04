#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>

using namespace std;

class Graph {
public:
    // Constructor
    Graph() : vertexCount(0) {
        for (int i = 0; i < MAX_VERTICES; ++i) {
            vertexIndex[i] = -1;
            vector<int> row(MAX_VERTICES, 0);
            adjMatrix.push_back(row);
            adjList.push_back(list<int>());
        }
    }

    // Add a vertex
    void addVertex(int vertex) {
        if (vertexCount < MAX_VERTICES && vertexIndex[vertex] == -1) {
            vertexIndex[vertex] = vertexCount;
            vertices.push_back(vertex);
            vertexCount++;
        }
    }

    // Add an edge
    void addEdge(int vertex1, int vertex2) {
        addVertex(vertex1);
        addVertex(vertex2);

        int index1 = vertexIndex[vertex1];
        int index2 = vertexIndex[vertex2];

        // Update adjacency matrix
        adjMatrix[index1][index2] = 1;
        adjMatrix[index2][index1] = 1; // For undirected graph

        // Update adjacency list
        adjList[index1].push_back(vertex2);
        adjList[index2].push_back(vertex1);

        // Store the edge
        edges.push_back(make_pair(vertex1, vertex2));
    }

    // BFS traversal
    void bfs(int start) {
        vector<bool> visited(MAX_VERTICES, false);
        queue<int> queue;

        visited[vertexIndex[start]] = true;
        queue.push(start);

        cout << "BFS Traversal: ";

        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            cout << vertex << " ";

            for (list<int>::iterator it = adjList[vertexIndex[vertex]].begin(); it != adjList[vertexIndex[vertex]].end(); ++it) {
                if (!visited[vertexIndex[*it]]) {
                    visited[vertexIndex[*it]] = true;
                    queue.push(*it);
                }
            }
        }
        cout << endl;
    }

    // DFS traversal
    void dfs(int start) {
        vector<bool> visited(MAX_VERTICES, false);
        cout << "DFS Traversal: ";
        dfsUtil(start, visited);
        cout << endl;
    }

private:
    static const int MAX_VERTICES = 100; // Maximum number of vertices
    vector<int> vertices; // Vector of vertices
    vector<vector<int> > adjMatrix; // Adjacency matrix
    vector<list<int> > adjList; // Adjacency list
    vector<pair<int, int> > edges; // Vector of edges
    int vertexIndex[MAX_VERTICES]; // Index map for vertices
    int vertexCount; // Count of vertices

    // Utility function for DFS
    void dfsUtil(int vertex, vector<bool>& visited) {
        visited[vertexIndex[vertex]] = true;
        cout << vertex << " ";

        for (list<int>::iterator it = adjList[vertexIndex[vertex]].begin(); it != adjList[vertexIndex[vertex]].end(); ++it) {
            if (!visited[vertexIndex[*it]]) {
                dfsUtil(*it, visited);
            }
        }
    }
};

int main() {
    Graph g;

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    g.bfs(1); // Start BFS from vertex 1
    g.dfs(1); // Start DFS from vertex 1

    return 0;
}
