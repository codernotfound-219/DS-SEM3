#include <iostream>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)

class Graph_ADJ_MATRIX {
private:
  int **adjMat;
  int size;

public:
  Graph_ADJ_MATRIX(int s) : size(s) {
    adjMat = new int *[size];
    loop(i, size) adjMat[i] = new int[size];
    loop(i, size) {
      loop(j, size) { adjMat[i][j] = 0; }
    }
  }

  bool checkUnfit(int i1, int i2) { return i1 >= size && i2 >= size; }

  bool checkUnfit(int i) { return i >= size; }

  bool addEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;
    adjMat[i1][i2] = 1;
    adjMat[i2][i1] = 1;

    return true;
  }

  bool removeEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;
    adjMat[i1][i2] = 0;
    adjMat[i2][i1] = 0;

    return true;
  }

  void printMatrix() {
    cout << "ADJACENCY MATRIX:\n" << endl;
    cout << "\t";
    loop(i, size) cout << i << " ";
    cout << endl;

    loop(i, size) {
      cout << i << "\t";
      loop(j, size) {
        if (adjMat[i][j] == 0)
          cout << "-" << " ";
        else
          cout << adjMat[i][j] << " ";
      }
      cout << endl;
    }

    cout << endl;
  }
};

class Graph_ADJ_LIST {
private:
  struct Node {
    int val;
    Node *next;
  };

  Node **adjList;
  int size;

public:
  Graph_ADJ_LIST(int s) : size(s) {
    adjList = new Node *[size];
    loop(i, size) adjList[i] = NULL;
  }

  bool checkUnfit(int i1, int i2) { return i1 >= size && i2 >= size; }

  bool checkUnfit(int i) { return i >= size; }

  bool addEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;

    Node *nn2 = new Node;
    Node *nn1 = new Node;
    if (nn1 == NULL || nn2 == NULL)
      return false;

    nn1->val = i2;
    nn1->next = adjList[i1];
    adjList[i1] = nn1;

    nn2->val = i1;
    nn2->next = adjList[i2];
    adjList[i2] = nn2;

    return true;
  }

  bool checkExistence(int i1, int i2) {
    Node *tmp = adjList[i1];
    while (tmp) {
      if (tmp->val == i2)
        return true;
      tmp = tmp->next;
    }
    return false;
  }

  bool removeEdge(int i1, int i2) {
    if (checkUnfit(i1, i2))
      return false;

    Node *tmp1 = adjList[i1];
    Node *tmp2 = adjList[i2];

    if (tmp1 == NULL || tmp2 == NULL)
      return false;
    if (!checkExistence(i1, i2) && !checkExistence(i2, i1))
      return false;

    if (tmp1->val == i2) {
      adjList[i1] = tmp1->next;
      delete tmp1;
    } else {
      while (tmp1->next->val != i2)
        tmp1 = tmp1->next;
      Node *del = tmp1->next;
      tmp1->next = del->next;
      delete del;
    }

    if (tmp2->val == i1) {
      adjList[i2] = tmp2->next;
      delete tmp2;
    } else {
      while (tmp2->next->val != i1)
        tmp2 = tmp2->next;
      Node *del = tmp2->next;
      tmp2->next = del->next;
      delete del;
    }

    return true;
  }

  void printList() {
    cout << "ADJACENCY LIST:\n" << endl;
    loop(i, size) {
      cout << i << " -> ";
      Node *tmp = adjList[i];
      while (tmp)
        cout << tmp->val << " ", tmp = tmp->next;

      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  Graph_ADJ_LIST gList(8);
  Graph_ADJ_MATRIX gMat(8);

  gList.addEdge(0, 1);
  gList.addEdge(0, 2);
  gList.addEdge(1, 3);
  gList.addEdge(1, 4);
  gList.addEdge(2, 5);
  gList.addEdge(2, 6);
  gList.addEdge(3, 7);
  gList.addEdge(4, 7);
  gList.addEdge(5, 7);
  gList.addEdge(6, 7);

  gMat.addEdge(0, 1);
  gMat.addEdge(0, 2);
  gMat.addEdge(1, 3);
  gMat.addEdge(1, 4);
  gMat.addEdge(2, 5);
  gMat.addEdge(2, 6);
  gMat.addEdge(3, 7);
  gMat.addEdge(4, 7);
  gMat.addEdge(5, 7);
  gMat.addEdge(6, 7);

  gList.printList();
  gMat.printMatrix();

  gList.removeEdge(6, 7);
  gMat.removeEdge(6, 7);

  cout << "REMOVED (6, 7)\n" << endl;
  gList.printList();
  gMat.printMatrix();

  return 0;
}
