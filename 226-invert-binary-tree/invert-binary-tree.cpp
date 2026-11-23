/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include<bits/stdc++.h>
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> q ;
        if (root == nullptr) return nullptr;
        q.push(root);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();
            swap(front->left , front->right);
            if(front->left != nullptr) q.push(front->left);
            if(front->right != nullptr) q.push(front->right);
        } return root ;
    }
};