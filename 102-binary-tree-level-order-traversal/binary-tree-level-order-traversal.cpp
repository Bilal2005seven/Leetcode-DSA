class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;

        if (root == NULL) {
            return result;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            int size = q.size();   // number of nodes in current level
            vector<int> level;     // store this level

            for (int i = 0; i < size; i++) {

                TreeNode* curr = q.front();
                q.pop();

                level.push_back(curr->val);

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            result.push_back(level); // add level to result
        }

        return result;
    }
};