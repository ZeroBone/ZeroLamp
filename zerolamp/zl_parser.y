%token_prefix T_

%token_type {Token}
%default_type {Token}

%token_destructor {
    // TODO
}

%name zl_parse

%include {
#include "token.h"

// we will not call free with a null pointer, turn off the guard
#define YYPARSEFREENEVERNULL 1
}

%extra_context {parser_context_t* context}

%syntax_error {
    parser_onSyntaxError(context, &TOKEN);
}

%parse_accept {
    parser_onParsingFinished(context);
}

%parse_failure {
    parser_onFatalSyntaxError(context);
}

%default_destructor {
    ast_defaultDestructor($$);
}

%stack_size 100

%stack_overflow {
    parser_onStackOverflow(context);
}

%start_symbol root

// ==================================
// GRAMMAR START
// ==================================
// terminals -> all uppercase
// non terminals -> all lowercase

root ::= definition_list.

%type definition_list {std::vector<DefinitionNode*>}
definition_list ::= . {}
definition_list ::= definition_list(DL) definition(D). { DL.push_back(D); }

// function definition
%type definition {DefinitionNode*}
definition(D) ::= FN ID LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = new FunctionDefinitionNode(SL); }
definition(D) ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = new FunctionDefinitionNode(SL); }
definition(D) ::= FN ID LEFT_PARENTHESIS formal_parameters(FP) RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = new FunctionDefinitionNode(FP, SL); }

// event handler definition
definition(D) ::= ON ID LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = new EventHandlerDefinitionNode(SL); }
definition(D) ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = new EventHandlerDefinitionNode(SL); }
definition(D) ::= ON ID LEFT_PARENTHESIS actual_parameters(AP) RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { D = EventHandlerDefinitionNode(AP, SL); }

%type formal_parameters {std::vector<std::string>}
formal_parameters(FPS) ::= ID(NAME). { std::vector<std::string> v; v.push_back(NAME); FPS = std::move(v); }
formal_parameters(FPS_NEW) ::= formal_parameters(FPS) COMMA ID(NAME). { FPS_NEW = std::move(FPS); FPSN.push_back(NAME); }

%type actual_parameter {ActualParameterNode*}
actual_parameter(AP) ::= expression(VALUE). { AP = ActualParameterNode(VALUE); }
actual_parameter(AP) ::= ID(KEY) EQUALS expression(VALUE). { AP = ActualParameterNode(KEY, VALUE); }

%type actual_parameters {std::vector<ActualParameterNode*>}
actual_parameters(APS) ::= actual_parameter(AP). { std::vector<ActualParameterNode*> v; APS = std::move(v); }
actual_parameters(APS_NEW) ::= actual_parameters(APS) COMMA actual_parameter(AP). { APS.push_back(AP); APS_NEW = std::move(APS);  }

%type statement_list {std::vector<StatementNode*>}
statement_list(SL) ::= . { std::vector<StatementNode*> v; SL = std::move(v); }
statement_list(SL_NEW) ::= statement_list(SL) statement(S). { SL.push_back(S); SL_NEW = std::move(SL); }

// statements
// function call
%type statement {StatementNode*}
statement(S) ::= ID(FUNCTION_NAME) LEFT_PARENTHESIS RIGHT_PARENTHESIS. { S = new FunctionCallStatementNode(FUNCTION_NAME); }
statement(S) ::= ID(FUNCTION_NAME) LEFT_PARENTHESIS actual_parameters(APS) RIGHT_PARENTHESIS. { S = new FunctionCallStatementNode(FUNCTION_NAME, APS); }

// push statement
statement(S) ::= ID(DISPLAY) ID(MODE) SEMICOLON. { S = new PushStatementNode(DISPLAY, MODE); }
statement(S) ::= ID(DISPLAY) ID(MODE) SEMICOLON IF expression(CONDITION). { S = new PushStatementNode(DISPLAY, MODE, CONDITION); }

// expressions
simple_expression(E) ::= ID(T).
simple_expression(E) ::= INT_V(T).
simple_expression(E) ::= FLOAT_V(T).
simple_expression(E) ::= STRING_V(T).
simple_expression(E) ::= TRUE.
simple_expression(E) ::= FALSE.
simple_expression(E) ::= LEFT_PARENTHESIS expression(NEXT_E) RIGHT_PARENTHESIS.

// postfix expressions
postfix_expression(E) ::= simple_expression(PREV_E).
postfix_expression(E) ::= postfix_expression(BASE) LEFT_BRACKET expression(INDEX) RIGHT_BRACKET.
postfix_expression(E) ::= postfix_expression(BASE) LEFT_PARENTHESIS RIGHT_PARENTHESIS.
postfix_expression(E) ::= postfix_expression(BASE) LEFT_PARENTHESIS actual_parameters(A_PARAMS) RIGHT_PARENTHESIS.
postfix_expression(E) ::= postfix_expression(BASE) DOT ID(T).
postfix_expression(E) ::= postfix_expression(BASE) INCREMENT.
postfix_expression(E) ::= postfix_expression(BASE) DECREMENT.

