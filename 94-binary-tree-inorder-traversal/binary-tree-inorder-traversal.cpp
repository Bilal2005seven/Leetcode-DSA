#include <vector>

using namespace std;

class Solution {
private:
    void inorder(TreeNode* root, vector<int>& ans) {
        if (root == nullptr) return;

        inorder(root->left, ans);   // 1. Traverse Left
        ans.push_back(root->val);   // 2. Visit Node
        inorder(root->right, ans);  // 3. Traverse Right
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inorder(root, ans);
        return ans;
    }
};