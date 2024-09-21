#include <iostream>
using namespace std;
#define EMPTY INT_MIN
#define DELETED INT_MAX

class HashTable {
private:
  int *arr;
  int size;
  int count;

public:
  // CONSTRUCTOR
  HashTable(int keys) {
    size = keys;
    arr = new int[size];

    for (int i = 0; i < size; i++) {
      // SETTING ALL ELEMENTS OF ARRAY TO BE EMPTY
      arr[i] = EMPTY;
    }

    count = 0;
  }

  bool isEmpty() { return count == 0; }
  int countVal() { return count; }
  float loadFactor() { return (float)countVal() / size; }

  int hashFunc(int key) {
    return key % size; // A Standard Hash Function
  }

  bool insert(int key) {
    if (countVal() == size)
      return false; // Base case to handle overflow
    int hashVal = hashFunc(key);
    while (arr[hashVal] != EMPTY && arr[hashVal] != DELETED) {
      hashVal = ++hashVal % size;
    }
    arr[hashVal] = key;
    count++;
    return true;
  }

  bool search(int target) {
    int hashVal = hashFunc(target);
    int tmp = hashVal;
    while (arr[hashVal] != target) {
      if (arr[hashVal] == EMPTY)
        return false;
      hashVal = ++hashVal % size;

      // BASE CASE: trying to find an element not in the array
      // when the array is full (preventing infinite loop)
      if (tmp == hashVal)
        return false;
    }
    return true; // target is found
  }

  int deleteKey(int target) {
    // Assuming the element does exist
    int hashVal = hashFunc(target);
    while (arr[hashVal] != target) {
      hashVal = ++hashVal % size;
    }
    arr[hashVal] = DELETED;
    count--;
    return target;
  }

  void display() {
    for (int i = 0; i < size; i++) {
      if (arr[i] == EMPTY)
        cout << "\t" << i << "\t" << "---";
      else if (arr[i] == DELETED)
        cout << "\t" << i << "\t" << "$_DELETED_$";
      else
        cout << "\t" << i << "\t" << arr[i];
      cout << endl;
    }
  }
};

int main() {
  int option = 1, val, keys;
  cout << "ENTER TOTAL ELEMENTS: ";
  cin >> keys;
  HashTable hash(keys);

  while (option) {
    cout << "\nMENU:\n0. Exit\n1. Insert\n2. Search\n3. Delete\n4. Count\n5. "
            "LoadFactor\n6. Display"
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
        cout << "UNSUCCESSFUL: overflow" << endl;
      else
        cout << "Successful" << endl;
      break;
    case 2:
      cout << "Enter target: ";
      cin >> val;
      cout << (hash.search(val) ? "Exists" : "Does not exist") << endl;
      break;
    case 3:
      if (hash.isEmpty()) {
        cout << "UNSUCCESSFUL: underflow" << endl;
        break;
      }
      cout << "Enter val to delete: ";
      cin >> val;
      if (!hash.search(val)) {
        cout << "UNSUCCESSFUL: given value doesnt exists in the hashtable"
             << endl;
        break;
      }
      cout << "DELETED: " << hash.deleteKey(val) << endl;
      break;
    case 4:
      cout << "COUNT: " << hash.countVal() << endl;
      break;
    case 5:
      cout << "LOAD_FACTOR: " << hash.loadFactor() << endl;
      break;
    case 6:
      cout << "HASHTABLE:" << endl;
      hash.display();
      break;
    default:
      cout << "Invalid option" << endl;
      option = 1;
    }
  }
  return 0;
}
