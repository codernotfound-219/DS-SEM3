#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  int val;
  Node *left, *right;
  vector<Node *> children;

  Node(int val) {
    this->val = val;
    this->left = this->right = NULL;
  }
};

Node *convertor(Node *curNode) {
  if (!curNode)
    return NULL;

  if (curNode->children.size() == 0) { // NO CHILDREN
    return curNode;
  }

  if (curNode->children.size() == 1) {
    curNode->left =
        convertor(curNode->children[0]); // One child {make it left child}
  }

  curNode->left = convertor(curNode->children[0]);
  curNode->right = convertor(curNode->children[1]);

  // More than 2 siblings
  for (int i = 2; i < curNode->children.size(); i++) {
    Node *tmp = curNode->right;
    while (tmp->left != NULL) {
      tmp = tmp->left;
    }
    tmp->left = convertor(curNode->children[i]);
  }

  return curNode;
}

void printTree(Node *curNode, string prefix, bool isLeft) {
  if (!curNode)
    return;

  cout << prefix;
  cout << (isLeft ? "|———" : "L——— ");
  cout << curNode->val << endl;

  printTree(curNode->left, prefix + (isLeft ? "|   " : "    "), true);
  printTree(curNode->right, prefix + (isLeft ? "|   " : "    "), false);
}

int main() {
  Node *root = new Node(1);
  root->children.push_back(new Node(2));
  root->children.push_back(new Node(3));
  root->children.push_back(new Node(4));
  root->children.push_back(new Node(5));
  root->children[0]->children.push_back(new Node(6));
  root->children[0]->children.push_back(new Node(7));
  root->children[3]->children.push_back(new Node(8));
  root->children[3]->children.push_back(new Node(9));

  /* TREE:
               1
               |
     -----------------------
     |       |      |      |
     2       3      4      5
     |                     |
   -----                 ------
   |   |                 |    |
   6   7                 8    9

  */

  Node *binRoot = convertor(root);
  printTree(binRoot, "", false);
  return 0;
}
