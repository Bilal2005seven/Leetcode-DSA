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
    // Preorder mein current root track karne ke liye global/member index
    int preIndex = 0; 
    // Inorder values ke index O(1) mein nikalne ke liye map
    unordered_map<int, int> inMap; 

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Step 1: Inorder ke har element ka index map mein save kar lo
        for (int i = 0; i < inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }
        
        // Step 2: Recursive function call karo poori range (0 se n-1) ke liye
        return helper(preorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* helper(vector<int>& preorder, int inStart, int inEnd) {
        // Base case: Agar range invalid ho gayi, matlab koi node nahi bacha
        if (inStart > inEnd) {
            return nullptr;
        }

        // 1. Preorder se current root nikalo aur preIndex ko aage badhao
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);

        // 2. Map se dekho ki yeh rootVal inorder array mein kahan hai
        int inIndex = inMap[rootVal];

        // 3. Pehle Left Subtree banao (kyunki Preorder mein Root ke baad Left aata hai)
        root->left = helper(preorder, inStart, inIndex - 1);

        // 4. Phir Right Subtree banao
        root->right = helper(preorder, inIndex + 1, inEnd);

        return root;
    }
};