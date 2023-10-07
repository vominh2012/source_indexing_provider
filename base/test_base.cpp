#include "vector.h"
#include "list.h"
#include <cstdio> // printf
int main()
{
    int* array = 0;
    
    vector_push_back(array, 1);
    vector_push_back(array, 2);
    
    printf("front: %d\n", vector_front(array));
    printf("back: %d\n", vector_back(array));
    
    vector_push_back(array, 3);
    printf("back from referent: %d\n", *vector_back_ref(array));
    
    vector_push_back(array, 5);
    *vector_back_ref(array) = 4;
    Assert(vector_back(array) == 4);
    
    for(u64 i = 0; i < vector_count(array);++i)
        printf("item: %d\n", array[i]);
    
    vector_free(array);
    
    
    struct ListNode {
        int data;
        ListNode *next;
        ListNode *prev;
    };
    
    ListNode list;
    ListNode element1 = {1};
    ListNode element2 = {2};
    dll_init(&list);
    dll_push_back(&list, &element1);
    Assert(dll_not_empty(&list));
    dll_push_back(&list, &element2);
    
    printf("list first item: %d\n", dll_begin(&list)->data);
    dll_remove(&element1);
    printf("list last item: %d\n", dll_begin(&list)->data);
    dll_remove(&element2);
    
    Assert(dll_is_empty(&list));
    
    
    ListNode slist;
    sll_init(&slist);
    Assert(sll_is_empty(&slist));
    
    sll_push(&slist, &element1);
    printf("list first item: %d\n", sll_front(&slist)->data);
    Assert(sll_not_empty(&slist));
    sll_push(&slist, &element2);
    printf("list second item: %d\n", sll_front(&slist)->data);
    
    sll_pop(&slist);
    Assert(sll_not_empty(&slist));
    sll_pop(&slist);
    Assert(sll_is_empty(&slist));
    sll_pop(&slist); // no crashing :)
    Assert(sll_is_empty(&slist));
    
    return 0;
}