class Solution {
public:

    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<
            ListNode*,
            vector<ListNode*>,
            compare
        > pq;

        // Put first node of every list into heap
        for (ListNode* node : lists) {
            if (node != nullptr) {
                pq.push(node);
            }
        }

        // Dummy node
        ListNode dummy(0);
        ListNode* temp = &dummy;

        while (!pq.empty()) {

            // Get smallest node
            ListNode* node = pq.top();
            pq.pop();

            // Add it to answer
            temp->next = node;
            temp = temp->next;

            // Add next node from same list
            if (node->next != nullptr) {
                pq.push(node->next);
            }
        }

        return dummy.next;
    }
};