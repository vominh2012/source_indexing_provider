/* date = October 1st 2023 1:22 pm */

#ifndef TREE_SITTER_HELPER_H
#define TREE_SITTER_HELPER_H
extern "C" {
#pragma warning(push, 0)
#include "tree_sitter/include/tree_sitter/api.h"
#pragma warning( pop )
}

#include "token.h"

typedef struct capture_token {
    char *capture_name;
    u32 capture_name_size;
    
    u32 token_kind;
} capture_token;


typedef struct TSLanguageData {
    TSLanguageData *next;
    TSLanguageData *prev;
    
    StringView8 extensions;
    StringView8 dll_name;
    char *function_name;
    String8 query_string;
    
    b32 support_virtual_whilespace;
    b32 support_auto_indent;
    
    void *language;
    void *query;
    capture_token *capture_token_table;
    u32 capture_token_table_size;
} TSLanguageData;

struct SystemLibrary;

void* get_library_function(StringView8 dll_name, StringView8 function_name) {
    void *func = 0;
    SystemLibrary * lib = system_load_library(dll_name);
    if (lib){
        func = system_get_proc(lib, function_name);
        if (!func) {
            system_release_library(lib);
        }
    }
    
    return func;
}

TSLanguage *get_library_language(StringView8 dll_name, StringView8 function_name)
{
    typedef TSLanguage*(__stdcall *tree_sitter_scanner)();
    
    TSLanguage *lang = 0;
    tree_sitter_scanner scanner = (tree_sitter_scanner)get_library_function(dll_name, function_name);
    if (scanner)
    {
        lang = scanner();
    }
    
    return lang;
}


function u32 token_kind_from_capture_name(char *capture_name, u32 capture_name_size)
{
    struct string_token {
        StringView8 str;
        
        IndexTokenKind token_kind;
    };
    
    const string_token string_token_table[] = {
        {StringView8("comment"), IndexTokenKind_Comment},
        {StringView8("string"), IndexTokenKind_LiteralString},
        {StringView8("number"), IndexTokenKind_LiteralInteger},
        {StringView8("constant"), IndexTokenKind_LiteralInteger},
        {StringView8("boolean"), IndexTokenKind_LiteralInteger},
        {StringView8("keyword"), IndexTokenKind_Keyword},
        {StringView8("attribute"), IndexTokenKind_Keyword},
        {StringView8("conditional"), IndexTokenKind_Keyword},
        {StringView8("repeat"), IndexTokenKind_Keyword},
        {StringView8("type"), IndexTokenKind_Type},
        {StringView8("function"), IndexTokenKind_Function},
        {StringView8("method"), IndexTokenKind_Function},
        {StringView8("include"), IndexTokenKind_Preprocessor},
        {StringView8("tag"), IndexTokenKind_Keyword},
    };
    
    // colors: keyword, type, function, constant, string, number, comment
    
    for( u32 k = 0; k < ArrayCount(string_token_table); ++k)
    {
        string_token item = string_token_table[k];
        if (str_begin_with(capture_name, capture_name_size, item.str.str, item.str.size))
        {
            return item.token_kind;
        }
    }
    
    return 0;
}

function bool initialize_language_data(TSLanguageData *lang)
{
    bool success = false;
    TSQuery *query = 0;
    
    TSLanguage *language = get_library_language(lang->dll_name, lang->function_name); 
    if (language)
    {
        TSQueryError error_type = TSQueryErrorNone;
        u32 error_offset = 0;
        query = ts_query_new(language,
                             (char*)lang->query_string.str,
                             lang->query_string.size,
                             &error_offset,
                             &error_type);
        
        if (query && error_type == TSQueryErrorNone)
        {
            
            u32 capture_count = ts_query_capture_count(query);
            lang->capture_token_table = (capture_token*)malloc(sizeof(capture_token) *  capture_count);
            lang->capture_token_table_size = capture_count;
            
            for (u32 i = 0; i < capture_count; ++i)
            {
                u32 capture_name_size = 0;
                char *capture_name = (char*)ts_query_capture_name_for_id(query,
                                                                         i,
                                                                         &capture_name_size);
                if (capture_name && capture_name_size > 0)
                {
                    lang->capture_token_table[i].capture_name = capture_name;
                    lang->capture_token_table[i].capture_name_size = capture_name_size;
                    lang->capture_token_table[i].token_kind = token_kind_from_capture_name(capture_name, capture_name_size);
                }
            }
            
            lang->language = language;
            lang->query = query;
            success = true;
        }
    }
    
    if (!success) {
        if (language) {
            // TODO: free language ??
        }
        if (query)
        {
            ts_query_delete(query);
        }
    }
    return success;
}



function void set_language_info(Arena *arena, TSLanguageData *lang_data, String_Const_u8 dll_name, char *function_name, char *query_file, String_Const_u8 extensions,
                                b32 support_virtual_whilespace = false, b32 support_auto_indent = false)
{
    String8 binary_path = system_get_path(arena, SystemPath_Binary);
    String8 full_dll_path = push_u8_stringf(arena, "%.*s/%.*s", string_expand(binary_path), string_expand(dll_name));
    String8 full_query_file_path = push_u8_stringf(arena, "%.*s/%s", string_expand(binary_path), query_file);
    
    lang_data->dll_name = full_dll_path;
    lang_data->function_name = function_name;
    lang_data->extensions = extensions;
    lang_data->query_string = read_entire_file(arena, full_query_file_path);
    lang_data->support_virtual_whilespace = support_virtual_whilespace;
    lang_data->support_auto_indent = support_auto_indent;
}

void tree_sitter_init(TSLanguageData *langs)
{
    dll_init_sentinel(langs);
    
    int max_lang = 10;
    int c = 0;
    
    
    TSLanguageData *lang_data = push_array(arena, TSLanguageData, max_lang);
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/cpp_scanner.dll"), "tree_sitter_cpp", "tree_sitter/cpp_query.scm", str8_lit(".h.cpp.cc.c.hpp"), true, true);
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/js_scanner.dll"), "tree_sitter_javascript", "tree_sitter/js_query.scm", str8_lit(".js"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/php_scanner.dll"), "tree_sitter_php", "tree_sitter/php_query.scm", str8_lit(".php"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/java_scanner.dll"), "tree_sitter_java", "tree_sitter/java_query.scm", str8_lit(".java"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/html_scanner.dll"), "tree_sitter_html", "tree_sitter/html_query.scm", str8_lit(".html.htm"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/css_scanner.dll"), "tree_sitter_css", "tree_sitter/css_query.scm", str8_lit(".css"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/json_scanner.dll"), "tree_sitter_json", "tree_sitter/json_query.scm", str8_lit(".json"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/python_scanner.dll"), "tree_sitter_python", "tree_sitter/python_query.scm", str8_lit(".py"));
    set_language_info(arena, &lang_data[c++], str8_lit("tree_sitter/bash_scanner.dll"), "tree_sitter_bash", "tree_sitter/bash_query.scm", str8_lit(".sh"));
    
    Assert(c <= max_lang);
    for (int i = 0; i < c; ++i)
    {
        dll_insert_back(langs, &lang_data[i]);
    }
    
}


#endif //TREE_SITTER_HELPER_H
