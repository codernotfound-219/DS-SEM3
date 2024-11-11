#include <iostream>
#include <string>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)

class Trie {
private:
  Trie *arr[26];
  bool endOfWord;

public:
  Trie() {
    loop(i, 26) arr[i] = NULL;
    endOfWord = false;
  }

  void insert(string word) {
    Trie *tmp = this;
    loop(i, word.length()) {
      int idx = word[i] - 'a';

      if (tmp->arr[idx] == NULL) {
        tmp->arr[idx] = new Trie;
      }
      tmp = tmp->arr[idx];
    }
    tmp->endOfWord = true;
  }

  bool search(string word) {
    Trie *tmp = this;
    loop(i, word.length()) {
      int idx = word[i] - 'a';
      if (tmp->arr[idx] == NULL)
        return false;
      tmp = tmp->arr[idx];
    }
    return tmp->endOfWord;
  }
};

int main() {
  Trie trie;
  trie.insert("wholetthedogsout");
  cout << "SEARCH wholetthedogsout: " << trie.search("wholetthedogsout")
       << endl;
  cout << "SEARCH cat: " << trie.search("cat") << endl;
  trie.insert("cat");
  cout << "SEARCH cat (inserted): " << trie.search("cat") << endl;
  return 0;
}
