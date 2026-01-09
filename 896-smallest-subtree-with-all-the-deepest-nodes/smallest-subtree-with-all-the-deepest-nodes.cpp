class Solution {
public:
    // returns {depth, subtree_root}
    pair<int, TreeNode*> dfs(TreeNode* root) {
        if (!root) return {0, nullptr};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        // If left subtree is deeper
        if (left.first > right.first) {
            return {left.first + 1, left.second};
        }
        // If right subtree is deeper
        else if (right.first > left.first) {
            return {right.first + 1, right.second};
        }
        // Same depth → current node is LCA of deepest nodes
        else {
            return {left.first + 1, root};
        }
    }

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs(root).second;
    }
};
