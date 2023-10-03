(php_tag) @tag
"?>" @tag

; Functions
(method_declaration
  name: (name) @method)

(function_call_expression
  function: (qualified_name (name)) @function)

(function_call_expression
  (name) @function)

(scoped_call_expression
  name: (name) @function)

(member_call_expression
  name: (name) @method)

(function_definition
  name: (name) @function)

(nullsafe_member_call_expression
    name: (name) @method)

; Namespace
(namespace_definition
  name: (namespace_name) @namespace)

; Conditions ( ? : )
(conditional_expression) @conditional
; Basic tokens

[
 (string)
 (heredoc)
 (shell_command_expression) ; backtick operator: `ls -la`
 ] @string
(encapsed_string (escape_sequence) @string.escape)

(boolean) @boolean
(null) @constant.builtin
(integer) @number
(float) @float
(comment) @comment

(named_label_statement) @label
; Keywords

[
 "and"
 "as"
 "instanceof"
 "or"
 "xor"
] @keyword.operator

[
 "fn"
 "function"
] @keyword.function

[
 "$"
 "abstract"
 "break"
 "class"
 "clone"
 "const"
 "declare"
 "default"
 "echo"
 "enddeclare"
 "enum"
 "extends"
 "final"
 "global"
 "goto"
 "implements"
 "insteadof"
 "interface"
 "namespace"
 "new"
 "private"
 "protected"
 "public"
 "static"
 "trait"
 "unset"
 ] @keyword

[
  "return"
  "yield"
] @keyword.return

[
 "case"
 "else"
 "elseif"
 "endif"
 "endswitch"
 "if"
 "switch"
 "match"
  "??"
 ] @conditional

[
 "continue"
 "do"
 "endfor"
 "endforeach"
 "endwhile"
 "for"
 "foreach"
 "while"
 ] @repeat

[
 "catch"
 "finally"
 "throw"
 "try"
 ] @exception

[
 "include_once"
 "include"
 "require_once"
 "require"
 "use"
 ] @include
