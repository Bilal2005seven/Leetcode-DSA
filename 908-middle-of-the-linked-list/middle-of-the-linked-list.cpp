class Solution {
public:
    ListNode* middleNode(ListNode* head) {

        ListNode* temp = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {

            temp = temp->next;
            fast = fast->next->next;
        }

        return temp;
    }
};