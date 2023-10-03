/* date = October 1st 2023 1:32 pm */

#ifndef PLATFORM_H
#define PLATFORM_H
#include "base/common.h"

struct SystemLibrary;

SystemLibrary* system_load_library(StringView8 lib_path);
void* system_get_proc(SystemLibrary *lib, StringView8 function_name);

void system_release_library(SystemLibrary *lib);

#endif //PLATFORM_H
