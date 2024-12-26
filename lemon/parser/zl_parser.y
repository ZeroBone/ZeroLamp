%token_prefix T_

%token_type {Token}
%default_type {Token}

%token_destructor {
    // TODO
}

%name zl_parse

%include {
#include "token.h"
#include "ast.h"

// we will not call free with a null pointer, turn off the guard
#define YYPARSEFREENEVERNULL 1
}

// %extra_context {parser_context_t* context}

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

%type root {RootNode*}
root(R) ::= statement_list(SL). { R = new RootNode(std::move(SL)); }

%type formal_parameters {std::vector<std::string>}
formal_parameters(FPS) ::= ID(NAME). { std::vector<std::string> v; v.push_back(NAME); FPS = std::move(v); }
formal_parameters(FPS_NEW) ::= formal_parameters(FPS) COMMA ID(NAME). { FPS_NEW = std::move(FPS); FPSN.push_back(NAME); }

%type actual_parameter {ActualParameterNode*}
actual_parameter(AP) ::= expression(VALUE). { AP = ActualParameterNode(VALUE); }
actual_parameter(AP) ::= ID(KEY) EQUALS expression(VALUE). { AP = ActualParameterNode(KEY, VALUE); }

%type actual_parameters {std::vector<ActualParameterNode*>}
actual_parameters(APS) ::= actual_parameter(AP). { std::vector<ActualParameterNode*> v; APS = std::move(v); APS.push_back(AP); }
actual_parameters(APS_NEW) ::= actual_parameters(APS) COMMA actual_parameter(AP). { APS.push_back(AP); APS_NEW = std::move(APS);  }

%type statement_list {std::vector<StatementNode*>}
statement_list(SL) ::= . { std::vector<StatementNode*> v; SL = std::move(v); }
statement_list(SL_NEW) ::= statement_list(SL) statement(S). { SL.push_back(S); SL_NEW = std::move(SL); }

// statements
%type statement {StatementNode*}

// function statement
statement(S) ::= FN ID LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = new FunctionDefinitionNode(SL); }
statement(S) ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = new FunctionDefinitionNode(SL); }
statement(S) ::= FN ID LEFT_PARENTHESIS formal_parameters(FP) RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = new FunctionDefinitionNode(FP, SL); }

// event handler statement
statement(S) ::= ON ID LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = new EventHandlerDefinitionNode(SL); }
statement(S) ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = new EventHandlerDefinitionNode(SL); }
statement(S) ::= ON ID LEFT_PARENTHESIS actual_parameters(AP) RIGHT_PARENTHESIS LEFT_BRACE statement_list(SL) RIGHT_BRACE. { S = EventHandlerDefinitionNode(AP, SL); }

// function call
statement(S) ::= ID(FUNCTION_NAME) LEFT_PARENTHESIS RIGHT_PARENTHESIS. { S = new FunctionCallStatementNode(FUNCTION_NAME); }
statement(S) ::= ID(FUNCTION_NAME) LEFT_PARENTHESIS actual_parameters(APS) RIGHT_PARENTHESIS. { S = new FunctionCallStatementNode(FUNCTION_NAME, APS); }

// push statement
statement(S) ::= ID(DISPLAY) ID(MODE) SEMICOLON. { S = new PushStatementNode(DISPLAY, MODE); }
statement(S) ::= ID(DISPLAY) ID(MODE) SEMICOLON IF expression(CONDITION). { S = new PushStatementNode(DISPLAY, MODE, CONDITION); }

