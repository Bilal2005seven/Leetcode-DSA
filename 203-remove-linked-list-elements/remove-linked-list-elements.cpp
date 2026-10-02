class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {

        ListNode temp(0);
        temp.next = head;

        ListNode* curr = &temp;

        while (curr->next != nullptr) {

            if (curr->next->val == val) {
                curr->next = curr->next->next;
            }
            else {
                curr = curr->next;
            }
        }

        return temp.next;
    }
};
