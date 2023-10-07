/* date = October 1st 2023 1:21 pm */
/* author: huantran */

#ifndef COMMON_H
#define COMMON_H

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef bool b32;

#define Assert(condition) if(!(condition)) { (*(void**)0) = 0;}
#define function static
#define ArrayCount(a) ((sizeof(a))/(sizeof(*a)))

#define KB(n) ((n) * 1024)
#define MB(n) ((n) * KB(1024))
#define GB(n) ((n) * MB(1024))

struct String8 {
    char *str;
    u32 size;
};

struct StringView8 {
    char *str;
    u32 size;
    
    StringView8(char *c_str)
    {
        str = c_str;
        for (char *c = c_str; *c; c++)
        {
            ++size;
        }
    }
};


function bool str_begin_with(char *str, int  str_size, char *begin, int begin_size)
{
    if (str_size < begin_size)
    {
        return false;
    }
    
    for (int i = 0; i < begin_size; ++i)
    {
        if (str[i] != begin[i]) 
        {
            return false;
        }
    }
    return true;
}

#endif //COMMON_H
