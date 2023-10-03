#include "vector.h"
#include <cstdio> // printf
int main()
{
    int* array = 0;
    
    vector_push_back(array, 1);
    vector_push_back(array, 2);
    vector_push_back(array, 3);
    
    printf("back: %d\n", vector_back(array));
    printf("back from referent: %d\n", *vector_back_ref(array));
    
    *vector_back_ref(array) = 4;
    Assert(vector_back(array) == 4);
    
    for(u64 i = 0; i < vector_count(array);++i)
        printf("item: %d\n", array[i]);
    
    vector_free(array);
    
    return 0;
}