// pow expression (right-accociative)
%type pow_expression {base_node_t*}
pow_expression(E) ::= postfix_expression(PREV_E). { E = PREV_E; }
pow_expression(E) ::= postfix_expression(L) POW pow_expression(R). { // a ** b // right-associative => right recursion, this is not good
    AST_DEBUG("Pow expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_POW, L, R);
}
pow_expression(E) ::= INCREMENT unary_expression(BASE). {
    // pre-increment
    AST_DEBUG("Pre increment expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_PRE_INCREMENT, BASE);
}
pow_expression(E) ::= DECREMENT unary_expression(BASE). {
    // pre-decrement
    AST_DEBUG("Pre decrement expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_PRE_DECREMENT, BASE);
}

// unary expressions
%type unary_expression {base_node_t*}
unary_expression(E) ::= pow_expression(PREV_E). { E = PREV_E; }
unary_expression(E) ::= MINUS unary_expression(BASE). { // - (unary)
    AST_DEBUG("Unary minus expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_MINUS, BASE);
}
unary_expression(E) ::= BITWISE_INVERT unary_expression(BASE). { // ~ (unary)
    AST_DEBUG("Unary bitwise invert expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_BITWISE_INVERT, BASE);
}
unary_expression(E) ::= INVERT unary_expression(BASE). { // ! (unary)
    AST_DEBUG("Unary logic invert.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_INVERT, BASE);
}
unary_expression(E) ::= SIZEOF unary_expression(BASE). { // sizeof a
    AST_DEBUG("Sizeof var expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_SIZEOF_VAR, BASE);
}
/*unary_expression(E) ::= SIZEOF LEFT_PARENTHESIS type_name(TYPE) RIGHT_PARENTHESIS. { // sizeof(a) (this is sizeof <type>)
    AST_DEBUG("Sizeof type expression.");
    E = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_SIZEOF_TYPE, TYPE);
}*/

// cast expression
%type cast_expression {base_node_t*}
cast_expression(E) ::= unary_expression(PREV_E). { E = PREV_E; }
/*cast_expression(E) ::= type_name(TYPE) LESS_THAN unary_expression(OPERAND) GREATER_THAN. { // type<exp>
    AST_DEBUG("Cast expression.");
    E = (base_node_t*)ast_newCastExpressionNode(TYPE, OPERAND);
}*/

// multiplicative expression
%type multiplicative_expression {base_node_t*}
multiplicative_expression(E) ::= cast_expression(PREV_E). { E = PREV_E; }
multiplicative_expression(E) ::= multiplicative_expression(L) MULTIPLY cast_expression(R). { // a * b
    AST_DEBUG("Multiply expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_MULTIPLY, L, R);
}
multiplicative_expression(E) ::= multiplicative_expression(L) DIVIDE cast_expression(R). { // a / b
    AST_DEBUG("Divide expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_DIVIDE, L, R);
}
multiplicative_expression(E) ::= multiplicative_expression(L) REMAINDER cast_expression(R). { // a % b
    AST_DEBUG("Remainder expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_REMAINDER, L, R);
}

// additive expression
%type additive_expression {base_node_t*}
additive_expression(E) ::= multiplicative_expression(PREV_E). { E = PREV_E; }
additive_expression(E) ::= additive_expression(L) PLUS multiplicative_expression(R). { // a + b
    AST_DEBUG("Plus expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_PLUS, L, R);
}
additive_expression(E) ::= additive_expression(L) MINUS multiplicative_expression(R). { // a - b
    AST_DEBUG("Minus expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_MINUS, L, R);
}

// bitwise shift expression
%type bitwise_shift_expression {base_node_t*}
bitwise_shift_expression(E) ::= additive_expression(PREV_E). { E = PREV_E; }
bitwise_shift_expression(E) ::= bitwise_shift_expression(L) BITWISE_SHIFT_LEFT additive_expression(R). { // a << b
    AST_DEBUG("Bitwise shift left expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_SHIFT_LEFT, L, R);
}
bitwise_shift_expression(E) ::= bitwise_shift_expression(L) BITWISE_SHIFT_RIGHT additive_expression(R). { // a >> b
    AST_DEBUG("Bitwise shift right expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_SHIFT_RIGHT, L, R);
}

// comparison expression
%type comparison_expression {base_node_t*}
comparison_expression(E) ::= bitwise_shift_expression(PREV_E). { E = PREV_E; }
comparison_expression(E) ::= comparison_expression(L) LESS_THAN bitwise_shift_expression(R). { // a < b
    AST_DEBUG("Less than expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_LESS_THAN, L, R);
}
comparison_expression(E) ::= comparison_expression(L) GREATER_THAN bitwise_shift_expression(R). { // a > b
    AST_DEBUG("Greater than expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_GREATER_THAN, L, R);
}
comparison_expression(E) ::= comparison_expression(L) LESS_THAN_OR_EQUALS bitwise_shift_expression(R). { // a <= b
    AST_DEBUG("Less than or equals expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_LESS_THAN_OR_EQUALS, L, R);
}
comparison_expression(E) ::= comparison_expression(L) GREATER_THAN_OR_EQUALS bitwise_shift_expression(R). { // a >= b
    AST_DEBUG("Greater than or equals expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_GREATER_THAN_OR_EQUALS, L, R);
}

// equality expression
%type equality_expression {base_node_t*}
equality_expression(E) ::= comparison_expression(PREV_E). { E = PREV_E; }
equality_expression(E) ::= equality_expression(L) EQUALS comparison_expression(R). { // a == b
    AST_DEBUG("Equals expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_EQUALS, L, R);
}
equality_expression(E) ::= equality_expression(L) NOT_EQUALS comparison_expression(R). { // a != b
    AST_DEBUG("Not equals expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_NOT_EQUALS, L, R);
}

// bitwise and expression
%type bitwise_and_expression {base_node_t*}
bitwise_and_expression(E) ::= equality_expression(PREV_E). { E = PREV_E; }
bitwise_and_expression(E) ::= bitwise_and_expression(L) BITWISE_AND equality_expression(R). { // a & b
    AST_DEBUG("Bitwise and expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_AND, L, R);
}

// bitwise xor expression
%type bitwise_xor_expression {base_node_t*}
bitwise_xor_expression(E) ::= bitwise_and_expression(PREV_E). { E = PREV_E; }
bitwise_xor_expression(E) ::= bitwise_xor_expression(L) BITWISE_XOR bitwise_and_expression(R). { // a ^ b
    AST_DEBUG("Bitwise xor expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_XOR, L, R);
}

// bitwise or expression
%type bitwise_or_expression {base_node_t*}
bitwise_or_expression(E) ::= bitwise_xor_expression(PREV_E). { E = PREV_E; }
bitwise_or_expression(E) ::= bitwise_or_expression(L) BITWISE_OR bitwise_xor_expression(R). { // a | b
    AST_DEBUG("Bitwise or expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_OR, L, R);
}

// and expression (logical)
%type and_expression {base_node_t*}
and_expression(E) ::= bitwise_or_expression(PREV_E). { E = PREV_E; }
and_expression(E) ::= and_expression(L) AND bitwise_or_expression(R). { // a && b
    AST_DEBUG("And expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_AND, L, R);
}

// or expression (logical)
%type or_expression {base_node_t*}
or_expression(E) ::= and_expression(PREV_E). { E = PREV_E; }
or_expression(E) ::= or_expression(L) OR and_expression(R). { // a || b
    AST_DEBUG("Or expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_OR, L, R);
}

// ternary expression (right associative)
%type ternary_expression {base_node_t*}
ternary_expression(E) ::= or_expression(PREV_E). { E = PREV_E; }
ternary_expression(E) ::= or_expression(COND) QUESTION_MARK expression(IFCOND) COLON ternary_expression(ELSECOND). { // a ? b : c
    AST_DEBUG("Ternary expression.");
    E = (base_node_t*)ast_newTernaryExpressionNode(COND, IFCOND, ELSECOND);
}

// assignment expression
%type assignment_expression {base_node_t*}
assignment_expression(E) ::= ternary_expression(PREV_E). { E = PREV_E; }
assignment_expression(E) ::= unary_expression(L) ASSIGN assignment_expression(R). { // a = b
    AST_DEBUG("Assign expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_MULTIPLY assignment_expression(R). { // a *= b
    AST_DEBUG("Assign multiply expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_MULTIPLY, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_DIVIDE assignment_expression(R). { // a /= b
    AST_DEBUG("Assign divide expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_DIVIDE, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_REMAINDER assignment_expression(R). { // a %= b
    AST_DEBUG("Assign remainder expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_REMAINDER, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_PLUS assignment_expression(R). { // a += b
    AST_DEBUG("Assign plus expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_PLUS, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_MINUS assignment_expression(R). { // a -= b
    AST_DEBUG("Assign minus expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_MINUS, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_SHIFT_LEFT assignment_expression(R). { // a <<= b
    AST_DEBUG("Assign bitwise shift left expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_SHIFT_LEFT, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression(R). { // a >>= b
    AST_DEBUG("Assign bitwise shift right expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_SHIFT_RIGHT, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_AND assignment_expression(R). { // a &= b
    AST_DEBUG("Assign bitwise and expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_AND, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_XOR assignment_expression(R). { // a ^= b
    AST_DEBUG("Assign bitwise xor expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_XOR, L, R);
}
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_OR assignment_expression(R). { // a |= b
    AST_DEBUG("Assign bitwise or expression.");
    E = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_OR, L, R);
}

// expression
%type expression {base_node_t*}
expression(E) ::= assignment_expression(PREV_E). { E = PREV_E; }
expression(E) ::= expression(L) COMMA assignment_expression(R). {
    E = (base_node_t*)ast_newCommaExpressionNode(L, R);
}