/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 12 "zl_parser.y"

#include "token.h"

// we will not call free with a null pointer, turn off the guard
#define YYPARSEFREENEVERNULL 1
#line 34 "zl_parser.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    zl_parseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is zl_parseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    zl_parseARG_SDECL     A static variable declaration for the %extra_argument
**    zl_parseARG_PDECL     A parameter declaration for the %extra_argument
**    zl_parseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    zl_parseARG_STORE     Code to store %extra_argument into yypParser
**    zl_parseARG_FETCH     Code to extract %extra_argument from yypParser
**    zl_parseCTX_*         As zl_parseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 78
#define YYACTIONTYPE unsigned short int
#define zl_parseTOKENTYPE Token
typedef union {
  int yyinit;
  zl_parseTOKENTYPE yy0;
  DefinitionNode* yy18;
  ActualParameterNode* yy32;
  StatementNode* yy94;
  std::vector<DefinitionNode*> yy114;
  std::vector<ActualParameterNode*> yy120;
  ExpressionNode* yy133;
  std::vector<std::string> yy143;
  std::vector<StatementNode*> yy154;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define zl_parseARG_SDECL
#define zl_parseARG_PDECL
#define zl_parseARG_PARAM
#define zl_parseARG_FETCH
#define zl_parseARG_STORE
#define zl_parseCTX_SDECL parser_context_t* context;
#define zl_parseCTX_PDECL ,parser_context_t* context
#define zl_parseCTX_PARAM ,context
#define zl_parseCTX_FETCH parser_context_t* context=yypParser->context;
#define zl_parseCTX_STORE yypParser->context=context;
#define YYNSTATE             110
#define YYNRULE              83
#define YYNTOKEN             53
#define YY_MAX_SHIFT         109
#define YY_MIN_SHIFTREDUCE   160
#define YY_MAX_SHIFTREDUCE   242
#define YY_ERROR_ACTION      243
#define YY_ACCEPT_ACTION     244
#define YY_NO_ACTION         245
#define YY_MIN_REDUCE        246
#define YY_MAX_REDUCE        328
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (670)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    67,  258,  108,  247,  273,   63,  280,   59,   66,   83,
 /*    10 */    82,   62,   75,  107,  106,  104,  102,   73,  314,  326,
 /*    20 */    71,  258,  108,   69,  273,   63,  280,   59,   66,   83,
 /*    30 */    82,   62,   75,  107,  106,  104,  102,   73,  314,  326,
 /*    40 */    70,  258,  108,   46,  273,   63,  280,   59,   66,   83,
 /*    50 */    82,   62,   75,  107,  106,  104,  102,   73,  314,  326,
 /*    60 */   259,  108,   47,  273,   63,  280,   59,   66,   83,   82,
 /*    70 */    62,   75,  107,  106,  104,  102,   73,  314,  326,   94,
 /*    80 */    48,  273,   63,  280,   59,   66,   83,   82,   62,   75,
 /*    90 */   107,  106,  104,  102,   73,  314,  326,   98,   49,  273,
 /*   100 */    63,  280,   59,   66,   83,   82,   62,   75,  107,  106,
 /*   110 */   104,  102,   73,  314,  326,   72,   50,  273,   63,  280,
 /*   120 */    59,   66,   83,   82,   62,   75,  107,  106,  104,  102,
 /*   130 */    73,  314,  326,   84,   52,  273,   63,  280,   59,   66,
 /*   140 */    83,   82,   62,   75,  107,  106,  104,  102,   73,  314,
 /*   150 */   326,   85,   53,  273,   63,  280,   59,   66,   83,   82,
 /*   160 */    62,   75,  107,  106,  104,  102,   73,  314,  326,  273,
 /*   170 */    63,  280,   59,   66,   83,   82,   62,   75,  107,  106,
 /*   180 */   104,  102,   73,  314,  325,  273,   63,  280,   59,   66,
 /*   190 */    83,   82,   62,   75,  107,  106,  104,  102,   73,  314,
 /*   200 */   324,  273,   63,  280,   59,   66,   83,   82,   62,   75,
 /*   210 */   107,  106,  104,  102,   73,  314,  323,  273,   63,  280,
 /*   220 */    59,   66,   83,   82,   62,   75,  107,  106,  104,  102,
 /*   230 */    73,  314,  322,  273,   63,  280,   59,   66,   83,   82,
 /*   240 */    62,   75,  107,  106,  104,  102,   73,  314,  321,  273,
 /*   250 */    63,  280,   59,   66,   83,   82,   62,   75,  107,  106,
 /*   260 */   104,  102,   73,  314,  320,  273,   63,  280,   59,   66,
 /*   270 */    83,   82,   62,   75,  107,  106,  104,  102,   73,  314,
 /*   280 */   319,  273,   63,  280,   59,   66,   83,   82,   62,   75,
 /*   290 */   107,  106,  104,  102,   73,  314,  318,  273,   63,  280,
 /*   300 */    59,   66,   83,   82,   62,   75,  107,  106,  104,  102,
 /*   310 */    73,  314,  317,  273,   63,  280,   59,   66,   83,   82,
 /*   320 */    62,   75,  107,  106,  104,  102,   73,  314,  316,  273,
 /*   330 */    63,  280,   59,   66,   83,   82,   62,   75,  107,  106,
 /*   340 */   104,  102,   73,  314,  315,  273,   63,  280,   59,   66,
 /*   350 */    83,   82,   62,   75,  107,  106,  104,  102,   73,  314,
 /*   360 */   327,  273,   63,  280,  284,   66,   83,   82,   62,   75,
 /*   370 */   107,  106,  104,  102,   73,  313,  273,   63,  280,  284,
 /*   380 */    66,   83,   82,   62,   75,  107,  106,  104,  100,  273,
 /*   390 */    63,  280,  284,   66,   83,   82,   62,   75,  107,  106,
 /*   400 */   101,   99,  244,   45,    9,   89,  273,   63,  280,  284,
 /*   410 */    64,  181,  182,  183,  184,  185,  273,   63,  280,  287,
 /*   420 */    43,   42,   41,   99,   23,    7,    9,  189,  273,   63,
 /*   430 */   280,  284,   65,  181,  182,  183,  184,  185,  273,   63,
 /*   440 */   280,  286,   43,   42,   41,   99,   35,   34,    9,  176,
 /*   450 */   273,   63,  280,  285,  261,  181,  182,  183,  184,  185,
 /*   460 */   273,   63,  280,  283,   43,   42,   41,  273,   63,  280,
 /*   470 */   284,   66,   83,   82,   62,   75,  107,  103,   20,   19,
 /*   480 */    18,   17,   16,   15,   14,   13,   12,   11,   10,   99,
 /*   490 */   328,  109,    9,  273,   63,  280,  282,   90,   54,  181,
 /*   500 */   182,  183,  184,  185,  180,   68,  169,    9,   43,   42,
 /*   510 */    41,  273,   63,  279,  181,  182,  183,  184,  185,  273,
 /*   520 */    63,  280,  281,   43,   42,   41,   56,  273,   63,  280,
 /*   530 */   284,   66,   83,   82,   62,   75,  105,  273,   63,  280,
 /*   540 */   284,   66,   83,   82,   62,   74,  273,   63,  280,  284,
 /*   550 */    66,   83,   82,   60,   57,  273,   63,  280,  284,   66,
 /*   560 */    83,   82,   61,  273,   63,  280,  284,   66,   83,   76,
 /*   570 */   273,   63,  280,  284,   66,   83,   77,  273,   63,  280,
 /*   580 */   284,   66,   83,   78,   21,   21,  273,   63,  280,  284,
 /*   590 */    66,   83,   79,  180,  188,   21,    9,  273,   63,  280,
 /*   600 */   284,   66,   80,  181,  182,  183,  184,  185,  273,   63,
 /*   610 */   280,  284,   66,   81,   33,   32,   31,   30,    2,    5,
 /*   620 */    95,   40,   39,   38,   86,   86,  167,  166,   22,   86,
 /*   630 */     8,  165,   97,   44,   86,   86,  164,  163,  168,   86,
 /*   640 */    29,  162,   93,   55,   88,    1,    4,   36,   92,  177,
 /*   650 */    91,    4,  190,   37,    4,  186,   96,   21,   58,    3,
 /*   660 */    51,  191,    6,   24,   26,   28,   25,   87,  245,   27,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    58,   59,   60,   55,   62,   63,   64,   65,   66,   67,
 /*    10 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*    20 */    58,   59,   60,   57,   62,   63,   64,   65,   66,   67,
 /*    30 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*    40 */    58,   59,   60,   56,   62,   63,   64,   65,   66,   67,
 /*    50 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*    60 */    59,   60,   56,   62,   63,   64,   65,   66,   67,   68,
 /*    70 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   60,
 /*    80 */    56,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*    90 */    71,   72,   73,   74,   75,   76,   77,   60,   56,   62,
 /*   100 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   110 */    73,   74,   75,   76,   77,   60,   56,   62,   63,   64,
 /*   120 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   130 */    75,   76,   77,   60,   56,   62,   63,   64,   65,   66,
 /*   140 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   150 */    77,   60,    3,   62,   63,   64,   65,   66,   67,   68,
 /*   160 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   62,
 /*   170 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   180 */    73,   74,   75,   76,   77,   62,   63,   64,   65,   66,
 /*   190 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   200 */    77,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*   210 */    71,   72,   73,   74,   75,   76,   77,   62,   63,   64,
 /*   220 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   230 */    75,   76,   77,   62,   63,   64,   65,   66,   67,   68,
 /*   240 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   62,
 /*   250 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   260 */    73,   74,   75,   76,   77,   62,   63,   64,   65,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*   290 */    71,   72,   73,   74,   75,   76,   77,   62,   63,   64,
 /*   300 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   310 */    75,   76,   77,   62,   63,   64,   65,   66,   67,   68,
 /*   320 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   62,
 /*   330 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   340 */    73,   74,   75,   76,   77,   62,   63,   64,   65,   66,
 /*   350 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   360 */    77,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*   370 */    71,   72,   73,   74,   75,   76,   62,   63,   64,   65,
 /*   380 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   62,
 /*   390 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   400 */    73,    2,   53,   54,    5,    6,   62,   63,   64,   65,
 /*   410 */    66,   12,   13,   14,   15,   16,   62,   63,   64,   65,
 /*   420 */    21,   22,   23,    2,   39,   40,    5,    6,   62,   63,
 /*   430 */    64,   65,   66,   12,   13,   14,   15,   16,   62,   63,
 /*   440 */    64,   65,   21,   22,   23,    2,   28,   29,    5,    6,
 /*   450 */    62,   63,   64,   65,   61,   12,   13,   14,   15,   16,
 /*   460 */    62,   63,   64,   65,   21,   22,   23,   62,   63,   64,
 /*   470 */    65,   66,   67,   68,   69,   70,   71,   72,   42,   43,
 /*   480 */    44,   45,   46,   47,   48,   49,   50,   51,   52,    2,
 /*   490 */     0,    1,    5,   62,   63,   64,   65,    7,    3,   12,
 /*   500 */    13,   14,   15,   16,    2,    2,    2,    5,   21,   22,
 /*   510 */    23,   62,   63,   64,   12,   13,   14,   15,   16,   62,
 /*   520 */    63,   64,   65,   21,   22,   23,    3,   62,   63,   64,
 /*   530 */    65,   66,   67,   68,   69,   70,   71,   62,   63,   64,
 /*   540 */    65,   66,   67,   68,   69,   70,   62,   63,   64,   65,
 /*   550 */    66,   67,   68,   69,    3,   62,   63,   64,   65,   66,
 /*   560 */    67,   68,   69,   62,   63,   64,   65,   66,   67,   68,
 /*   570 */    62,   63,   64,   65,   66,   67,   68,   62,   63,   64,
 /*   580 */    65,   66,   67,   68,    8,    8,   62,   63,   64,   65,
 /*   590 */    66,   67,   68,    2,   18,    8,    5,   62,   63,   64,
 /*   600 */    65,   66,   67,   12,   13,   14,   15,   16,   62,   63,
 /*   610 */    64,   65,   66,   67,   30,   31,   32,   33,    5,   11,
 /*   620 */    10,   24,   25,   26,    2,    2,    4,    4,   41,    2,
 /*   630 */    17,    4,   19,   20,    2,    2,    4,    4,    2,    2,
 /*   640 */     9,    4,    6,    3,    6,    5,    8,   21,    6,    6,
 /*   650 */     8,    8,    6,   27,    8,    6,    2,    8,    3,    5,
 /*   660 */     5,    2,    9,   38,   36,   34,   37,    2,   78,   35,
 /*   670 */    78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*   680 */    78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*   690 */    78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*   700 */    78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*   710 */    78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*   720 */    78,   78,   78,
};
#define YY_SHIFT_COUNT    (109)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (665)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   670,  399,  421,  443,  487,  502,  502,  502,  502,  502,
 /*    10 */   502,  502,  502,  502,  502,  502,  502,  502,  502,  502,
 /*    20 */   502,  502,  502,  502,  502,  502,  502,  502,  502,  502,
 /*    30 */   502,  502,  502,  502,  502,  502,  502,  502,  502,  502,
 /*    40 */   502,  502,  502,  502,  591,  490,  622,  623,  627,  632,
 /*    50 */   633,  636,  637,  670,  670,  670,  670,  670,  670,  436,
 /*    60 */   584,  584,  584,  613,  597,  597,  597,  638,  640,  642,
 /*    70 */   643,  646,  587,  385,  631,  631,  418,  418,  418,  418,
 /*    80 */   626,  626,  418,  626,  576,  649,  654,  655,  149,  495,
 /*    90 */   503,  504,  523,  551,  577,  608,  610,  659,  577,  653,
 /*   100 */   625,  629,  625,  628,  629,  634,  628,  634,  577,  665,
};
#define YY_REDUCE_COUNT (58)
#define YY_REDUCE_MIN   (-58)
#define YY_REDUCE_MAX   (546)
static const short yy_reduce_ofst[] = {
 /*     0 */   349,  -58,  -38,  -18,    1,   19,   37,   55,   73,   91,
 /*    10 */   107,  123,  139,  155,  171,  187,  203,  219,  235,  251,
 /*    20 */   267,  283,  299,  314,  327,  405,  465,  475,  484,  493,
 /*    30 */   501,  508,  515,  524,  535,  546,  344,  366,  354,  376,
 /*    40 */   388,  398,  431,  457,  449,  -52,  393,  393,  393,  393,
 /*    50 */   393,  -34,  393,  -13,    6,   24,   42,   60,   78,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   246,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    10 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    20 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    30 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    40 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    50 */   243,  243,  243,  260,  260,  260,  260,  260,  260,  284,
 /*    60 */   301,  300,  299,  278,  290,  289,  288,  243,  243,  243,
 /*    70 */   243,  243,  243,  312,  303,  302,  298,  297,  296,  295,
 /*    80 */   293,  292,  294,  291,  243,  243,  243,  243,  243,  243,
 /*    90 */   243,  243,  243,  243,  265,  264,  243,  243,  257,  266,
 /*   100 */   311,  309,  310,  307,  308,  305,  306,  304,  256,  243,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  zl_parseARG_SDECL                /* A place to hold %extra_argument */
  zl_parseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void zl_parseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "FN",
  /*    2 */ "ID",
  /*    3 */ "LEFT_BRACE",
  /*    4 */ "RIGHT_BRACE",
  /*    5 */ "LEFT_PARENTHESIS",
  /*    6 */ "RIGHT_PARENTHESIS",
  /*    7 */ "ON",
  /*    8 */ "COMMA",
  /*    9 */ "EQUALS",
  /*   10 */ "SEMICOLON",
  /*   11 */ "IF",
  /*   12 */ "INT_V",
  /*   13 */ "FLOAT_V",
  /*   14 */ "STRING_V",
  /*   15 */ "TRUE",
  /*   16 */ "FALSE",
  /*   17 */ "LEFT_BRACKET",
  /*   18 */ "RIGHT_BRACKET",
  /*   19 */ "DOT",
  /*   20 */ "POW",
  /*   21 */ "MINUS",
  /*   22 */ "BITWISE_INVERT",
  /*   23 */ "INVERT",
  /*   24 */ "MULTIPLY",
  /*   25 */ "DIVIDE",
  /*   26 */ "REMAINDER",
  /*   27 */ "PLUS",
  /*   28 */ "BITWISE_SHIFT_LEFT",
  /*   29 */ "BITWISE_SHIFT_RIGHT",
  /*   30 */ "LESS_THAN",
  /*   31 */ "GREATER_THAN",
  /*   32 */ "LESS_THAN_OR_EQUALS",
  /*   33 */ "GREATER_THAN_OR_EQUALS",
  /*   34 */ "NOT_EQUALS",
  /*   35 */ "BITWISE_AND",
  /*   36 */ "BITWISE_XOR",
  /*   37 */ "BITWISE_OR",
  /*   38 */ "AND",
  /*   39 */ "OR",
  /*   40 */ "QUESTION_MARK",
  /*   41 */ "COLON",
  /*   42 */ "ASSIGN",
  /*   43 */ "ASSIGN_MULTIPLY",
  /*   44 */ "ASSIGN_DIVIDE",
  /*   45 */ "ASSIGN_REMAINDER",
  /*   46 */ "ASSIGN_PLUS",
  /*   47 */ "ASSIGN_MINUS",
  /*   48 */ "ASSIGN_BITWISE_SHIFT_LEFT",
  /*   49 */ "ASSIGN_BITWISE_SHIFT_RIGHT",
  /*   50 */ "ASSIGN_BITWISE_AND",
  /*   51 */ "ASSIGN_BITWISE_XOR",
  /*   52 */ "ASSIGN_BITWISE_OR",
  /*   53 */ "root",
  /*   54 */ "definition_list",
  /*   55 */ "definition",
  /*   56 */ "statement_list",
  /*   57 */ "formal_parameters",
  /*   58 */ "actual_parameters",
  /*   59 */ "actual_parameter",
  /*   60 */ "expression",
  /*   61 */ "statement",
  /*   62 */ "simple_expression",
  /*   63 */ "postfix_expression",
  /*   64 */ "pow_expression",
  /*   65 */ "unary_expression",
  /*   66 */ "multiplicative_expression",
  /*   67 */ "additive_expression",
  /*   68 */ "bitwise_shift_expression",
  /*   69 */ "comparison_expression",
  /*   70 */ "equality_expression",
  /*   71 */ "bitwise_and_expression",
  /*   72 */ "bitwise_xor_expression",
  /*   73 */ "bitwise_or_expression",
  /*   74 */ "and_expression",
  /*   75 */ "or_expression",
  /*   76 */ "ternary_expression",
  /*   77 */ "assignment_expression",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "definition_list ::=",
 /*   1 */ "definition_list ::= definition_list definition",
 /*   2 */ "definition ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE",
 /*   3 */ "definition ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*   4 */ "definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*   5 */ "definition ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE",
 /*   6 */ "definition ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*   7 */ "definition ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*   8 */ "formal_parameters ::= ID",
 /*   9 */ "formal_parameters ::= formal_parameters COMMA ID",
 /*  10 */ "actual_parameter ::= expression",
 /*  11 */ "actual_parameter ::= ID EQUALS expression",
 /*  12 */ "actual_parameters ::= actual_parameter",
 /*  13 */ "actual_parameters ::= actual_parameters COMMA actual_parameter",
 /*  14 */ "statement_list ::=",
 /*  15 */ "statement_list ::= statement_list statement",
 /*  16 */ "statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  17 */ "statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  18 */ "statement ::= ID ID SEMICOLON",
 /*  19 */ "statement ::= ID ID SEMICOLON IF expression",
 /*  20 */ "simple_expression ::= ID",
 /*  21 */ "simple_expression ::= INT_V",
 /*  22 */ "simple_expression ::= FLOAT_V",
 /*  23 */ "simple_expression ::= STRING_V",
 /*  24 */ "simple_expression ::= TRUE",
 /*  25 */ "simple_expression ::= FALSE",
 /*  26 */ "simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS",
 /*  27 */ "postfix_expression ::= simple_expression",
 /*  28 */ "postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET",
 /*  29 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  30 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  31 */ "postfix_expression ::= postfix_expression DOT ID",
 /*  32 */ "pow_expression ::= postfix_expression",
 /*  33 */ "pow_expression ::= postfix_expression POW pow_expression",
 /*  34 */ "unary_expression ::= pow_expression",
 /*  35 */ "unary_expression ::= MINUS unary_expression",
 /*  36 */ "unary_expression ::= BITWISE_INVERT unary_expression",
 /*  37 */ "unary_expression ::= INVERT unary_expression",
 /*  38 */ "multiplicative_expression ::= unary_expression",
 /*  39 */ "multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression",
 /*  40 */ "multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression",
 /*  41 */ "multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression",
 /*  42 */ "additive_expression ::= multiplicative_expression",
 /*  43 */ "additive_expression ::= additive_expression PLUS multiplicative_expression",
 /*  44 */ "additive_expression ::= additive_expression MINUS multiplicative_expression",
 /*  45 */ "bitwise_shift_expression ::= additive_expression",
 /*  46 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression",
 /*  47 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression",
 /*  48 */ "comparison_expression ::= bitwise_shift_expression",
 /*  49 */ "comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression",
 /*  50 */ "comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression",
 /*  51 */ "comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression",
 /*  52 */ "comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression",
 /*  53 */ "equality_expression ::= comparison_expression",
 /*  54 */ "equality_expression ::= equality_expression EQUALS comparison_expression",
 /*  55 */ "equality_expression ::= equality_expression NOT_EQUALS comparison_expression",
 /*  56 */ "bitwise_and_expression ::= equality_expression",
 /*  57 */ "bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression",
 /*  58 */ "bitwise_xor_expression ::= bitwise_and_expression",
 /*  59 */ "bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression",
 /*  60 */ "bitwise_or_expression ::= bitwise_xor_expression",
 /*  61 */ "bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression",
 /*  62 */ "and_expression ::= bitwise_or_expression",
 /*  63 */ "and_expression ::= and_expression AND bitwise_or_expression",
 /*  64 */ "or_expression ::= and_expression",
 /*  65 */ "or_expression ::= or_expression OR and_expression",
 /*  66 */ "ternary_expression ::= or_expression",
 /*  67 */ "ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression",
 /*  68 */ "assignment_expression ::= ternary_expression",
 /*  69 */ "assignment_expression ::= unary_expression ASSIGN assignment_expression",
 /*  70 */ "assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression",
 /*  71 */ "assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression",
 /*  72 */ "assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression",
 /*  73 */ "assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression",
 /*  74 */ "assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression",
 /*  75 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression",
 /*  76 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression",
 /*  77 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression",
 /*  78 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression",
 /*  79 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression",
 /*  80 */ "expression ::= assignment_expression",
 /*  81 */ "expression ::= expression COMMA assignment_expression",
 /*  82 */ "root ::= definition_list",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to zl_parseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void zl_parseInit(void *yypRawParser zl_parseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  zl_parseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef zl_parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to zl_parse and zl_parseFree.
*/
void *zl_parseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) zl_parseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    zl_parseCTX_STORE
    zl_parseInit(yypParser zl_parseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* zl_parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  zl_parseARG_FETCH
  zl_parseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* TERMINAL Destructor */
    case 1: /* FN */
    case 2: /* ID */
    case 3: /* LEFT_BRACE */
    case 4: /* RIGHT_BRACE */
    case 5: /* LEFT_PARENTHESIS */
    case 6: /* RIGHT_PARENTHESIS */
    case 7: /* ON */
    case 8: /* COMMA */
    case 9: /* EQUALS */
    case 10: /* SEMICOLON */
    case 11: /* IF */
    case 12: /* INT_V */
    case 13: /* FLOAT_V */
    case 14: /* STRING_V */
    case 15: /* TRUE */
    case 16: /* FALSE */
    case 17: /* LEFT_BRACKET */
    case 18: /* RIGHT_BRACKET */
    case 19: /* DOT */
    case 20: /* POW */
    case 21: /* MINUS */
    case 22: /* BITWISE_INVERT */
    case 23: /* INVERT */
    case 24: /* MULTIPLY */
    case 25: /* DIVIDE */
    case 26: /* REMAINDER */
    case 27: /* PLUS */
    case 28: /* BITWISE_SHIFT_LEFT */
    case 29: /* BITWISE_SHIFT_RIGHT */
    case 30: /* LESS_THAN */
    case 31: /* GREATER_THAN */
    case 32: /* LESS_THAN_OR_EQUALS */
    case 33: /* GREATER_THAN_OR_EQUALS */
    case 34: /* NOT_EQUALS */
    case 35: /* BITWISE_AND */
    case 36: /* BITWISE_XOR */
    case 37: /* BITWISE_OR */
    case 38: /* AND */
    case 39: /* OR */
    case 40: /* QUESTION_MARK */
    case 41: /* COLON */
    case 42: /* ASSIGN */
    case 43: /* ASSIGN_MULTIPLY */
    case 44: /* ASSIGN_DIVIDE */
    case 45: /* ASSIGN_REMAINDER */
    case 46: /* ASSIGN_PLUS */
    case 47: /* ASSIGN_MINUS */
    case 48: /* ASSIGN_BITWISE_SHIFT_LEFT */
    case 49: /* ASSIGN_BITWISE_SHIFT_RIGHT */
    case 50: /* ASSIGN_BITWISE_AND */
    case 51: /* ASSIGN_BITWISE_XOR */
    case 52: /* ASSIGN_BITWISE_OR */
{
#line 6 "zl_parser.y"

    // TODO

#line 843 "zl_parser.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 53: /* root */
    case 54: /* definition_list */
    case 55: /* definition */
    case 56: /* statement_list */
    case 57: /* formal_parameters */
    case 58: /* actual_parameters */
    case 59: /* actual_parameter */
    case 60: /* expression */
    case 61: /* statement */
    case 62: /* simple_expression */
    case 63: /* postfix_expression */
    case 64: /* pow_expression */
    case 65: /* unary_expression */
    case 66: /* multiplicative_expression */
    case 67: /* additive_expression */
    case 68: /* bitwise_shift_expression */
    case 69: /* comparison_expression */
    case 70: /* equality_expression */
    case 71: /* bitwise_and_expression */
    case 72: /* bitwise_xor_expression */
    case 73: /* bitwise_or_expression */
    case 74: /* and_expression */
    case 75: /* or_expression */
    case 76: /* ternary_expression */
    case 77: /* assignment_expression */
{
#line 33 "zl_parser.y"

    ast_defaultDestructor((yypminor->yy133));

#line 877 "zl_parser.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void zl_parseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef zl_parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void zl_parseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  zl_parseFinalize(p);
  (*freeProc)(p);
}
#endif /* zl_parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int zl_parseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int zl_parseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    assert( i+YYNTOKEN<=(int)sizeof(yy_lookahead)/sizeof(yy_lookahead[0]) );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   zl_parseARG_FETCH
   zl_parseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
#line 39 "zl_parser.y"

    parser_onStackOverflow(context);
#line 1101 "zl_parser.c"
/******** End %stack_overflow code ********************************************/
   zl_parseARG_STORE /* Suppress warning about unused %extra_argument var */
   zl_parseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  zl_parseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;       /* Symbol on the left-hand side of the rule */
  signed char nrhs;     /* Negative of the number of RHS symbols in the rule */
} yyRuleInfo[] = {
  {   54,    0 }, /* (0) definition_list ::= */
  {   54,   -2 }, /* (1) definition_list ::= definition_list definition */
  {   55,   -5 }, /* (2) definition ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   55,   -7 }, /* (3) definition ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   55,   -8 }, /* (4) definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   55,   -5 }, /* (5) definition ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   55,   -7 }, /* (6) definition ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   55,   -8 }, /* (7) definition ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   57,   -1 }, /* (8) formal_parameters ::= ID */
  {   57,   -3 }, /* (9) formal_parameters ::= formal_parameters COMMA ID */
  {   59,   -1 }, /* (10) actual_parameter ::= expression */
  {   59,   -3 }, /* (11) actual_parameter ::= ID EQUALS expression */
  {   58,   -1 }, /* (12) actual_parameters ::= actual_parameter */
  {   58,   -3 }, /* (13) actual_parameters ::= actual_parameters COMMA actual_parameter */
  {   56,    0 }, /* (14) statement_list ::= */
  {   56,   -2 }, /* (15) statement_list ::= statement_list statement */
  {   61,   -3 }, /* (16) statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   61,   -4 }, /* (17) statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   61,   -3 }, /* (18) statement ::= ID ID SEMICOLON */
  {   61,   -5 }, /* (19) statement ::= ID ID SEMICOLON IF expression */
  {   62,   -1 }, /* (20) simple_expression ::= ID */
  {   62,   -1 }, /* (21) simple_expression ::= INT_V */
  {   62,   -1 }, /* (22) simple_expression ::= FLOAT_V */
  {   62,   -1 }, /* (23) simple_expression ::= STRING_V */
  {   62,   -1 }, /* (24) simple_expression ::= TRUE */
  {   62,   -1 }, /* (25) simple_expression ::= FALSE */
  {   62,   -3 }, /* (26) simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
  {   63,   -1 }, /* (27) postfix_expression ::= simple_expression */
  {   63,   -4 }, /* (28) postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
  {   63,   -3 }, /* (29) postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   63,   -4 }, /* (30) postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   63,   -3 }, /* (31) postfix_expression ::= postfix_expression DOT ID */
  {   64,   -1 }, /* (32) pow_expression ::= postfix_expression */
  {   64,   -3 }, /* (33) pow_expression ::= postfix_expression POW pow_expression */
  {   65,   -1 }, /* (34) unary_expression ::= pow_expression */
  {   65,   -2 }, /* (35) unary_expression ::= MINUS unary_expression */
  {   65,   -2 }, /* (36) unary_expression ::= BITWISE_INVERT unary_expression */
  {   65,   -2 }, /* (37) unary_expression ::= INVERT unary_expression */
  {   66,   -1 }, /* (38) multiplicative_expression ::= unary_expression */
  {   66,   -3 }, /* (39) multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression */
  {   66,   -3 }, /* (40) multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression */
  {   66,   -3 }, /* (41) multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression */
  {   67,   -1 }, /* (42) additive_expression ::= multiplicative_expression */
  {   67,   -3 }, /* (43) additive_expression ::= additive_expression PLUS multiplicative_expression */
  {   67,   -3 }, /* (44) additive_expression ::= additive_expression MINUS multiplicative_expression */
  {   68,   -1 }, /* (45) bitwise_shift_expression ::= additive_expression */
  {   68,   -3 }, /* (46) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
  {   68,   -3 }, /* (47) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
  {   69,   -1 }, /* (48) comparison_expression ::= bitwise_shift_expression */
  {   69,   -3 }, /* (49) comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
  {   69,   -3 }, /* (50) comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
  {   69,   -3 }, /* (51) comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
  {   69,   -3 }, /* (52) comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
  {   70,   -1 }, /* (53) equality_expression ::= comparison_expression */
  {   70,   -3 }, /* (54) equality_expression ::= equality_expression EQUALS comparison_expression */
  {   70,   -3 }, /* (55) equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
  {   71,   -1 }, /* (56) bitwise_and_expression ::= equality_expression */
  {   71,   -3 }, /* (57) bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
  {   72,   -1 }, /* (58) bitwise_xor_expression ::= bitwise_and_expression */
  {   72,   -3 }, /* (59) bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
  {   73,   -1 }, /* (60) bitwise_or_expression ::= bitwise_xor_expression */
  {   73,   -3 }, /* (61) bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
  {   74,   -1 }, /* (62) and_expression ::= bitwise_or_expression */
  {   74,   -3 }, /* (63) and_expression ::= and_expression AND bitwise_or_expression */
  {   75,   -1 }, /* (64) or_expression ::= and_expression */
  {   75,   -3 }, /* (65) or_expression ::= or_expression OR and_expression */
  {   76,   -1 }, /* (66) ternary_expression ::= or_expression */
  {   76,   -5 }, /* (67) ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
  {   77,   -1 }, /* (68) assignment_expression ::= ternary_expression */
  {   77,   -3 }, /* (69) assignment_expression ::= unary_expression ASSIGN assignment_expression */
  {   77,   -3 }, /* (70) assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
  {   77,   -3 }, /* (71) assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
  {   77,   -3 }, /* (72) assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
  {   77,   -3 }, /* (73) assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
  {   77,   -3 }, /* (74) assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
  {   77,   -3 }, /* (75) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
  {   77,   -3 }, /* (76) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
  {   77,   -3 }, /* (77) assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
  {   77,   -3 }, /* (78) assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
  {   77,   -3 }, /* (79) assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
  {   60,   -1 }, /* (80) expression ::= assignment_expression */
  {   60,   -3 }, /* (81) expression ::= expression COMMA assignment_expression */
  {   53,   -1 }, /* (82) root ::= definition_list */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  zl_parseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  zl_parseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  zl_parseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* definition_list ::= */
#line 54 "zl_parser.y"
{}
#line 1349 "zl_parser.c"
        break;
      case 1: /* definition_list ::= definition_list definition */
#line 55 "zl_parser.y"
{ yymsp[-1].minor.yy114.push_back(yymsp[0].minor.yy18); }
#line 1354 "zl_parser.c"
        break;
      case 2: /* definition ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-4].minor);
#line 59 "zl_parser.y"
{ yymsp[-4].minor.yy18 = new FunctionDefinitionNode(yymsp[-1].minor.yy154); }
#line 1360 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 3: /* definition ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-6].minor);
#line 60 "zl_parser.y"
{ yymsp[-6].minor.yy18 = new FunctionDefinitionNode(yymsp[-1].minor.yy154); }
#line 1370 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 4: /* definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-7].minor);
#line 61 "zl_parser.y"
{ yymsp[-7].minor.yy18 = new FunctionDefinitionNode(yymsp[-4].minor.yy143, yymsp[-1].minor.yy154); }
#line 1382 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-6].minor);
  yy_destructor(yypParser,5,&yymsp[-5].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 5: /* definition ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-4].minor);
#line 64 "zl_parser.y"
{ yymsp[-4].minor.yy18 = new EventHandlerDefinitionNode(yymsp[-1].minor.yy154); }
#line 1394 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 6: /* definition ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-6].minor);
#line 65 "zl_parser.y"
{ yymsp[-6].minor.yy18 = new EventHandlerDefinitionNode(yymsp[-1].minor.yy154); }
#line 1404 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 7: /* definition ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-7].minor);
#line 66 "zl_parser.y"
{ yymsp[-7].minor.yy18 = EventHandlerDefinitionNode(yymsp[-4].minor.yy120, yymsp[-1].minor.yy154); }
#line 1416 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-6].minor);
  yy_destructor(yypParser,5,&yymsp[-5].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 8: /* formal_parameters ::= ID */
#line 69 "zl_parser.y"
{ std::vector<std::string> v; v.push_back(yymsp[0].minor.yy0); yylhsminor.yy143 = std::move(v); }
#line 1427 "zl_parser.c"
  yymsp[0].minor.yy143 = yylhsminor.yy143;
        break;
      case 9: /* formal_parameters ::= formal_parameters COMMA ID */
#line 70 "zl_parser.y"
{ yylhsminor.yy143 = std::move(yymsp[-2].minor.yy143); FPSN.push_back(yymsp[0].minor.yy0); }
#line 1433 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yymsp[-2].minor.yy143 = yylhsminor.yy143;
        break;
      case 10: /* actual_parameter ::= expression */
#line 73 "zl_parser.y"
{ yylhsminor.yy32 = ActualParameterNode(yymsp[0].minor.yy133); }
#line 1440 "zl_parser.c"
  yymsp[0].minor.yy32 = yylhsminor.yy32;
        break;
      case 11: /* actual_parameter ::= ID EQUALS expression */
#line 74 "zl_parser.y"
{ yylhsminor.yy32 = ActualParameterNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy133); }
#line 1446 "zl_parser.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yymsp[-2].minor.yy32 = yylhsminor.yy32;
        break;
      case 12: /* actual_parameters ::= actual_parameter */
#line 77 "zl_parser.y"
{ std::vector<ActualParameterNode*> v; yylhsminor.yy120 = std::move(v); yylhsminor.yy120.push_back(yymsp[0].minor.yy32); }
#line 1453 "zl_parser.c"
  yymsp[0].minor.yy120 = yylhsminor.yy120;
        break;
      case 13: /* actual_parameters ::= actual_parameters COMMA actual_parameter */
#line 78 "zl_parser.y"
{ yymsp[-2].minor.yy120.push_back(yymsp[0].minor.yy32); yylhsminor.yy120 = std::move(yymsp[-2].minor.yy120);  }
#line 1459 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yymsp[-2].minor.yy120 = yylhsminor.yy120;
        break;
      case 14: /* statement_list ::= */
#line 81 "zl_parser.y"
{ std::vector<StatementNode*> v; yymsp[1].minor.yy154 = std::move(v); }
#line 1466 "zl_parser.c"
        break;
      case 15: /* statement_list ::= statement_list statement */
#line 82 "zl_parser.y"
{ yymsp[-1].minor.yy154.push_back(yymsp[0].minor.yy94); yylhsminor.yy154 = std::move(yymsp[-1].minor.yy154); }
#line 1471 "zl_parser.c"
  yymsp[-1].minor.yy154 = yylhsminor.yy154;
        break;
      case 16: /* statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
#line 87 "zl_parser.y"
{ yylhsminor.yy94 = new FunctionCallStatementNode(yymsp[-2].minor.yy0); }
#line 1477 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-2].minor.yy94 = yylhsminor.yy94;
        break;
      case 17: /* statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
#line 88 "zl_parser.y"
{ yylhsminor.yy94 = new FunctionCallStatementNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy120); }
#line 1485 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-3].minor.yy94 = yylhsminor.yy94;
        break;
      case 18: /* statement ::= ID ID SEMICOLON */
#line 91 "zl_parser.y"
{ yylhsminor.yy94 = new PushStatementNode(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0); }
#line 1493 "zl_parser.c"
  yy_destructor(yypParser,10,&yymsp[0].minor);
  yymsp[-2].minor.yy94 = yylhsminor.yy94;
        break;
      case 19: /* statement ::= ID ID SEMICOLON IF expression */
#line 92 "zl_parser.y"
{ yylhsminor.yy94 = new PushStatementNode(yymsp[-4].minor.yy0, yymsp[-3].minor.yy0, yymsp[0].minor.yy133); }
#line 1500 "zl_parser.c"
  yy_destructor(yypParser,10,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[-1].minor);
  yymsp[-4].minor.yy94 = yylhsminor.yy94;
        break;
      case 20: /* simple_expression ::= ID */
#line 96 "zl_parser.y"
{ yylhsminor.yy133 = new IdExpressionNode(yymsp[0].minor.yy0.payload.string); }
#line 1508 "zl_parser.c"
  yymsp[0].minor.yy133 = yylhsminor.yy133;
        break;
      case 21: /* simple_expression ::= INT_V */
#line 97 "zl_parser.y"
{ yylhsminor.yy133 = new IntLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1514 "zl_parser.c"
  yymsp[0].minor.yy133 = yylhsminor.yy133;
        break;
      case 22: /* simple_expression ::= FLOAT_V */
#line 98 "zl_parser.y"
{ yylhsminor.yy133 = new FloatLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1520 "zl_parser.c"
  yymsp[0].minor.yy133 = yylhsminor.yy133;
        break;
      case 23: /* simple_expression ::= STRING_V */
#line 99 "zl_parser.y"
{ yylhsminor.yy133 = new StringLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1526 "zl_parser.c"
  yymsp[0].minor.yy133 = yylhsminor.yy133;
        break;
      case 24: /* simple_expression ::= TRUE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 100 "zl_parser.y"
{ yymsp[0].minor.yy133 = new BooleanLiteralExpressionNode(true); }
#line 1533 "zl_parser.c"
}
        break;
      case 25: /* simple_expression ::= FALSE */
{  yy_destructor(yypParser,16,&yymsp[0].minor);
#line 101 "zl_parser.y"
{ yymsp[0].minor.yy133 = new BooleanLiteralExpressionNode(false); }
#line 1540 "zl_parser.c"
}
        break;
      case 26: /* simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
{  yy_destructor(yypParser,5,&yymsp[-2].minor);
#line 102 "zl_parser.y"
{ yymsp[-2].minor.yy133 = yymsp[-1].minor.yy133; }
#line 1547 "zl_parser.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 27: /* postfix_expression ::= simple_expression */
      case 32: /* pow_expression ::= postfix_expression */ yytestcase(yyruleno==32);
      case 34: /* unary_expression ::= pow_expression */ yytestcase(yyruleno==34);
      case 38: /* multiplicative_expression ::= unary_expression */ yytestcase(yyruleno==38);
      case 42: /* additive_expression ::= multiplicative_expression */ yytestcase(yyruleno==42);
      case 45: /* bitwise_shift_expression ::= additive_expression */ yytestcase(yyruleno==45);
      case 48: /* comparison_expression ::= bitwise_shift_expression */ yytestcase(yyruleno==48);
      case 53: /* equality_expression ::= comparison_expression */ yytestcase(yyruleno==53);
      case 56: /* bitwise_and_expression ::= equality_expression */ yytestcase(yyruleno==56);
      case 58: /* bitwise_xor_expression ::= bitwise_and_expression */ yytestcase(yyruleno==58);
      case 60: /* bitwise_or_expression ::= bitwise_xor_expression */ yytestcase(yyruleno==60);
      case 62: /* and_expression ::= bitwise_or_expression */ yytestcase(yyruleno==62);
      case 64: /* or_expression ::= and_expression */ yytestcase(yyruleno==64);
      case 66: /* ternary_expression ::= or_expression */ yytestcase(yyruleno==66);
      case 68: /* assignment_expression ::= ternary_expression */ yytestcase(yyruleno==68);
      case 80: /* expression ::= assignment_expression */ yytestcase(yyruleno==80);
#line 106 "zl_parser.y"
{ yylhsminor.yy133 = yymsp[0].minor.yy133; }
#line 1569 "zl_parser.c"
  yymsp[0].minor.yy133 = yylhsminor.yy133;
        break;
      case 28: /* postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
#line 107 "zl_parser.y"
{ yylhsminor.yy133 = new IndexingExpressionNode(yymsp[-3].minor.yy133, yymsp[-1].minor.yy133); }
#line 1575 "zl_parser.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,18,&yymsp[0].minor);
  yymsp[-3].minor.yy133 = yylhsminor.yy133;
        break;
      case 29: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
#line 108 "zl_parser.y"
{ yylhsminor.yy133 = new FunctionCallExpressionNode(yymsp[-2].minor.yy133); }
#line 1583 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 30: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
#line 109 "zl_parser.y"
{ yylhsminor.yy133 = new FunctionCallExpressionNode(yymsp[-3].minor.yy133, yymsp[-1].minor.yy120); }
#line 1591 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-3].minor.yy133 = yylhsminor.yy133;
        break;
      case 31: /* postfix_expression ::= postfix_expression DOT ID */
#line 110 "zl_parser.y"
{ yylhsminor.yy133 = new MemberAccessExpressionNode(yymsp[-2].minor.yy133, yymsp[0].minor.yy0); }
#line 1599 "zl_parser.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 33: /* pow_expression ::= postfix_expression POW pow_expression */
#line 116 "zl_parser.y"
{ yylhsminor.yy133 = new PowExpressionNode(yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1606 "zl_parser.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 35: /* unary_expression ::= MINUS unary_expression */
{  yy_destructor(yypParser,21,&yymsp[-1].minor);
#line 121 "zl_parser.y"
{ yymsp[-1].minor.yy133 = new UnaryExpressionNode(UnaryExpressionType::NEGATION, yymsp[0].minor.yy133); }
#line 1614 "zl_parser.c"
}
        break;
      case 36: /* unary_expression ::= BITWISE_INVERT unary_expression */
{  yy_destructor(yypParser,22,&yymsp[-1].minor);
#line 122 "zl_parser.y"
{ yymsp[-1].minor.yy133 = new UnaryExpressionNode(UnaryExpressionType::BITWISE_INVERT, yymsp[0].minor.yy133); }
#line 1621 "zl_parser.c"
}
        break;
      case 37: /* unary_expression ::= INVERT unary_expression */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 123 "zl_parser.y"
{ yymsp[-1].minor.yy133 = new UnaryExpressionNode(UnaryExpressionType::INVERT, yymsp[0].minor.yy133); }
#line 1628 "zl_parser.c"
}
        break;
      case 39: /* multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression */
#line 128 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::MULTIPLICATION, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1634 "zl_parser.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 40: /* multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression */
#line 129 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::DIVISION, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1641 "zl_parser.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 41: /* multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression */
#line 130 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::REMAINDER, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1648 "zl_parser.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 43: /* additive_expression ::= additive_expression PLUS multiplicative_expression */
#line 135 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ADDITION, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1655 "zl_parser.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 44: /* additive_expression ::= additive_expression MINUS multiplicative_expression */
#line 136 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::SUBTRACTION, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1662 "zl_parser.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 46: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
#line 141 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1669 "zl_parser.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 47: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
#line 142 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1676 "zl_parser.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 49: /* comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
#line 147 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1683 "zl_parser.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 50: /* comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
#line 148 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1690 "zl_parser.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 51: /* comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
#line 149 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN_OR_EQUAL, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1697 "zl_parser.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 52: /* comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
#line 150 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN_OR_EQUAL, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1704 "zl_parser.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 54: /* equality_expression ::= equality_expression EQUALS comparison_expression */
#line 155 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::EQUAL, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1711 "zl_parser.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 55: /* equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
#line 156 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::NOT_EQUAL, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1718 "zl_parser.c"
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 57: /* bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
#line 161 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_AND, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1725 "zl_parser.c"
  yy_destructor(yypParser,35,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 59: /* bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
#line 166 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_XOR, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1732 "zl_parser.c"
  yy_destructor(yypParser,36,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 61: /* bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
#line 171 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_OR, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1739 "zl_parser.c"
  yy_destructor(yypParser,37,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 63: /* and_expression ::= and_expression AND bitwise_or_expression */
#line 176 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::AND, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1746 "zl_parser.c"
  yy_destructor(yypParser,38,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 65: /* or_expression ::= or_expression OR and_expression */
#line 181 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::OR, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1753 "zl_parser.c"
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 67: /* ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
#line 186 "zl_parser.y"
{ yylhsminor.yy133 = new TernaryExpressionNode(yymsp[-4].minor.yy133, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1760 "zl_parser.c"
  yy_destructor(yypParser,40,&yymsp[-3].minor);
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yymsp[-4].minor.yy133 = yylhsminor.yy133;
        break;
      case 69: /* assignment_expression ::= unary_expression ASSIGN assignment_expression */
#line 191 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1768 "zl_parser.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 70: /* assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
#line 192 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MULTIPLY, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1775 "zl_parser.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 71: /* assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
#line 193 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_DIVIDE, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1782 "zl_parser.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 72: /* assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
#line 194 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_REMAINDER, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1789 "zl_parser.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 73: /* assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
#line 195 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_PLUS, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1796 "zl_parser.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 74: /* assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
#line 196 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MINUS, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1803 "zl_parser.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 75: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
#line 197 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1810 "zl_parser.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 76: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
#line 198 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1817 "zl_parser.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 77: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
#line 199 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_AND, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1824 "zl_parser.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 78: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
#line 200 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_XOR, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1831 "zl_parser.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 79: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
#line 201 "zl_parser.y"
{ yylhsminor.yy133 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_OR, yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1838 "zl_parser.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 81: /* expression ::= expression COMMA assignment_expression */
#line 206 "zl_parser.y"
{ yylhsminor.yy133 = new CommaExpressionNode(yymsp[-2].minor.yy133, yymsp[0].minor.yy133); }
#line 1845 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yymsp[-2].minor.yy133 = yylhsminor.yy133;
        break;
      case 82: /* root ::= definition_list */
{  yy_destructor(yypParser,54,&yymsp[0].minor);
#line 51 "zl_parser.y"
{
}
#line 1854 "zl_parser.c"
}
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  zl_parseARG_FETCH
  zl_parseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 29 "zl_parser.y"

    parser_onFatalSyntaxError(context);
#line 1902 "zl_parser.c"
/************ End %parse_failure code *****************************************/
  zl_parseARG_STORE /* Suppress warning about unused %extra_argument variable */
  zl_parseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  zl_parseTOKENTYPE yyminor         /* The minor type of the error token */
){
  zl_parseARG_FETCH
  zl_parseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 21 "zl_parser.y"

    parser_onSyntaxError(context, &TOKEN);
#line 1924 "zl_parser.c"
/************ End %syntax_error code ******************************************/
  zl_parseARG_STORE /* Suppress warning about unused %extra_argument variable */
  zl_parseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  zl_parseARG_FETCH
  zl_parseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 25 "zl_parser.y"

    parser_onParsingFinished(context);
#line 1953 "zl_parser.c"
/*********** End %parse_accept code *******************************************/
  zl_parseARG_STORE /* Suppress warning about unused %extra_argument variable */
  zl_parseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "zl_parseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void zl_parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  zl_parseTOKENTYPE yyminor       /* The value for the token */
  zl_parseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  zl_parseCTX_FETCH
  zl_parseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action(yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor zl_parseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
