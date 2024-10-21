#include <iostream>
using namespace std;

int depth(int count) {
  if (count <= 0)
    return -1;
  int ans = -1;

  while (count) {
    ans++;
    count >>= 1;
  }

  return ans + 1;
}

class PriorityQueue {
private:
  int *arr;
  int count;
  int size;

public:
  PriorityQueue() {
    size = 10;
    count = 0;
    arr = new int[size];
  }

  void maxHeapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < count && arr[left] > arr[largest])
      largest = left;
    if (right < count && arr[right] > arr[largest])
      largest = right;

    if (largest != i) {
      swap(arr[largest], arr[i]);
      maxHeapify(largest);
    }
  }

  void insert(int v) {
    if (count == size) {
      size *= 2;
      int *tmp = new int[size];
      for (int i = 0; i < count; i++)
        tmp[i] = arr[i];
      delete[] arr;
      arr = tmp;
    }

    arr[count++] = v;
    int i = count - 1;

    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
      swap(arr[i], arr[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  int peek() {
    if (count <= 0) {
      return INT_MIN;
    }
    return arr[0];
  }

  int extract() {
    if (count <= 0)
      return INT_MIN;
    if (count == 1) {
      return arr[--count];
    }

    int rv = peek();
    swap(arr[0], arr[count - 1]);
    count--;
    maxHeapify(0);

    return rv;
  }

  void print() {
    for (int i = 0; i < count; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }

  void printTree() {
    int dep = depth(count);
    int index = 0, num = 1;
    bool brake = false;

    for (int i = 1; i <= dep; i++) {
      for (int j = 1; j <= num; j++) {
        cout << arr[index] << " ";
        index++;
        if (index >= count) {
          brake = true;
          break;
        }
      }

      cout << endl;
      num *= 2;
      if (brake)
        break;
    }
  }
};

int main() {
  int option = 1, val;
  PriorityQueue pq;
  cout << "\nNOTE: extract returns the maximum in O(1) time." << endl;

  while (option) {
    cout << "\nMENU:\n0. Exit  \t1. Insert\n2. Extract\t3. Peek\n4. Print\t5. "
            "PrintTree"
         << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXITING" << endl;
      break;
    case 1:
      cout << "ENTER VAL: ";
      cin >> val;
      pq.insert(val);
      break;
    case 2:
      cout << "EXTRACTED: " << pq.extract() << endl;
      break;
    case 3:
      cout << "PEEK: " << pq.peek() << endl;
      break;
    case 4:
      cout << "QUEUE: " << endl;
      pq.print();
      break;
    case 5:
      cout << "TREE STRUCTURE: " << endl;
      pq.printTree();
      break;
    default:
      cout << "INVALID CHOICE" << endl;
      option = 1;
    }
  }
  return 0;
}
