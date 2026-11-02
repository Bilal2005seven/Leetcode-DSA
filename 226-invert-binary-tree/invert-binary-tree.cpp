#include <algorithm>

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // Base case: null node par kuch invert nahi karna
        if (root == nullptr) return nullptr;

        // Step 1: Subtrees ko recursively invert karo
        TreeNode* leftSubtree = invertTree(root->left);
        TreeNode* rightSubtree = invertTree(root->right);

        // Step 2: Swap the inverted subtrees
        root->left = rightSubtree;
        root->right = leftSubtree;

        return root;
    }
};