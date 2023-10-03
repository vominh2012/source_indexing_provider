/* date = October 2nd 2023 7:46 am */

#ifndef TOKEN_H
#define TOKEN_H

enum IndexTokenKind
{
    IndexTokenKind__EOF = 0,
    IndexTokenKind_Whitespace = 1,
    IndexTokenKind_LexError = 2,
    IndexTokenKind_Comment = 3,
    IndexTokenKind_Keyword = 4,
    IndexTokenKind_Preprocessor = 5,
    IndexTokenKind_Identifier = 6,
    IndexTokenKind_Operator = 7,
    IndexTokenKind_LiteralInteger = 8,
    IndexTokenKind_LiteralFloat = 9,
    IndexTokenKind_LiteralString = 10,
    IndexTokenKind_ScopeOpen = 11,
    IndexTokenKind_ScopeClose = 12,
    IndexTokenKind_ParentheticalOpen = 13,
    IndexTokenKind_ParentheticalClose = 14,
    IndexTokenKind_StatementClose = 15,
    IndexTokenKind_Function = 16,
    IndexTokenKind_Type = 17,
    
    IndexTokenKind_Count,
};
#endif //TOKEN_H
