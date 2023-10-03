#include "platform.h"
#include "Windows.h"

struct SystemLibrary {
    HMODULE handle;
};

SystemLibrary* system_load_library(StringView8 lib_path)
{
    SystemLibrary *lib = (SystemLibrary*)malloc(sizeof(SystemLibrary));
    lib->handle = LoadLibraryA(lib_path.str);
    if (!lib->handle) {
        free(lib);
        lib  = 0;
    }
    
    return lib;
    
}

void* system_get_proc(SystemLibrary *lib, StringView8 function_name)
{
    Assert(lib);
    return GetProcAddress(lib->handle, function_name.str);
}

void system_release_library(SystemLibrary *lib)
{
    Assert(lib);
    FreeLibrary(lib->handle);
    free(lib);
}