// expressions
%type simple_expression {ExpressionNode*}
simple_expression(E) ::= ID(T). { E = new IdExpressionNode(T.payload.string); }
simple_expression(E) ::= INT_V(T). { E = new IntLiteralExpressionNode(T.payload.TODO); }
simple_expression(E) ::= FLOAT_V(T). { E = new FloatLiteralExpressionNode(T.payload.TODO); }
simple_expression(E) ::= STRING_V(T). { E = new StringLiteralExpressionNode(T.payload.TODO); }
simple_expression(E) ::= TRUE. { E = new BooleanLiteralExpressionNode(true); }
simple_expression(E) ::= FALSE. { E = new BooleanLiteralExpressionNode(false); }
simple_expression(E) ::= LEFT_PARENTHESIS expression(E_INNER) RIGHT_PARENTHESIS. { E = E_INNER; }

// postfix expressions
%type postfix_expression {ExpressionNode*}
postfix_expression(E) ::= simple_expression(E_INNER). { E = E_INNER; }
postfix_expression(E) ::= postfix_expression(BASE) LEFT_BRACKET expression(INDEX) RIGHT_BRACKET. { E = new IndexingExpressionNode(BASE, INDEX); }
postfix_expression(E) ::= postfix_expression(BASE) LEFT_PARENTHESIS RIGHT_PARENTHESIS. { E = new FunctionCallExpressionNode(BASE); }
postfix_expression(E) ::= postfix_expression(BASE) LEFT_PARENTHESIS actual_parameters(A_PARAMS) RIGHT_PARENTHESIS. { E = new FunctionCallExpressionNode(BASE, A_PARAMS); }
postfix_expression(E) ::= postfix_expression(BASE) DOT ID(MEMBER). { E = new MemberAccessExpressionNode(BASE, MEMBER); }

// pow expression (right-accociative)
%type pow_expression {ExpressionNode*}
pow_expression(E) ::= postfix_expression(E_INNER). { E = E_INNER; }
// a ** b // right-associative => right recursion, this is not good
pow_expression(E) ::= postfix_expression(BASE) POW pow_expression(EXPONENT). { E = new PowExpressionNode(BASE, EXPONENT); }

// unary expressions
%type unary_expression {ExpressionNode*}
unary_expression(E) ::= pow_expression(E_INNER). { E = E_INNER; }
unary_expression(E) ::= MINUS unary_expression(BASE). { E = new UnaryExpressionNode(UnaryExpressionType::NEGATION, BASE); }
unary_expression(E) ::= BITWISE_INVERT unary_expression(BASE). { E = new UnaryExpressionNode(UnaryExpressionType::BITWISE_INVERT, BASE); }
unary_expression(E) ::= INVERT unary_expression(BASE). { E = new UnaryExpressionNode(UnaryExpressionType::INVERT, BASE); }

// multiplicative expression
%type multiplicative_expression {ExpressionNode*}
multiplicative_expression(E) ::= unary_expression(E_INNER). { E = E_INNER; }
multiplicative_expression(E) ::= multiplicative_expression(L) MULTIPLY unary_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::MULTIPLICATION, L, R); }
multiplicative_expression(E) ::= multiplicative_expression(L) DIVIDE unary_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::DIVISION, L, R); }
multiplicative_expression(E) ::= multiplicative_expression(L) REMAINDER unary_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::REMAINDER, L, R); }

// additive expression
%type additive_expression {ExpressionNode*}
additive_expression(E) ::= multiplicative_expression(E_INNER). { E = E_INNER; }
additive_expression(E) ::= additive_expression(L) PLUS multiplicative_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ADDITION, L, R); }
additive_expression(E) ::= additive_expression(L) MINUS multiplicative_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::SUBTRACTION, L, R); }

// bitwise shift expression
%type bitwise_shift_expression {ExpressionNode*}
bitwise_shift_expression(E) ::= additive_expression(E_INNER). { E = E_INNER; }
bitwise_shift_expression(E) ::= bitwise_shift_expression(L) BITWISE_SHIFT_LEFT additive_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_LEFT, L, R); }
bitwise_shift_expression(E) ::= bitwise_shift_expression(L) BITWISE_SHIFT_RIGHT additive_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_RIGHT, L, R); }

