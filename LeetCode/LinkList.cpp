#include <cstdio>
#include <algorithm>
#include <unordered_map>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
 
class Solution {
public:
    /* 206 */
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return head;
        auto cur = head, aft = head->next;
        ListNode *bfr = nullptr;
        while (aft)
        {
            cur->next = bfr;
            bfr = cur;
            cur = aft;
            aft = aft->next;
        }
        cur->next = bfr;
        return cur;
    }

    /* 206 */
    ListNode* reverseList_recursive(ListNode* head)
    {
        if (!head) return nullptr;
        if (!head->next) return head;
        auto t = reverseList_recursive(head->next);
        t->next = head;
        head->next = nullptr;
        return head;
    }

    /* 92 */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (!head) return nullptr;
        if (!head->next) return head;
        if (m >= n) return head;
        int idx = 1;
        auto _h = head;
        ListNode *cur, *bfr, *aft;
        if (m <= 1)
        {
            bfr = nullptr; cur = head; aft = cur->next;
            while (aft && idx++ < n)
            {
                cur->next = bfr;
                bfr = cur; 
                cur = aft;
                aft = aft->next;
            }
            cur->next = bfr;
            _h->next = aft;
            return cur;
        }
        else
        {
            ListNode *first;
            while (_h && idx++ < m - 1)
                _h = _h->next;

            first = _h->next;
            bfr = nullptr; cur = _h->next; aft = cur->next;
            while (aft && idx++ < n)
            {
                cur->next = bfr;
                bfr = cur; 
                cur = aft;
                aft = aft->next;
            }
            cur->next = bfr;
            _h->next = cur;
            first->next = aft;
            return head;
        }
    }

    /* 160 */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        int na = 0, nb = 0;
        auto _ha = headA, _hb = headB;
        while (_ha->next)
        {
            na++; _ha = _ha->next;
        }
        na++;
        while (_hb->next)
        {
            nb++; _hb = _hb->next;
        }
        nb++;

        if (_ha != _hb)
            return nullptr;
        else
        {
            _ha = headA; _hb = headB;
            int _sub = std::abs(na - nb), _len = std::min(na, nb);
            if (na > nb)
            {
                while (_sub-- > 0) _ha = _ha->next;
            }
            else
            {
                while (_sub-- > 0) _hb = _hb->next;
            }

            while (_len-- > 0)
            {
                if (_ha == _hb)
                    return _ha;
                _ha = _ha->next; _hb = _hb->next;
            }
            return nullptr;
        }
    }

    /* 21 */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode* _h;
        if (l1->val > l2->val)
        {
            _h = l2; l2 = l2->next;
        }
        else
        {
            _h = l1; l1 = l1->next;
        }

        auto _i = _h;
        ListNode* temp;
        while (l1 && l2)
        {
            if (l1->val > l2->val)
            {
                temp = l2;
                l2 = l2->next;
                _i -> next = temp;
                _i = _i->next;
            }
            else
            {
                temp = l1;
                l1 = l1->next;
                _i -> next = temp;
                _i = _i->next;
            }
        }
        if (!l1) _i->next = l2;
        if (!l2) _i->next = l1;
        return _h;
    }

    /* 142 */
    ListNode *detectCycle(ListNode *head) {
        /* 快慢指针 */
        ListNode *slow, *fast;
        slow = fast = head;
        while (slow && fast)
        {
            slow = slow->next;
            fast = fast->next;
            if (!fast) return nullptr;
            fast = fast->next;
            if (slow == fast) break;
        }

        slow = head;
        while (slow && fast)
        {
            if (slow == fast) return slow;
            slow = slow->next;
            fast = fast->next;
        }
        return nullptr;
    }

    /* 86 */
    ListNode* partition(ListNode* head, int x) {
        if (!head) return nullptr;
        if (!head->next) return head;
        ListNode *heada, *taila, *headb, *tailb, *c;
        heada = taila = headb = tailb = nullptr;
        c = head;
        while (c)
        {
            if (c->val >= x)
            {
                if (!tailb)
                { 
                    tailb = c;
                    headb = tailb;
                }
                else
                {
                    tailb->next = c;
                    tailb = tailb->next;
                }
            }
            else
            {
                if (!taila) 
                {
                    taila = c;
                    heada = taila;
                }
                else
                {
                    taila->next = c;
                    taila = taila->next;
                }
            }
            c = c->next;
        }
        if (heada) taila->next = headb;
        if (headb) tailb->next = nullptr;
        
        if (heada) return heada;
        else return headb;
    }

    /* 138 */
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return nullptr;
        std::unordered_map<RandomListNode*, RandomListNode*> mp;
        RandomListNode *new_head, *new_list, *new_idx;
        new_head = new_list = new_idx = nullptr;
        
        auto old_list = head;
        new_head = new_list = new RandomListNode(old_list->label);
        new_list->random = old_list->random;
        mp[old_list] = new_list;
        old_list = old_list->next;
        
        while (old_list)
        {
            new_idx = new RandomListNode(old_list->label);
            new_idx->random = old_list->random;
            new_list->next = new_idx;
            mp[old_list] = new_idx;
            
            new_list = new_list->next;
            old_list = old_list->next;
        }

        new_list = new_head;
        while (new_list)
        {
            if (new_list->random)
                new_list->random = mp[new_list->random];
            new_list = new_list->next;
        }
        return new_head;
    }
};

void p(RandomListNode *head)
{
    while (head)
    {
        printf("%d ", head->label);
        head = head->next;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    RandomListNode l1(1), l2(1), l3(1), l4(5), l5(2), l6(6);
    l1.next = &l2; l2.next = &l3; l3.next = &l4;
    l4.next = &l5; l5.next = &l6;
    p(&l1);
    Solution solve;
    p(solve.copyRandomList(&l1));
    return 0;
}