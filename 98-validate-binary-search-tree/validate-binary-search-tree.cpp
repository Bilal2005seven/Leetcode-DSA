#include <climits>

using namespace std;

class Solution {
private:
    bool validate(TreeNode* root, long long minBound, long long maxBound) {
        if (root == nullptr) return true;

        // Current node bound ke bahar hai
        if (root->val <= minBound || root->val >= maxBound) {
            return false;
        }

        // Left child must be in (minBound, root->val)
        // Right child must be in (root->val, maxBound)
        return validate(root->left, minBound, root->val) &&
               validate(root->right, root->val, maxBound);
    }

public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
};
