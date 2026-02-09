class Solution {
public:
    vector<int> vals;

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        vals.push_back(root->val);
        inorder(root->right);
    }

    TreeNode* build(int l, int r) {
        if (l > r) return nullptr;

        int mid = (l + r) / 2;
        TreeNode* node = new TreeNode(vals[mid]);
        node->left = build(l, mid - 1);
        node->right = build(mid + 1, r);
        return node;
    }

    TreeNode* balanceBST(TreeNode* root) {
        inorder(root);                  // Step 1: sorted values
        return build(0, vals.size() - 1); // Step 2: build balanced BST
    }
};
