#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        if(root == nullptr) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int n = q.size();
            vector<int> curr;
            for(int i = 0; i < n; i++) {

                TreeNode* top = q.front();
                q.pop();

                curr.push_back(top->val);

                if(top->left) q.push(top->left);
                if(top->right) q.push(top->right);
            }

            ans.push_back(curr);
        }

        return ans;
    }
};