@echo off

set COMMON_FLAGS=/Od /DUNICODE /W4 /Z7 /EHsc /wd4996 /wd4042 /wd4505 /nologo /MT
set BUILD_FLAGS=%COMMON_FLAGS%  /link  Advapi32.lib

cl main.cpp platform_win32.cpp /Fesource_indexing_provider.exe %BUILD_FLAGS% 
cl test_client.cpp /Fetest_client.exe %BUILD_FLAGS% 
cl base/test_base.cpp /Fetest_base.exe %BUILD_FLAGS% 

del *.ilk
del *.obj
