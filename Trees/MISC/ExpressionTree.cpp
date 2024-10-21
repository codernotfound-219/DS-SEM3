#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
  char data;
  Node *left, *right;
};

class NodeStack {
private:
  stack<Node *> s;

public:
  void push(Node *v) { s.push(v); }

  Node *pop() {
    Node *tmp = s.top();
    s.pop();
    return tmp;
  }
};

bool isOperator(char c) {
  if (c == '/' || c == '*' || c == '%' || c == '^' || c == '+' || c == '-')
    return true;
  return false;
}

Node *expTree(string postfix) {
  NodeStack st;
  Node *op, *opnd1, *opnd2, *opnd;

  for (int i = 0; i < postfix.size(); i++) {
    char c = postfix[i];

    if (!isOperator(c)) {
      opnd = new Node;
      opnd->data = c;
      opnd->left = opnd->right = NULL;
      st.push(opnd);
    } else {
      opnd1 = st.pop();
      opnd2 = st.pop();

      op = new Node;
      op->data = c;
      op->left = opnd2;
      op->right = opnd1;

      st.push(op);
    }
  }

  return st.pop();
}

void printTree(Node *curNode, int spaces) {
  if (!curNode)
    return;
  spaces += 4;

  printTree(curNode->right, spaces);
  cout << endl;

  for (int i = 4; i < spaces; i++)
    cout << " ";
  cout << curNode->data << endl;

  printTree(curNode->left, spaces);
}

int main() {
  string input;
  int option = 1;

  cout << "\nNOTE: the tree is printed horizontal." << endl;

  while (option) {
    cout << "\n0. Exit  \t1. GenerateTree" << endl;
    cin >> option;

    if (option == 0) {
      cout << "EXITING...";
      break;
    }

    if (option != 1) {
      cout << "INV CHOICE " << endl;
      continue;
    }

    cout << "Enter string (no_spaces, single_chars only): ";
    cin >> input;

    cout << "\nTREE:" << endl;
    printTree(expTree(input), 0);
    cout << endl;
  }

  return 0;
}
