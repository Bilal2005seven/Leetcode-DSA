#include <vector>
#include <unordered_map>
using namespace std;

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
    int postIndex; // Postorder ko peeche se track karne ke liye
    unordered_map<int, int> inMap;

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();
        // Step 1: postIndex ko last element par set karo
        postIndex = n - 1; 

        // Step 2: Inorder values ke index map mein save kar lo
        for (int i = 0; i < n; i++) {
            inMap[inorder[i]] = i;
        }

        // Step 3: Recursive function call karo
        return helper(postorder, 0, n - 1);
    }

private:
    TreeNode* helper(vector<int>& postorder, int inStart, int inEnd) {
        // Base case
        if (inStart > inEnd) {
            return nullptr;
        }

        // 1. Postorder ke end se current root nikalo aur postIndex ko peeche lao (--)
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);

        // 2. Map se inorder mein is root ki position nikalo
        int inIndex = inMap[rootVal];

        // 3. PEHLE Right Subtree banao (kyunki postorder peeche se Root -> Right -> Left hota hai)
        root->right = helper(postorder, inIndex + 1, inEnd);

        // 4. PHIR Left Subtree banao
        root->left = helper(postorder, inStart, inIndex - 1);

        return root;
    }
};