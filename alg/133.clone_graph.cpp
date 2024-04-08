#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
    unordered_set<pair<int, int>> vis;
public:

    Node* cloneGraph(Node* node) {
        if (!node || !node->val) return nullptr;
        Node* new_node = new Node(node->val);
        for (auto n : node->neighbors) {
            if (vis.find({node->val, n->val}) != vis.end()) continue;
            vis.insert({node->val, n->val});
            new_node->neighbors.push_back(cloneGraph(n));
        }
        return new_node;
    }
};

int main() {

}
