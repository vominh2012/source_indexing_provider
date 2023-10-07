/* date = October 7th 2023 7:10 am */

#ifndef LIST_H
#define LIST_H

struct Node {
    Node *next;
    Node *prev;
};

// double circular linked list
// sentinal, node, type 
#define dll_init_(s) s->next=s,s->prev=s
#define dll_begin_(s) s->next
#define dll_end_(s) s->prev
#define dll_is_end_(s, n) (n == s)
#define dll_next_(n) n->next
#define dll_is_empty_(s) (s->next) == (s)
#define dll_not_empty_(s) (s->next) != (s)

#define dll_insert_(n, val) val->prev =n, val->next=n->next, val->prev->next=val, val->next->prev=val
#define dll_push_back_(s, n) dll_insert_(s->prev, n)
#define dll_push_front_(s, n) dll_insert_(s, n)

#define dll_remove_(n) n->prev->next=n->next, n->next->prev=n->prev, n->next=n->prev=0

#define dll_init(s) dll_init_((s))
#define dll_begin(s) dll_begin_((s))
#define dll_end(s) dll_end_((s))
#define dll_is_end(s, n) dll_is_end_((s), (n))
#define dll_next(n) dll_next_((n))
#define dll_is_empty(s) dll_is_empty_((s))
#define dll_not_empty(s) dll_not_empty_((s))

#define dll_push_back(s, n) dll_push_back_((s), (n))
#define dll_push_front(s, n) dll_push_front_((s), (n))

#define dll_remove(n) dll_remove_((n)) 

// single link list
#define sll_init(s) ((s)->next = s)
#define sll_push(s, n) (n)->next = (s)->next, (s)->next=(n)
#define sll_pop(s) (s)->next = (s)->next->next
#define sll_front(s) (s)->next
#define sll_front_ref(s) &(s)->next
#define sll_is_empty(s) ((s)->next == s)
#define sll_not_empty(s) ((s)->next != s)

#endif //LIST_H