// comparison expression
%type comparison_expression {ExpressionNode*}
comparison_expression(E) ::= bitwise_shift_expression(E_INNER). { E = E_INNER; }
comparison_expression(E) ::= comparison_expression(L) LESS_THAN bitwise_shift_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN, L, R); }
comparison_expression(E) ::= comparison_expression(L) GREATER_THAN bitwise_shift_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN, L, R); }
comparison_expression(E) ::= comparison_expression(L) LESS_THAN_OR_EQUALS bitwise_shift_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN_OR_EQUAL, L, R); }
comparison_expression(E) ::= comparison_expression(L) GREATER_THAN_OR_EQUALS bitwise_shift_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN_OR_EQUAL, L, R); }

// equality expression
%type equality_expression {ExpressionNode*}
equality_expression(E) ::= comparison_expression(E_INNER). { E = E_INNER; }
equality_expression(E) ::= equality_expression(L) EQUALS comparison_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::EQUAL, L, R); }
equality_expression(E) ::= equality_expression(L) NOT_EQUALS comparison_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::NOT_EQUAL, L, R); }

// bitwise and expression
%type bitwise_and_expression {ExpressionNode*}
bitwise_and_expression(E) ::= equality_expression(E_INNER). { E = E_INNER; }
bitwise_and_expression(E) ::= bitwise_and_expression(L) BITWISE_AND equality_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::BITWISE_AND, L, R); }

// bitwise xor expression
%type bitwise_xor_expression {ExpressionNode*}
bitwise_xor_expression(E) ::= bitwise_and_expression(E_INNER). { E = E_INNER; }
bitwise_xor_expression(E) ::= bitwise_xor_expression(L) BITWISE_XOR bitwise_and_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::BITWISE_XOR, L, R); }

// bitwise or expression
%type bitwise_or_expression {ExpressionNode*}
bitwise_or_expression(E) ::= bitwise_xor_expression(E_INNER). { E = E_INNER; }
bitwise_or_expression(E) ::= bitwise_or_expression(L) BITWISE_OR bitwise_xor_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::BITWISE_OR, L, R); }

// and expression (logical)
%type and_expression {ExpressionNode*}
and_expression(E) ::= bitwise_or_expression(E_INNER). { E = E_INNER; }
and_expression(E) ::= and_expression(L) AND bitwise_or_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::AND, L, R); }

// or expression (logical)
%type or_expression {ExpressionNode*}
or_expression(E) ::= and_expression(E_INNER). { E = E_INNER; }
or_expression(E) ::= or_expression(L) OR and_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::OR, L, R); }

// ternary expression (right associative)
%type ternary_expression {ExpressionNode*}
ternary_expression(E) ::= or_expression(E_INNER). { E = E_INNER; }
ternary_expression(E) ::= or_expression(COND) QUESTION_MARK expression(IF) COLON ternary_expression(ELSE). { E = new TernaryExpressionNode(COND, IF, ELSE); }

// assignment expression
%type assignment_expression {ExpressionNode*}
assignment_expression(E) ::= ternary_expression(E_INNER). { E = E_INNER; }
assignment_expression(E) ::= unary_expression(L) ASSIGN assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_MULTIPLY assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MULTIPLY, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_DIVIDE assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_DIVIDE, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_REMAINDER assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_REMAINDER, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_PLUS assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_PLUS, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_MINUS assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MINUS, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_SHIFT_LEFT assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_LEFT, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_RIGHT, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_AND assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_AND, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_XOR assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_XOR, L, R); }
assignment_expression(E) ::= unary_expression(L) ASSIGN_BITWISE_OR assignment_expression(R). { E = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_OR, L, R); }

// expression
%type expression {ExpressionNode*}
expression(E) ::= assignment_expression(E_INNER). { E = E_INNER; }
expression(E) ::= expression(L) COMMA assignment_expression(R). { E = new CommaExpressionNode(L, R); }