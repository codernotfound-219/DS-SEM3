#include <iostream>
using namespace std;

class AVL {
private:
  // ADT
  struct Node {
    int val, height;
    Node *left, *right;
  };

  Node *root;

private:
  // MISC
  int height(Node *curNode) {
    if (curNode == NULL)
      return 0;
    return curNode->height;
  }

  Node *minNode(Node *curNode) {
    if (curNode == NULL || curNode->left == NULL)
      return curNode;
    return minNode(curNode->left);
  }

  Node *maxNode(Node *curNode) {
    if (curNode == NULL || curNode->right == NULL)
      return curNode;
    return maxNode(curNode->right);
  }

  int getBalance(Node *curNode) {
    if (!curNode)
      return 0;
    return height(curNode->left) - height(curNode->right);
  }

  void updateHeight(Node *curNode) {
    curNode->height = 1 + max(height(curNode->left), height(curNode->right));
  }

private:
  // Rotations
  Node *leftRotate(Node *y) {
    Node *x = y->right;
    Node *T2 = x->left;

    x->left = y;
    y->right = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  Node *rightRotate(Node *x) {
    Node *y = x->left;
    Node *T2 = y->right;

    y->right = x;
    x->left = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

private:
  // FUNC
  Node *search(Node *curNode, int sv) {
    if (curNode == NULL || curNode->val == sv)
      return curNode;

    if (curNode->val < sv) {
      return search(curNode->right, sv);
    }
    return search(curNode->left, sv);
  }

  Node *insert(Node *curNode, int v) {
    if (curNode == NULL) {
      Node *nn = new Node;
      nn->val = v;
      nn->height = 1;
      nn->left = nn->right = NULL;
      return nn;
    }

    if (curNode->val < v) {
      curNode->right = insert(curNode->right, v);
    } else if (curNode->val > v) {
      curNode->left = insert(curNode->left, v);
    } else {
      return curNode;
    }

    updateHeight(curNode);
    int balance = getBalance(curNode);

    // left-left
    if (balance > 1 && v < curNode->left->val) {
      return rightRotate(curNode);
    }

    // left-right
    if (balance > 1 && v > curNode->left->val) {
      curNode->left = leftRotate(curNode->left);
      return rightRotate(curNode);
    }

    // right-right
    if (balance < -1 && v > curNode->right->val) {
      return leftRotate(curNode);
    }

    // right-left
    if (balance < -1 && v < curNode->right->val) {
      curNode->right = rightRotate(curNode->right);
      return leftRotate(curNode);
    }

    return curNode;
  }

  Node *deleteNode(Node *curNode, int v) {
    if (curNode == NULL)
      return NULL;

    if (curNode->val < v) {
      curNode->right = deleteNode(curNode->right, v);
    } else if (curNode->val > v) {
      curNode->left = deleteNode(curNode->left, v);
    } else {
      if (!curNode->left && !curNode->right) {
        delete curNode;
        curNode = NULL;
      } else if (!curNode->right) {
        Node *tmp = curNode->left;
        delete curNode;
        curNode = tmp;
      } else if (!curNode->left) {
        Node *tmp = curNode->right;
        delete curNode;
        curNode = tmp;
      } else {
        int succVal = minNode(curNode->right)->val;
        curNode->val = succVal;
        curNode->right = deleteNode(curNode->right, succVal);
      }
    }

    if (curNode == NULL)
      return curNode;

    updateHeight(curNode);
    int balance = getBalance(curNode);

    // left-left
    if (balance > 1 && getBalance(curNode->left) >= 0) {
      return rightRotate(curNode);
    }

    // left-right
    if (balance > 1 && getBalance(curNode->left) < 0) {
      curNode->left = leftRotate(curNode);
      return rightRotate(curNode);
    }

    // right-right
    if (balance < -1 && getBalance(curNode->right) <= 0) {
      return leftRotate(curNode);
    }

    // right-left
    if (balance < -1 && getBalance(curNode->right) > 0) {
      curNode->right = rightRotate(curNode->right);
      return leftRotate(curNode);
    }

    return curNode;
  }

private:
  // DISPLAY
  void display(Node *curNode, int spaces) {
    if (curNode == NULL)
      return;

    spaces += 4;

    display(curNode->right, spaces);
    cout << endl;
    for (int i = 4; i < spaces; i++)
      cout << " ";
    cout << curNode->val << endl;

    display(curNode->left, spaces);
  }

private:
  Node *predecessorNode(int v) {
    Node *cur = search(root, v);
    if (!cur) {
      return NULL;
    }

    if (cur->left) {
      return maxNode(cur->left);
    }

    Node *pred = NULL;
    Node *ancestor = root;

    while (ancestor != cur) {
      if (ancestor->val < cur->val) {
        pred = ancestor;
        ancestor = ancestor->right;
      } else {
        ancestor = ancestor->left;
      }
    }

    return pred;
  }

  Node *successorNode(int v) {
    Node *cur = search(root, v);
    if (!cur) {
      return NULL;
    }

    if (cur->right) {
      return minNode(cur->right);
    }

    Node *succ = NULL;
    Node *ancestor = root;

    while (ancestor != cur) {
      if (ancestor->val < cur->val) {
        ancestor = ancestor->right;
      } else {
        succ = ancestor;
        ancestor = ancestor->left;
      }
    }

    return succ;
  }

private:
  // TRAVERSAL
  void inOrder(Node *curNode) {
    if (!curNode)
      return;
    inOrder(curNode->left);
    cout << curNode->val << " ";
    inOrder(curNode->right);
  }

  void postOrder(Node *curNode) {
    if (!curNode)
      return;
    postOrder(curNode->left);
    postOrder(curNode->right);
    cout << curNode->val << " ";
  }

  void preOrder(Node *curNode) {
    if (!curNode)
      return;
    cout << curNode->val << " ";
    preOrder(curNode->left);
    preOrder(curNode->right);
  }

public:
  AVL() { root = NULL; }

  bool search(int v) {
    Node *serNode = search(root, v);
    if (serNode == NULL)
      return false;
    return serNode->val == v ? true : false;
  }

  bool insert(int v) {
    root = insert(root, v);
    return search(v);
  }

  bool deleteNode(int v) {
    root = deleteNode(root, v);
    return !search(v);
  }

  void display() { display(root, 0); }

  int predecessor(int v) {
    Node *pred = predecessorNode(v);
    return pred ? pred->val : INT_MAX;
  }

  int successor(int v) {
    Node *succ = successorNode(v);
    return succ ? succ->val : INT_MIN;
  }

  void inOrder() { return inOrder(root); }
  void postOrder() { return postOrder(root); }
  void preOrder() { return preOrder(root); }
};

int main() {
  int option = 1, val;
  AVL tree;

  while (option) {
    cout << "\nMENU:\n0. Exit  \t1. Insert\n2. Delete\t3. Search\n4. "
            "Predecessor\t5. Successor\n6. Inorder\t7. PostOrder\n8. "
            "PreOrder\t9. Display"
         << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXITING..." << endl;
      break;
    case 1:
      cout << "ENTER VAL: ";
      cin >> val;
      cout << (tree.insert(val) ? "SUCCESS" : "UNSUCCESSFUL") << endl;
      break;
    case 2:
      cout << "ENTER VAL: ";
      cin >> val;
      cout << (tree.deleteNode(val) ? "SUCCESS" : "UNSUCCESSFUL") << endl;
      break;
    case 3:
      cout << "ENTER VAL: ";
      cin >> val;
      cout << (tree.search(val) ? "EXISTS" : "DOES NOT EXIST") << endl;
      break;
    case 4:
      cout << "ENTER VAL: ";
      cin >> val;
      if (!tree.search(val)) {
        cout << "VAL DOES NOT EXIST" << endl;
        break;
      }
      cout << "PREDECESSOR: " << tree.predecessor(val) << endl;
      break;
    case 5:
      cout << "ENTER VAL: ";
      cin >> val;
      if (!tree.search(val)) {
        cout << "VAL DOES NOT EXIST" << endl;
        break;
      }
      cout << "SUCESSFUL: " << tree.successor(val) << endl;
      break;
    case 6:
      cout << "INORDER TRAVERSAL:" << endl;
      tree.inOrder();
      cout << endl;
      break;
    case 7:
      cout << "POSTORDER TRAVERSAL:" << endl;
      tree.postOrder();
      cout << endl;
      break;
    case 8:
      cout << "PREORDER TRAVERSAL:" << endl;
      tree.preOrder();
      cout << endl;
      break;
    case 9:
      cout << "TREE:" << endl;
      tree.display();
      break;
    default:
      cout << "INVALID OPTION" << endl;
      option = 1;
    }
  }
  return 0;
}
