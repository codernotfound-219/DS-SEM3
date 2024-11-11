#include <iostream>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)

struct Node {
  float val;
  Node *next;
  Node(float val) : val(val), next(NULL) {};
};

void insertionSort(Node *&head) {
  if (!head || !head->next)
    return;

  Node *sorted = NULL;
  Node *current = head;

  while (current != NULL) {
    Node *next = current->next;

    if (sorted == NULL || sorted->val >= current->val) {
      current->next = sorted;
      sorted = current;
    } else {
      Node *search = sorted;
      while (search->next != NULL && search->next->val < current->val) {
        search = search->next;
      }
      current->next = search->next;
      search->next = current;
    }

    current = next;
  }

  head = sorted;
}

void bucketSort(float arr[], int size) {
  Node **buckets = new Node *[size];

  // Initialize buckets to NULL
  for (int i = 0; i < size; i++) {
    buckets[i] = NULL;
  }

  // Place elements into buckets
  for (int i = 0; i < size; i++) {
    int idx = size * arr[i];
    Node *newNode = new Node(arr[i]);
    newNode->next = buckets[idx];
    buckets[idx] = newNode;
  }

  // Apply insertion sort to each bucket
  for (int i = 0; i < size; i++) {
    insertionSort(buckets[i]);
  }

  // Concatenate all buckets back into arr
  int idx = 0;
  for (int i = 0; i < size; i++) {
    Node *current = buckets[i];
    while (current) {
      arr[idx++] = current->val;
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }

  delete[] buckets;
}

int main() {
  float arr[] = {0.234, 0.182, 0.43,  0.244, 0.231,
                 0.562, 0.001, 0.656, 0.834, 0.2351};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "INPUT ARRAY:\t";
  loop(i, size) cout << arr[i] << " ";
  cout << endl;

  bucketSort(arr, size);

  cout << "SORTED ARRAY:\t";
  loop(i, size) cout << arr[i] << " ";
  cout << endl;

  return 0;
}
