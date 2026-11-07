#include <stack>

using namespace std;

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* curr = root;

        while (curr != nullptr || !st.empty()) {
            // Saare leftmost nodes push karo
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }

            // Leftmost node bahar nikalo (Sorted order me next node)
            curr = st.top();
            st.pop();

            // Ek element process ho gaya
            k--;
            if (k == 0) {
                return curr->val; // kth element milte hi instant exit
            }

            // Right subtree explore karo
            curr = curr->right;
        }

        return -1;
    }
};