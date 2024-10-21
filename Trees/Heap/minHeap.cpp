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

class minHeap {
private:
  int *arr;
  int count;
  int size;

public:
  minHeap(int s) {
    count = 0;
    size = s;
    arr = new int[size];
  }

  void heapify(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < count && arr[left] < arr[smallest])
      smallest = left;
    if (right < count && arr[right] < arr[smallest])
      smallest = right;

    if (smallest != i) {
      swap(arr[i], arr[smallest]);
      heapify(smallest);
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

    while (i != 0 && arr[(i - 1) / 2] > arr[i]) {
      swap(arr[i], arr[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  int peek() {
    if (count <= 0)
      return INT_MIN;
    return arr[0];
  }

  int extract() {
    if (count <= 0)
      return INT_MIN;
    if (count == 1) {
      return arr[--count];
    }

    int rv = peek();
    swap(arr[0], arr[count - 1]); // swap root and last node
    count--;
    heapify(0);

    return rv;
  }

  void print() {
    for (int i = 0; i < count; i++)
      cout << arr[i] << " ";
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
  minHeap heap(10);

  while (option) {
    cout << "\nMENU:\n0. Exit  \t1. Insert\n2. Extract\t3. Peek  \n4. "
            "Print\t5. PrintTree"
         << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXITING..." << endl;
      break;
    case 1:
      cout << "ENTER VAL: ";
      cin >> val;
      heap.insert(val);
      break;
    case 2:
      cout << "EXTRACTED: " << heap.extract() << endl;
      break;
    case 3:
      cout << "PEEK: " << heap.peek() << endl;
      break;
    case 4:
      cout << "Array:" << endl;
      heap.print();
      break;
    case 5:
      cout << "Tree:" << endl;
      heap.printTree();
      break;
    default:
      cout << "Invalid choice" << endl;
      option = 1;
    }
  }
}
