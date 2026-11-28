/*
// Definition for a Node.
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
*/

class Solution {
public:
    // Original Node* -> Cloned Node* map karne ke liye
    unordered_map<Node*, Node*> mp;

    Node* cloneGraph(Node* node) {
        // Edge case: Agar graph khali (null) hai
        if (node == nullptr) {
            return nullptr;
        }

        // Agar is node ka clone pehle hi ban chuka hai, toh wahi return kar do
        if (mp.find(node) != mp.end()) {
            return mp[node];
        }

        // 1. Naya clone node banao aur turant map mein store karo (cycle se bachne ke liye)
        Node* clone = new Node(node->val);
        mp[node] = clone;

        // 2. Original node ke har neighbor ko clone karke naye node ke neighbors mein daalo
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }

        return clone;
    }
};