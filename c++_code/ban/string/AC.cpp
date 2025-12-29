#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class TrieNode {
public:
  unordered_map<char, TrieNode *> children;
  TrieNode *fail;
  int endCount;
  int inDegree;
  int id;
  string word; // 存储完整的模式串

  TrieNode(int id) : fail(nullptr), endCount(0), inDegree(0), id(id) {}
};

class AC_Automaton {
private:
  TrieNode *root;
  vector<TrieNode *> nodes;
  int nodeCount;
  vector<TrieNode *> patternNodes; // 存储每个模式串的结束节点

public:
  AC_Automaton() {
    nodeCount = 0;
    root = new TrieNode(nodeCount++);
    nodes.push_back(root);
  }

  ~AC_Automaton() {
    for (auto node : nodes) {
      delete node;
    }
  }

  void insert(const string &word) {
    TrieNode *current = root;
    for (char c : word) {
      if (current->children.find(c) == current->children.end()) {
        TrieNode *newNode = new TrieNode(nodeCount++);
        current->children[c] = newNode;
        nodes.push_back(newNode);
      }
      current = current->children[c];
    }
    current->endCount++;
    current->word = word;            // 存储完整的模式串
    patternNodes.push_back(current); // 记录模式串结束节点
  }

  void buildFailPointers() {
    queue<TrieNode *> q;

    for (auto &child : root->children) {
      child.second->fail = root;
      root->inDegree++;
      q.push(child.second);
    }

    while (!q.empty()) {
      TrieNode *current = q.front();
      q.pop();

      for (auto &child : current->children) {
        char c = child.first;
        TrieNode *node = child.second;

        TrieNode *failNode = current->fail;
        while (failNode &&
               failNode->children.find(c) == failNode->children.end()) {
          failNode = failNode->fail;
        }

        if (failNode &&
            failNode->children.find(c) != failNode->children.end()) {
          node->fail = failNode->children[c];
        } else {
          node->fail = root;
        }

        node->fail->inDegree++;
        q.push(node);
      }
    }
  }

  void query(const string &text) {
    // 重置计数
    for (auto node : nodes) {
      node->endCount = 0;
    }

    TrieNode *current = root;
    for (char c : text) {
      while (current != root &&
             current->children.find(c) == current->children.end()) {
        current = current->fail;
      }

      if (current->children.find(c) != current->children.end()) {
        current = current->children[c];
      } else {
        current = root;
      }

      current->endCount++;
    }

    // 拓扑排序优化
    queue<TrieNode *> topoQueue;
    for (auto node : nodes) {
      if (node->inDegree == 0) {
        topoQueue.push(node);
      }
    }

    while (!topoQueue.empty()) {
      TrieNode *node = topoQueue.front();
      topoQueue.pop();

      if (node->fail) {
        node->fail->endCount += node->endCount;
        if (--node->fail->inDegree == 0) {
          topoQueue.push(node->fail);
        }
      }
    }
  }

  // 获取所有模式串的计数（按插入顺序）
  vector<int> getPatternCounts() {
    vector<int> counts;
    for (auto node : patternNodes) {
      counts.push_back(node->endCount);
    }
    return counts;
  }
};

int main() {
  int n;
  cin >> n;

  vector<string> patterns;
  for (int i = 0; i < n; i++) {
    string pattern;
    cin >> pattern;
    patterns.push_back(pattern);
  }

  string text;
  cin >> text;

  AC_Automaton ac;
  for (const string &pattern : patterns) {
    ac.insert(pattern);
  }

  ac.buildFailPointers();
  ac.query(text);

  vector<int> results = ac.getPatternCounts();
  for (int count : results) {
    cout << count << endl;
  }

  return 0;
}