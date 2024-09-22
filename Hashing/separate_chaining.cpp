#include <iostream>
using namespace std;

class HashTable {
private:
  struct Node {
    int val;
    Node *next;
  };

  Node **arr;
  int size, count;

public:
  HashTable(int keys) {
    size = keys;
    arr = new Node *[size];
    count = 0;

    for (int i = 0; i < size; i++) {
      arr[i] = NULL; // SETTING ALL ELEMENTS TO BE NULL
    }
  }

  bool isEmpty() { return count == 0; }

  int countVal() { return count; }

  float LoadFactor() { return (float)count / size; }

  int hashFunc(int key) { return key % size; }

  bool insert(int key) {
    int hashVal = hashFunc(key);
    Node *nn = new Node;
    if (nn == NULL)
      return false;
    if (arr[hashVal] == NULL)
      count++;
    nn->val = key;
    nn->next = arr[hashVal];
    arr[hashVal] = nn;
    return true;
  }

  bool search(int target) {
    int hashVal = hashFunc(target);
    Node *curHead = arr[hashVal];

    while (curHead != NULL) {
      if (curHead->val == target)
        return true;
      curHead = curHead->next;
    }

    return false;
  }

  int deleteKey(int target) {
    // ASSUMING TARGET EXISTS
    int hashVal = hashFunc(target);

    if (arr[hashVal]->val == target) {
      int rv = arr[hashVal]->val;
      Node *del = arr[hashVal];
      arr[hashVal] = arr[hashVal]->next;
      if (arr[hashVal] == NULL)
        count--;
      delete del;
      return rv;
    }

    Node *curHead = arr[hashVal];
    while (curHead->next->val != target) {
      curHead = curHead->next;
    }
    Node *del = curHead->next;
    int rv = del->val;
    curHead->next = del->next;
    delete del;
    return rv;
  }

  void display() {
    for (int i = 0; i < size; i++) {
      if (arr[i] == NULL) {
        cout << "\t" << i << "\t" << "---" << endl;
      } else {
        Node *tmp = arr[i];
        cout << "\t" << i << "\t";
        while (tmp != NULL) {
          cout << tmp->val << " -> ";
          tmp = tmp->next;
        }
        cout << "NULL" << endl;
      }
    }
  }

  ~HashTable() {
    cout << "DELETED HASHSET" << endl;
    delete[] arr;
  }
};

int main() {
  int option = 1, val;
  int size;
  cout << "ENTER SIZE: ";
  cin >> size;
  HashTable hash(size);

  while (option) {
    cout << "\nMENU:\n0. Exit\n1. Insert\n2. Search\n3. Delete\n4. count\n5. "
            "LoadFactor\n6. Print"
         << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "Exiting...";
      break;
    case 1:
      cout << "Enter val: ";
      cin >> val;
      if (!hash.insert(val))
        cout << "UNSUCCESSFUL" << endl;
      else
        cout << "SUCCESSFUL" << endl;
      break;
    case 2:
      cout << "Enter target: ";
      cin >> val;
      cout << (hash.search(val) ? "exists" : "doesnt exist") << endl;
      break;
    case 3:
      if (hash.isEmpty()) {
        cout << "UNSUCCESSFUL: underflow" << endl;
        break;
      }
      cout << "Enter target: ";
      cin >> val;
      if (!hash.search(val)) {
        cout << "UNSUCCESSFUL: value doesnt exist in hashmap" << endl;
        break;
      }
      cout << "DELETED: " << hash.deleteKey(val) << endl;
      break;
    case 4:
      cout << "COUNT: " << hash.countVal() << endl;
      break;
    case 5:
      cout << "LOADFACTOR: " << hash.LoadFactor() << endl;
      break;
    case 6:
      cout << "HASH:" << endl;
      hash.display();
      break;
    default:
      cout << "INVALID OPTION" << endl;
      option = 1;
    }
  }
  return 0;
}
