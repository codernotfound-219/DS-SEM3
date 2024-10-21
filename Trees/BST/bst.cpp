#include <iostream>
using namespace std;

class BST {
private:
  struct Node {
    int val;
    Node* left;
    Node* right;
  };

  Node *root;

private:
  int minValue(Node* curNode) {
    if (curNode->left == NULL) return curNode->val;
    return minValue(curNode->left);
  }
private:
  Node* search(Node* curNode, int sv) {
    if (!curNode || curNode->val == sv) return curNode;

    if (curNode->val > sv) 
      return search(curNode->left, sv);
    else
      return search(curNode->right, sv);
  }

  Node* insert(Node* curNode, int v) {
    if (curNode == NULL) {
      Node* nn = new Node;
      nn->val = v;
      nn->left = nn->right = NULL;
      return nn;
    }

    if (curNode->val > v) {
      curNode->left = insert(curNode->left, v);
    } 

    if (curNode->val < v) {
      curNode->right = insert(curNode->right, v);
    }

    return curNode;
  }

  Node* deleteNode(Node* curNode, int v) {
    if (curNode == NULL) return curNode;

    if (curNode->val < v) {
      curNode->right = deleteNode(curNode->right, v);
    } else if (curNode->val > v) {
      curNode->left = deleteNode(curNode->left, v);
    } else {
      if (curNode->right == NULL && curNode->left == NULL) {
        delete curNode;
        return NULL;
      }

      if (curNode->right == NULL) {
        Node* tmp = curNode->left;
        delete curNode;
        return tmp;
      }

      if (curNode->left == NULL) {
        Node* tmp = curNode->right;
        delete curNode;
        return tmp;
      }

      int succVal = minValue(curNode->right);
      curNode->val = succVal;
      curNode->right = deleteNode(curNode->right, succVal);
    }

    return curNode;
  }

private:
  void display(Node* curNode, int spaces) {
    if (curNode == NULL) return;
    spaces += 4;

    display(curNode->right, spaces);
    cout << endl;
    for (int i = 4; i < spaces; i++) {
      cout << " ";
    }
    cout << curNode->val << endl;

    display(curNode->left, spaces);
  }
public:
  BST() {
    root = NULL;
  }

  bool insert(int v) {
    root = insert(root, v);
    return search(v);
  }

  bool deleteNode(int v) {
    root = deleteNode(root, v);
    return !search(v);
  }

  bool search(int sv) {
    Node* serNode = search(root, sv);
    if (serNode == NULL) return false;
    if (serNode->val == sv) return true;
    return false;
  }

  void display() {
    return display(root, 0);
  }
};

int main() {
  int option = 1, val;
  BST bst;

  while (option) {
    cout << "0. Exit\t1. Insert\n2. Delete\t3. Search\n4. Display" << endl;
    cin >> option;

    switch(option) {
      case 0:
        cout << "EXITING" << endl;
        break;
      case 1:
        cout << "ENTER VAL: "; cin>> val;
        cout << (bst.insert(val) ? "SUCCESS" : "UNSUCCESSFUL") << endl;
        break;
      case 2:
        cout << "ENTER VAL: "; cin >> val;
        cout << (bst.deleteNode(val) ? "SUCCESS" : "UNSUCCESSFUL") << endl;
        break;
      case 3:
        cout << "ENTER VAL: "; cin >> val;
        cout << (bst.search(val) ? "EXISTS" : "DOES NOT EXIST") << endl;
        break;
      case 4:
        cout << "TREE:" << endl; 
        bst.display();
        break;
      default:
        cout << "INV" << endl;
        option=1;
    }
  }

  return 0;
}
