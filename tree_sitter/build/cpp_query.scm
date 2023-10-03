[
 (type_identifier)
 (primitive_type)
 (sized_type_specifier)
 (type_descriptor)
] @type

(string_literal) @string
(system_lib_string) @string
(escape_sequence) @string.escape

(null) @constant.builtin
(number_literal) @number
(char_literal) @character

(comment) @comment

(call_expression
  function: (identifier) @function)
(call_expression
  function: (field_expression
    field: (field_identifier) @function))
(function_declarator
  declarator: (identifier) @function)
(preproc_function_def
  name: (identifier) @function.macro)
  

[
  "const"
  "default"
  "enum"
  "extern"
  "inline"
  "static"
  "struct"
  "typedef"
  "union"
  "volatile"
  "goto"
  "register"

] @keyword

"sizeof" @keyword.operator
"return" @keyword.return

[
  "while"
  "for"
  "do"
  "continue"
  "break"
] @repeat

[
 "if"
 "else"
 "case"
 "switch"
] @conditional

[
 "#define"
  "#if"
  "#ifdef"
  "#ifndef"
  "#else"
  "#elif"
  "#endif"
  (preproc_directive)
] @keyword

[
 (true)
 (false)
] @boolean

"#include" @include
[
  "__attribute__"
  "__cdecl"
  "__clrcall"
  "__stdcall"
  "__fastcall"
  "__thiscall"
  "__vectorcall"
  "_unaligned"
  "__unaligned"
  "__declspec"
] @attribute

(ERROR) @error