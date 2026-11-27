/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        // 1. Bilkul left edge ki height nikalo
        int lh = getLeftHeight(root);
        // 2. Bilkul right edge ki height nikalo
        int rh = getRightHeight(root);

        // 3. Agar dono heights barabar hain, toh yeh Perfect Binary Tree hai
        // (1 << lh) ka matlab 2^lh hota hai (bitwise left shift)
        if (lh == rh) {
            return (1 << lh) - 1;
        }

        // 4. Agar barabar nahi hain, toh left aur right subtrees ke liye recursively call karo
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

private:
    int getLeftHeight(TreeNode* node) {
        int height = 0;
        while (node != nullptr) {
            height++;
            node = node->left;
        }
        return height;
    }

    int getRightHeight(TreeNode* node) {
        int height = 0;
        while (node != nullptr) {
            height++;
            node = node->right;
        }
        return height;
    }
};