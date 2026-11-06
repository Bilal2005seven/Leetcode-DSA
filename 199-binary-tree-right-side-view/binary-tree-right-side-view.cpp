#include <vector>

using namespace std;

class Solution {
private:
    void dfs(TreeNode* root, int level, vector<int>& result) {
        if (root == nullptr) return;

        // Agar hum is level par pehli baar aaye hain
        if (level == result.size()) {
            result.push_back(root->val);
        }

        // Pehle RIGHT explore karo, phir LEFT
        dfs(root->right, level + 1, result);
        dfs(root->left, level + 1, result);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }
};
