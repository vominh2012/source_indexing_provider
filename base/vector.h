/* date = October 3rd 2023 0:32 pm */
/* author: huantran */
/* this vector implementation that make things work almost like a normal array */

#ifndef VECTOR_H
#define VECTOR_H
#include "common.h"

// redefine these before the header if you want call to your allocator
#ifndef vector_mem_alloc
#include <stdlib.h> // malloc, realloc, free
#define vector_mem_alloc malloc
#define vector_mem_realloc realloc
#define vector_mem_free free
#endif

struct VectorHeader
{
    u64 size;
    u64 capacity;
};

#define vector(v) (v)*
#define vector_count(v) ((v) ? vector_get_header(v)->size : 0)
#define vector_push_back(v, element) { u64 size = vector_maybe_expand((void**)&v, sizeof(*v), 1); v[size] = element; vector_get_header(v)->size++;}
#define vector_reserve(v, size) { vector_maybe_expand((void**)&v, sizeof(*v), size);}
#define vector_pop_back(v) { if(v) vector_get_header(v)->size--;}
#define vector_back(v) (v[vector_count(v) - 1])
#define vector_front(v) (v[0])
#define vector_back_ref(v) (&v[vector_count(v) - 1])
#define vector_front_ref(v) (&v[0])
#define vector_free(v) { vector_mem_free(vector_get_header(v)); v = 0; }

VectorHeader *vector_get_header(void *vector)
{
    return (VectorHeader*)(vector) - 1;
}

function u64 vector_maybe_expand(void **vec_ref, u64 type_size, u64 size)
{
    VectorHeader *header = 0;
    
    if (*vec_ref)
    {
        header = vector_get_header(*vec_ref);
        u64 new_size = header->size + size;
        if (new_size > header->capacity)
        {
            u64 new_capacity = (u64)(header->capacity * 1.5) + size;
            header = (VectorHeader*) vector_mem_realloc(header, new_capacity * type_size + sizeof(VectorHeader));
            header->capacity = new_capacity;
        }
    }
    else
    {
        u32 header_size = sizeof(VectorHeader);
        u32 default_capacity = 8;
        header = (VectorHeader *)vector_mem_alloc(header_size  +  default_capacity * type_size); 
        header->size = 0;
        header->capacity = default_capacity;
    }
    
    *vec_ref = header + 1;
    return header->size;
}
#endif //VECTOR_H
