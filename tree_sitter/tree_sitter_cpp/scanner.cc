

enum TokenType {
    RAW_STRING_LITERAL,
};

struct Scanner {
    int i;
};

bool cpp_scan(TSLexer *lexer, const bool *valid_symbols) {
    while (iswspace(lexer->lookahead)) {
        lexer->advance(lexer, true);
    }
    
    lexer->result_symbol = RAW_STRING_LITERAL;
    
    // Raw string literals can start with: R, LR, uR, UR, u8R
    // Consume 'R'
    if (lexer->lookahead == 'L' || lexer->lookahead == 'U') {
        lexer->advance(lexer, false);
        if (lexer->lookahead != 'R') {
            return false;
        }
    } else if (lexer->lookahead == 'u') {
        lexer->advance(lexer, false);
        if (lexer->lookahead == '8') {
            lexer->advance(lexer, false);
            if (lexer->lookahead != 'R') {
                return false;
            }
        } else if (lexer->lookahead != 'R') {
            return false;
        }
    } else if (lexer->lookahead != 'R') {
        return false;
    }
    lexer->advance(lexer, false);
    
    // Consume '"'
    if (lexer->lookahead != '"') return false;
    lexer->advance(lexer, false);
    
    // Consume '(', delimiter
    char delimiter[2048];
    int pos = 0;
    
    for (;;) {
        if (lexer->lookahead == 0 || lexer->lookahead == '\\' || iswspace(lexer->lookahead)) {
            return false;
        }
        if (lexer->lookahead == '(') {
            lexer->advance(lexer, false);
            break;
        }
        delimiter[pos++] = lexer->lookahead;
        lexer->advance(lexer, false);
    }
    
    // Consume content, delimiter, ')', '"'
    int delimiter_index = -1;
    for (;;) {
        if (lexer->lookahead == 0) return false;
        
        if (delimiter_index >= 0) {
            if ((size_t)(delimiter_index) == pos) {
                if (lexer->lookahead == '"') {
                    lexer->advance(lexer, false);
                    return true;
                } else {
                    delimiter_index = -1;
                }
            } else {
                if (lexer->lookahead == delimiter[delimiter_index]) {
                    delimiter_index++;
                } else {
                    delimiter_index = -1;
                }
            }
        }
        
        if (delimiter_index == -1 && lexer->lookahead == ')') {
            delimiter_index = 0;
        }
        
        lexer->advance(lexer, false);
    }
}


void *tree_sitter_cpp_external_scanner_create() {
    static struct Scanner s;
    return &s;
}

bool tree_sitter_cpp_external_scanner_scan(void *payload, TSLexer *lexer,
                                           const bool *valid_symbols) {
    return cpp_scan(lexer, valid_symbols);
}

unsigned tree_sitter_cpp_external_scanner_serialize(void *payload, char *buffer) {
    return 0;
}

void tree_sitter_cpp_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {
}

void tree_sitter_cpp_external_scanner_destroy(void *payload) {
}

