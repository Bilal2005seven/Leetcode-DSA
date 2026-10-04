class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* temp = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            temp = temp->next;
            fast = fast->next->next;

            if (temp == fast) {
                return true;
            }
        }

        return false;
    }
};