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
#include "ast.h"

// we will not call free with a null pointer, turn off the guard
#define YYPARSEFREENEVERNULL 1
#line 35 "zl_parser.c"
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
#define YYNOCODE 76
#define YYACTIONTYPE unsigned short int
#define zl_parseTOKENTYPE Token
typedef union {
  int yyinit;
  zl_parseTOKENTYPE yy0;
  RootNode* yy9;
  ExpressionNode* yy33;
  StatementNode* yy46;
  std::vector<StatementNode*> yy102;
  std::vector<ActualParameterNode*> yy104;
  std::vector<std::string> yy127;
  ActualParameterNode* yy128;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define zl_parseARG_SDECL
#define zl_parseARG_PDECL
#define zl_parseARG_PARAM
#define zl_parseARG_FETCH
#define zl_parseARG_STORE
#define zl_parseCTX_SDECL
#define zl_parseCTX_PDECL
#define zl_parseCTX_PARAM
#define zl_parseCTX_FETCH
#define zl_parseCTX_STORE
#define YYNSTATE             110
#define YYNRULE              81
#define YYNTOKEN             53
#define YY_MAX_SHIFT         109
#define YY_MIN_SHIFTREDUCE   159
#define YY_MAX_SHIFTREDUCE   239
#define YY_ERROR_ACTION      240
#define YY_ACCEPT_ACTION     241
#define YY_NO_ACTION         242
#define YY_MIN_REDUCE        243
#define YY_MAX_REDUCE        323
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
#define YY_ACTTAB_COUNT (695)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   248,  107,   68,   67,  269,   63,  276,   59,   66,   82,
 /*    10 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  322,
 /*    20 */   248,  107,   70,   45,  269,   63,  276,   59,   66,   82,
 /*    30 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  322,
 /*    40 */   248,  107,   69,   46,  269,   63,  276,   59,   66,   82,
 /*    50 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  322,
 /*    60 */   251,  249,  107,  241,   51,  269,   63,  276,   59,   66,
 /*    70 */    82,   81,   62,   74,  106,  105,  103,  101,   72,  310,
 /*    80 */   322,   47,   93,   21,   48,  269,   63,  276,   59,   66,
 /*    90 */    82,   81,   62,   74,  106,  105,  103,  101,   72,  310,
 /*   100 */   322,   49,   97,   23,    7,  269,   63,  276,   59,   66,
 /*   110 */    82,   81,   62,   74,  106,  105,  103,  101,   72,  310,
 /*   120 */   322,   50,   22,   71,   35,   34,  269,   63,  276,   59,
 /*   130 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   140 */   310,  322,   57,   83,    1,  161,  269,   63,  276,   59,
 /*   150 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   160 */   310,  322,   58,   84,   52,   53,  269,   63,  276,   59,
 /*   170 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   180 */   310,  322,   54,   55,  269,   63,  276,   59,   66,   82,
 /*   190 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  321,
 /*   200 */   269,   63,  276,   59,   66,   82,   81,   62,   74,  106,
 /*   210 */   105,  103,  101,   72,  310,  320,  269,   63,  276,   59,
 /*   220 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   230 */   310,  319,  269,   63,  276,   59,   66,   82,   81,   62,
 /*   240 */    74,  106,  105,  103,  101,   72,  310,  318,  269,   63,
 /*   250 */   276,   59,   66,   82,   81,   62,   74,  106,  105,  103,
 /*   260 */   101,   72,  310,  317,  269,   63,  276,   59,   66,   82,
 /*   270 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  316,
 /*   280 */   269,   63,  276,   59,   66,   82,   81,   62,   74,  106,
 /*   290 */   105,  103,  101,   72,  310,  315,  269,   63,  276,   59,
 /*   300 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   310 */   310,  314,  269,   63,  276,   59,   66,   82,   81,   62,
 /*   320 */    74,  106,  105,  103,  101,   72,  310,  313,  269,   63,
 /*   330 */   276,   59,   66,   82,   81,   62,   74,  106,  105,  103,
 /*   340 */   101,   72,  310,  312,  269,   63,  276,   59,   66,   82,
 /*   350 */    81,   62,   74,  106,  105,  103,  101,   72,  310,  311,
 /*   360 */   269,   63,  276,   59,   66,   82,   81,   62,   74,  106,
 /*   370 */   105,  103,  101,   72,  310,  323,  269,   63,  276,  280,
 /*   380 */    66,   82,   81,   62,   74,  106,  105,  103,  101,   72,
 /*   390 */   309,  269,   63,  276,  280,   66,   82,   81,   62,   74,
 /*   400 */   106,  105,  103,   99,  269,   63,  276,  280,   66,   82,
 /*   410 */    81,   62,   74,  106,  105,  100,   98,  269,   63,  276,
 /*   420 */   280,   64,    9,   91,  269,   63,  275,  179,  180,  181,
 /*   430 */   182,  183,   56,   98,    5,   21,   43,   42,   41,    9,
 /*   440 */   187,   40,   39,   38,  179,  180,  181,  182,  183,  189,
 /*   450 */    98,   94,  160,   43,   42,   41,    9,  174,    6,   88,
 /*   460 */    24,  179,  180,  181,  182,  183,  269,   63,  276,  283,
 /*   470 */    43,   42,   41,  269,   63,  276,  280,   66,   82,   81,
 /*   480 */    62,   74,  106,  102,   25,   29,   26,   20,   19,   18,
 /*   490 */    17,   16,   15,   14,   13,   12,   11,   10,   98,  269,
 /*   500 */    63,  276,  280,   65,    9,   33,   32,   31,   30,  179,
 /*   510 */   180,  181,  182,  183,   27,  178,   28,   86,   43,   42,
 /*   520 */    41,    9,  269,   63,  276,  282,  179,  180,  181,  182,
 /*   530 */   183,  269,   63,  276,  281,   43,   42,   41,  269,   63,
 /*   540 */   276,  280,   66,   82,   81,   62,   74,  104,  269,   63,
 /*   550 */   276,  280,   66,   82,   81,   62,   73,   87,  269,   63,
 /*   560 */   276,  280,   66,   82,   81,   60,  242,  242,  242,  242,
 /*   570 */   269,   63,  276,  280,   66,   82,   81,   61,   21,  269,
 /*   580 */    63,  276,  280,   66,   82,   75,  242,  269,   63,  276,
 /*   590 */   280,   66,   82,   76,  186,  242,  269,   63,  276,  280,
 /*   600 */    66,   82,   77,  269,   63,  276,  280,   66,   82,   78,
 /*   610 */   178,  269,   63,  276,  279,  242,    9,  269,   63,  276,
 /*   620 */   278,  179,  180,  181,  182,  183,  269,   63,  276,  280,
 /*   630 */    66,   79,  269,   63,  276,  280,   66,   80,  269,   63,
 /*   640 */   276,  277,   85,   85,  242,  109,  109,  169,  170,   85,
 /*   650 */   108,  108,  109,   85,  172,  242,  109,  108,  173,   85,
 /*   660 */    85,  108,  109,  109,  171,  168,   95,  108,  108,  243,
 /*   670 */    85,    2,    3,  109,   90,  242,    4,  242,  108,    4,
 /*   680 */    89,    8,   92,   96,   44,  175,    4,   36,   21,  242,
 /*   690 */   242,  242,  188,   37,  184,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    56,   57,   58,   55,   60,   61,   62,   63,   64,   65,
 /*    10 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    20 */    56,   57,   58,   54,   60,   61,   62,   63,   64,   65,
 /*    30 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    40 */    56,   57,   58,   54,   60,   61,   62,   63,   64,   65,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    59,   56,   57,   53,   54,   60,   61,   62,   63,   64,
 /*    70 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*    80 */    75,   54,   57,    2,   54,   60,   61,   62,   63,   64,
 /*    90 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   100 */    75,   54,   57,   39,   40,   60,   61,   62,   63,   64,
 /*   110 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   120 */    75,   54,   41,   57,   28,   29,   60,   61,   62,   63,
 /*   130 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   140 */    74,   75,    5,   57,    7,    1,   60,   61,   62,   63,
 /*   150 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   160 */    74,   75,    5,   57,    7,    5,   60,   61,   62,   63,
 /*   170 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   180 */    74,   75,    5,    5,   60,   61,   62,   63,   64,   65,
 /*   190 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   200 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   210 */    70,   71,   72,   73,   74,   75,   60,   61,   62,   63,
 /*   220 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   230 */    74,   75,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   240 */    68,   69,   70,   71,   72,   73,   74,   75,   60,   61,
 /*   250 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   260 */    72,   73,   74,   75,   60,   61,   62,   63,   64,   65,
 /*   270 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   280 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   290 */    70,   71,   72,   73,   74,   75,   60,   61,   62,   63,
 /*   300 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   310 */    74,   75,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   320 */    68,   69,   70,   71,   72,   73,   74,   75,   60,   61,
 /*   330 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   340 */    72,   73,   74,   75,   60,   61,   62,   63,   64,   65,
 /*   350 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   360 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   370 */    70,   71,   72,   73,   74,   75,   60,   61,   62,   63,
 /*   380 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   390 */    74,   60,   61,   62,   63,   64,   65,   66,   67,   68,
 /*   400 */    69,   70,   71,   72,   60,   61,   62,   63,   64,   65,
 /*   410 */    66,   67,   68,   69,   70,   71,    1,   60,   61,   62,
 /*   420 */    63,   64,    7,    8,   60,   61,   62,   12,   13,   14,
 /*   430 */    15,   16,    5,    1,   11,    2,   21,   22,   23,    7,
 /*   440 */     8,   24,   25,   26,   12,   13,   14,   15,   16,    1,
 /*   450 */     1,   10,    1,   21,   22,   23,    7,    8,    3,    8,
 /*   460 */    38,   12,   13,   14,   15,   16,   60,   61,   62,   63,
 /*   470 */    21,   22,   23,   60,   61,   62,   63,   64,   65,   66,
 /*   480 */    67,   68,   69,   70,   37,    3,   36,   42,   43,   44,
 /*   490 */    45,   46,   47,   48,   49,   50,   51,   52,    1,   60,
 /*   500 */    61,   62,   63,   64,    7,   30,   31,   32,   33,   12,
 /*   510 */    13,   14,   15,   16,   35,    1,   34,    1,   21,   22,
 /*   520 */    23,    7,   60,   61,   62,   63,   12,   13,   14,   15,
 /*   530 */    16,   60,   61,   62,   63,   21,   22,   23,   60,   61,
 /*   540 */    62,   63,   64,   65,   66,   67,   68,   69,   60,   61,
 /*   550 */    62,   63,   64,   65,   66,   67,   68,    1,   60,   61,
 /*   560 */    62,   63,   64,   65,   66,   67,   76,   76,   76,   76,
 /*   570 */    60,   61,   62,   63,   64,   65,   66,   67,    2,   60,
 /*   580 */    61,   62,   63,   64,   65,   66,   76,   60,   61,   62,
 /*   590 */    63,   64,   65,   66,   18,   76,   60,   61,   62,   63,
 /*   600 */    64,   65,   66,   60,   61,   62,   63,   64,   65,   66,
 /*   610 */     1,   60,   61,   62,   63,   76,    7,   60,   61,   62,
 /*   620 */    63,   12,   13,   14,   15,   16,   60,   61,   62,   63,
 /*   630 */    64,   65,   60,   61,   62,   63,   64,   65,   60,   61,
 /*   640 */    62,   63,    1,    1,   76,    4,    4,    6,    6,    1,
 /*   650 */     9,    9,    4,    1,    6,   76,    4,    9,    6,    1,
 /*   660 */     1,    9,    4,    4,    6,    6,    1,    9,    9,    0,
 /*   670 */     1,    7,    7,    4,    2,   76,    2,   76,    9,    2,
 /*   680 */     8,   17,    8,   19,   20,    8,    2,   21,    2,   76,
 /*   690 */    76,   76,    8,   27,    8,   76,   76,   76,   76,   76,
 /*   700 */    76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
 /*   710 */    76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
 /*   720 */    76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
 /*   730 */    76,   76,   76,   76,   76,   76,   76,   76,   76,   76,
 /*   740 */    76,   76,
};
#define YY_SHIFT_COUNT    (109)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (686)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   695,  415,  432,  449,  497,  514,  514,  514,  514,  514,
 /*    10 */   514,  514,  514,  514,  514,  514,  514,  514,  514,  514,
 /*    20 */   514,  514,  514,  514,  514,  514,  514,  514,  514,  514,
 /*    30 */   514,  514,  514,  514,  514,  514,  514,  514,  514,  514,
 /*    40 */   514,  514,  514,  514,  609,  641,  642,  648,  652,  658,
 /*    50 */   659,  669,  451,  695,  695,  695,  695,  695,  695,  445,
 /*    60 */   475,  475,  475,  664,  417,  417,  417,  672,  674,  677,
 /*    70 */   684,   81,   64,  482,  482,   96,   96,   96,   96,  666,
 /*    80 */   666,   96,  666,  576,  686,  665,  137,  157,  160,  177,
 /*    90 */   144,  178,  427,  433,  423,  441,  448,  433,  455,  422,
 /*   100 */   447,  422,  450,  447,  479,  450,  479,  433,  516,  556,
};
#define YY_REDUCE_COUNT (58)
#define YY_REDUCE_MIN   (-56)
#define YY_REDUCE_MAX   (578)
static const short yy_reduce_ofst[] = {
 /*     0 */    10,  -56,  -36,  -16,    5,   25,   45,   66,   86,  106,
 /*    10 */   124,  140,  156,  172,  188,  204,  220,  236,  252,  268,
 /*    20 */   284,  300,  316,  331,  344,  413,  478,  488,  498,  510,
 /*    30 */   519,  527,  536,  543,  566,  572,  357,  439,  406,  462,
 /*    40 */   471,  551,  557,  578,  364,    1,    1,    1,    1,    1,
 /*    50 */     1,    1,  -52,  -31,  -11,   27,   30,   47,   67,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   250,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    10 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    20 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    30 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    40 */   240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
 /*    50 */   240,  240,  240,  250,  250,  250,  250,  250,  250,  280,
 /*    60 */   297,  296,  295,  274,  286,  285,  284,  240,  240,  240,
 /*    70 */   240,  240,  308,  299,  298,  294,  293,  292,  291,  289,
 /*    80 */   288,  290,  287,  240,  240,  240,  240,  240,  240,  240,
 /*    90 */   240,  240,  240,  261,  260,  240,  240,  247,  262,  307,
 /*   100 */   305,  306,  303,  304,  301,  302,  300,  246,  240,  240,
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
  /*    1 */ "ID",
  /*    2 */ "COMMA",
  /*    3 */ "EQUALS",
  /*    4 */ "FN",
  /*    5 */ "LEFT_BRACE",
  /*    6 */ "RIGHT_BRACE",
  /*    7 */ "LEFT_PARENTHESIS",
  /*    8 */ "RIGHT_PARENTHESIS",
  /*    9 */ "ON",
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
  /*   54 */ "statement_list",
  /*   55 */ "formal_parameters",
  /*   56 */ "actual_parameter",
  /*   57 */ "expression",
  /*   58 */ "actual_parameters",
  /*   59 */ "statement",
  /*   60 */ "simple_expression",
  /*   61 */ "postfix_expression",
  /*   62 */ "pow_expression",
  /*   63 */ "unary_expression",
  /*   64 */ "multiplicative_expression",
  /*   65 */ "additive_expression",
  /*   66 */ "bitwise_shift_expression",
  /*   67 */ "comparison_expression",
  /*   68 */ "equality_expression",
  /*   69 */ "bitwise_and_expression",
  /*   70 */ "bitwise_xor_expression",
  /*   71 */ "bitwise_or_expression",
  /*   72 */ "and_expression",
  /*   73 */ "or_expression",
  /*   74 */ "ternary_expression",
  /*   75 */ "assignment_expression",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "root ::= statement_list",
 /*   1 */ "formal_parameters ::= ID",
 /*   2 */ "formal_parameters ::= formal_parameters COMMA ID",
 /*   3 */ "actual_parameter ::= expression",
 /*   4 */ "actual_parameter ::= ID EQUALS expression",
 /*   5 */ "actual_parameters ::= actual_parameter",
 /*   6 */ "actual_parameters ::= actual_parameters COMMA actual_parameter",
 /*   7 */ "statement_list ::=",
 /*   8 */ "statement_list ::= statement_list statement",
 /*   9 */ "statement ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE",
 /*  10 */ "statement ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  11 */ "statement ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  12 */ "statement ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE",
 /*  13 */ "statement ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  14 */ "statement ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  15 */ "statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  16 */ "statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  17 */ "statement ::= ID ID SEMICOLON",
 /*  18 */ "statement ::= ID ID SEMICOLON IF expression",
 /*  19 */ "simple_expression ::= ID",
 /*  20 */ "simple_expression ::= INT_V",
 /*  21 */ "simple_expression ::= FLOAT_V",
 /*  22 */ "simple_expression ::= STRING_V",
 /*  23 */ "simple_expression ::= TRUE",
 /*  24 */ "simple_expression ::= FALSE",
 /*  25 */ "simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS",
 /*  26 */ "postfix_expression ::= simple_expression",
 /*  27 */ "postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET",
 /*  28 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  29 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  30 */ "postfix_expression ::= postfix_expression DOT ID",
 /*  31 */ "pow_expression ::= postfix_expression",
 /*  32 */ "pow_expression ::= postfix_expression POW pow_expression",
 /*  33 */ "unary_expression ::= pow_expression",
 /*  34 */ "unary_expression ::= MINUS unary_expression",
 /*  35 */ "unary_expression ::= BITWISE_INVERT unary_expression",
 /*  36 */ "unary_expression ::= INVERT unary_expression",
 /*  37 */ "multiplicative_expression ::= unary_expression",
 /*  38 */ "multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression",
 /*  39 */ "multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression",
 /*  40 */ "multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression",
 /*  41 */ "additive_expression ::= multiplicative_expression",
 /*  42 */ "additive_expression ::= additive_expression PLUS multiplicative_expression",
 /*  43 */ "additive_expression ::= additive_expression MINUS multiplicative_expression",
 /*  44 */ "bitwise_shift_expression ::= additive_expression",
 /*  45 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression",
 /*  46 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression",
 /*  47 */ "comparison_expression ::= bitwise_shift_expression",
 /*  48 */ "comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression",
 /*  49 */ "comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression",
 /*  50 */ "comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression",
 /*  51 */ "comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression",
 /*  52 */ "equality_expression ::= comparison_expression",
 /*  53 */ "equality_expression ::= equality_expression EQUALS comparison_expression",
 /*  54 */ "equality_expression ::= equality_expression NOT_EQUALS comparison_expression",
 /*  55 */ "bitwise_and_expression ::= equality_expression",
 /*  56 */ "bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression",
 /*  57 */ "bitwise_xor_expression ::= bitwise_and_expression",
 /*  58 */ "bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression",
 /*  59 */ "bitwise_or_expression ::= bitwise_xor_expression",
 /*  60 */ "bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression",
 /*  61 */ "and_expression ::= bitwise_or_expression",
 /*  62 */ "and_expression ::= and_expression AND bitwise_or_expression",
 /*  63 */ "or_expression ::= and_expression",
 /*  64 */ "or_expression ::= or_expression OR and_expression",
 /*  65 */ "ternary_expression ::= or_expression",
 /*  66 */ "ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression",
 /*  67 */ "assignment_expression ::= ternary_expression",
 /*  68 */ "assignment_expression ::= unary_expression ASSIGN assignment_expression",
 /*  69 */ "assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression",
 /*  70 */ "assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression",
 /*  71 */ "assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression",
 /*  72 */ "assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression",
 /*  73 */ "assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression",
 /*  74 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression",
 /*  75 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression",
 /*  76 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression",
 /*  77 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression",
 /*  78 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression",
 /*  79 */ "expression ::= assignment_expression",
 /*  80 */ "expression ::= expression COMMA assignment_expression",
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
    case 1: /* ID */
    case 2: /* COMMA */
    case 3: /* EQUALS */
    case 4: /* FN */
    case 5: /* LEFT_BRACE */
    case 6: /* RIGHT_BRACE */
    case 7: /* LEFT_PARENTHESIS */
    case 8: /* RIGHT_PARENTHESIS */
    case 9: /* ON */
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

#line 844 "zl_parser.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 53: /* root */
    case 54: /* statement_list */
    case 55: /* formal_parameters */
    case 56: /* actual_parameter */
    case 57: /* expression */
    case 58: /* actual_parameters */
    case 59: /* statement */
    case 60: /* simple_expression */
    case 61: /* postfix_expression */
    case 62: /* pow_expression */
    case 63: /* unary_expression */
    case 64: /* multiplicative_expression */
    case 65: /* additive_expression */
    case 66: /* bitwise_shift_expression */
    case 67: /* comparison_expression */
    case 68: /* equality_expression */
    case 69: /* bitwise_and_expression */
    case 70: /* bitwise_xor_expression */
    case 71: /* bitwise_or_expression */
    case 72: /* and_expression */
    case 73: /* or_expression */
    case 74: /* ternary_expression */
    case 75: /* assignment_expression */
{
#line 34 "zl_parser.y"

    ast_defaultDestructor((yypminor->yy33));

#line 876 "zl_parser.c"
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
#line 40 "zl_parser.y"

    parser_onStackOverflow(context);
#line 1100 "zl_parser.c"
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
  {   53,   -1 }, /* (0) root ::= statement_list */
  {   55,   -1 }, /* (1) formal_parameters ::= ID */
  {   55,   -3 }, /* (2) formal_parameters ::= formal_parameters COMMA ID */
  {   56,   -1 }, /* (3) actual_parameter ::= expression */
  {   56,   -3 }, /* (4) actual_parameter ::= ID EQUALS expression */
  {   58,   -1 }, /* (5) actual_parameters ::= actual_parameter */
  {   58,   -3 }, /* (6) actual_parameters ::= actual_parameters COMMA actual_parameter */
  {   54,    0 }, /* (7) statement_list ::= */
  {   54,   -2 }, /* (8) statement_list ::= statement_list statement */
  {   59,   -5 }, /* (9) statement ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -7 }, /* (10) statement ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -8 }, /* (11) statement ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -5 }, /* (12) statement ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -7 }, /* (13) statement ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -8 }, /* (14) statement ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   59,   -3 }, /* (15) statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   59,   -4 }, /* (16) statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   59,   -3 }, /* (17) statement ::= ID ID SEMICOLON */
  {   59,   -5 }, /* (18) statement ::= ID ID SEMICOLON IF expression */
  {   60,   -1 }, /* (19) simple_expression ::= ID */
  {   60,   -1 }, /* (20) simple_expression ::= INT_V */
  {   60,   -1 }, /* (21) simple_expression ::= FLOAT_V */
  {   60,   -1 }, /* (22) simple_expression ::= STRING_V */
  {   60,   -1 }, /* (23) simple_expression ::= TRUE */
  {   60,   -1 }, /* (24) simple_expression ::= FALSE */
  {   60,   -3 }, /* (25) simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
  {   61,   -1 }, /* (26) postfix_expression ::= simple_expression */
  {   61,   -4 }, /* (27) postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
  {   61,   -3 }, /* (28) postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   61,   -4 }, /* (29) postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   61,   -3 }, /* (30) postfix_expression ::= postfix_expression DOT ID */
  {   62,   -1 }, /* (31) pow_expression ::= postfix_expression */
  {   62,   -3 }, /* (32) pow_expression ::= postfix_expression POW pow_expression */
  {   63,   -1 }, /* (33) unary_expression ::= pow_expression */
  {   63,   -2 }, /* (34) unary_expression ::= MINUS unary_expression */
  {   63,   -2 }, /* (35) unary_expression ::= BITWISE_INVERT unary_expression */
  {   63,   -2 }, /* (36) unary_expression ::= INVERT unary_expression */
  {   64,   -1 }, /* (37) multiplicative_expression ::= unary_expression */
  {   64,   -3 }, /* (38) multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression */
  {   64,   -3 }, /* (39) multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression */
  {   64,   -3 }, /* (40) multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression */
  {   65,   -1 }, /* (41) additive_expression ::= multiplicative_expression */
  {   65,   -3 }, /* (42) additive_expression ::= additive_expression PLUS multiplicative_expression */
  {   65,   -3 }, /* (43) additive_expression ::= additive_expression MINUS multiplicative_expression */
  {   66,   -1 }, /* (44) bitwise_shift_expression ::= additive_expression */
  {   66,   -3 }, /* (45) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
  {   66,   -3 }, /* (46) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
  {   67,   -1 }, /* (47) comparison_expression ::= bitwise_shift_expression */
  {   67,   -3 }, /* (48) comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
  {   67,   -3 }, /* (49) comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
  {   67,   -3 }, /* (50) comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
  {   67,   -3 }, /* (51) comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
  {   68,   -1 }, /* (52) equality_expression ::= comparison_expression */
  {   68,   -3 }, /* (53) equality_expression ::= equality_expression EQUALS comparison_expression */
  {   68,   -3 }, /* (54) equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
  {   69,   -1 }, /* (55) bitwise_and_expression ::= equality_expression */
  {   69,   -3 }, /* (56) bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
  {   70,   -1 }, /* (57) bitwise_xor_expression ::= bitwise_and_expression */
  {   70,   -3 }, /* (58) bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
  {   71,   -1 }, /* (59) bitwise_or_expression ::= bitwise_xor_expression */
  {   71,   -3 }, /* (60) bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
  {   72,   -1 }, /* (61) and_expression ::= bitwise_or_expression */
  {   72,   -3 }, /* (62) and_expression ::= and_expression AND bitwise_or_expression */
  {   73,   -1 }, /* (63) or_expression ::= and_expression */
  {   73,   -3 }, /* (64) or_expression ::= or_expression OR and_expression */
  {   74,   -1 }, /* (65) ternary_expression ::= or_expression */
  {   74,   -5 }, /* (66) ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
  {   75,   -1 }, /* (67) assignment_expression ::= ternary_expression */
  {   75,   -3 }, /* (68) assignment_expression ::= unary_expression ASSIGN assignment_expression */
  {   75,   -3 }, /* (69) assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
  {   75,   -3 }, /* (70) assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
  {   75,   -3 }, /* (71) assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
  {   75,   -3 }, /* (72) assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
  {   75,   -3 }, /* (73) assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
  {   75,   -3 }, /* (74) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
  {   75,   -3 }, /* (75) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
  {   75,   -3 }, /* (76) assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
  {   75,   -3 }, /* (77) assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
  {   75,   -3 }, /* (78) assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
  {   57,   -1 }, /* (79) expression ::= assignment_expression */
  {   57,   -3 }, /* (80) expression ::= expression COMMA assignment_expression */
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
      case 0: /* root ::= statement_list */
#line 53 "zl_parser.y"
{ yylhsminor.yy9 = new RootNode(std::move(yymsp[0].minor.yy102)); }
#line 1346 "zl_parser.c"
  yymsp[0].minor.yy9 = yylhsminor.yy9;
        break;
      case 1: /* formal_parameters ::= ID */
#line 56 "zl_parser.y"
{ std::vector<std::string> v; v.push_back(yymsp[0].minor.yy0); yylhsminor.yy127 = std::move(v); }
#line 1352 "zl_parser.c"
  yymsp[0].minor.yy127 = yylhsminor.yy127;
        break;
      case 2: /* formal_parameters ::= formal_parameters COMMA ID */
#line 57 "zl_parser.y"
{ yylhsminor.yy127 = std::move(yymsp[-2].minor.yy127); FPSN.push_back(yymsp[0].minor.yy0); }
#line 1358 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-1].minor);
  yymsp[-2].minor.yy127 = yylhsminor.yy127;
        break;
      case 3: /* actual_parameter ::= expression */
#line 60 "zl_parser.y"
{ yylhsminor.yy128 = ActualParameterNode(yymsp[0].minor.yy33); }
#line 1365 "zl_parser.c"
  yymsp[0].minor.yy128 = yylhsminor.yy128;
        break;
      case 4: /* actual_parameter ::= ID EQUALS expression */
#line 61 "zl_parser.y"
{ yylhsminor.yy128 = ActualParameterNode(yymsp[-2].minor.yy0, yymsp[0].minor.yy33); }
#line 1371 "zl_parser.c"
  yy_destructor(yypParser,3,&yymsp[-1].minor);
  yymsp[-2].minor.yy128 = yylhsminor.yy128;
        break;
      case 5: /* actual_parameters ::= actual_parameter */
#line 64 "zl_parser.y"
{ std::vector<ActualParameterNode*> v; yylhsminor.yy104 = std::move(v); yylhsminor.yy104.push_back(yymsp[0].minor.yy128); }
#line 1378 "zl_parser.c"
  yymsp[0].minor.yy104 = yylhsminor.yy104;
        break;
      case 6: /* actual_parameters ::= actual_parameters COMMA actual_parameter */
#line 65 "zl_parser.y"
{ yymsp[-2].minor.yy104.push_back(yymsp[0].minor.yy128); yylhsminor.yy104 = std::move(yymsp[-2].minor.yy104);  }
#line 1384 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-1].minor);
  yymsp[-2].minor.yy104 = yylhsminor.yy104;
        break;
      case 7: /* statement_list ::= */
#line 68 "zl_parser.y"
{ std::vector<StatementNode*> v; yymsp[1].minor.yy102 = std::move(v); }
#line 1391 "zl_parser.c"
        break;
      case 8: /* statement_list ::= statement_list statement */
#line 69 "zl_parser.y"
{ yymsp[-1].minor.yy102.push_back(yymsp[0].minor.yy46); yylhsminor.yy102 = std::move(yymsp[-1].minor.yy102); }
#line 1396 "zl_parser.c"
  yymsp[-1].minor.yy102 = yylhsminor.yy102;
        break;
      case 9: /* statement ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,4,&yymsp[-4].minor);
#line 75 "zl_parser.y"
{ yymsp[-4].minor.yy46 = new FunctionDefinitionNode(yymsp[-1].minor.yy102); }
#line 1403 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 10: /* statement ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,4,&yymsp[-6].minor);
#line 76 "zl_parser.y"
{ yymsp[-6].minor.yy46 = new FunctionDefinitionNode(yymsp[-1].minor.yy102); }
#line 1413 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-5].minor);
  yy_destructor(yypParser,7,&yymsp[-4].minor);
  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 11: /* statement ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,4,&yymsp[-7].minor);
#line 77 "zl_parser.y"
{ yymsp[-7].minor.yy46 = new FunctionDefinitionNode(yymsp[-4].minor.yy127, yymsp[-1].minor.yy102); }
#line 1425 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-6].minor);
  yy_destructor(yypParser,7,&yymsp[-5].minor);
  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 12: /* statement ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,9,&yymsp[-4].minor);
#line 80 "zl_parser.y"
{ yymsp[-4].minor.yy46 = new EventHandlerDefinitionNode(yymsp[-1].minor.yy102); }
#line 1437 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 13: /* statement ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,9,&yymsp[-6].minor);
#line 81 "zl_parser.y"
{ yymsp[-6].minor.yy46 = new EventHandlerDefinitionNode(yymsp[-1].minor.yy102); }
#line 1447 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-5].minor);
  yy_destructor(yypParser,7,&yymsp[-4].minor);
  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 14: /* statement ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,9,&yymsp[-7].minor);
#line 82 "zl_parser.y"
{ yymsp[-7].minor.yy46 = EventHandlerDefinitionNode(yymsp[-4].minor.yy104, yymsp[-1].minor.yy102); }
#line 1459 "zl_parser.c"
  yy_destructor(yypParser,1,&yymsp[-6].minor);
  yy_destructor(yypParser,7,&yymsp[-5].minor);
  yy_destructor(yypParser,8,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 15: /* statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
#line 85 "zl_parser.y"
{ yylhsminor.yy46 = new FunctionCallStatementNode(yymsp[-2].minor.yy0); }
#line 1470 "zl_parser.c"
  yy_destructor(yypParser,7,&yymsp[-1].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
  yymsp[-2].minor.yy46 = yylhsminor.yy46;
        break;
      case 16: /* statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
#line 86 "zl_parser.y"
{ yylhsminor.yy46 = new FunctionCallStatementNode(yymsp[-3].minor.yy0, yymsp[-1].minor.yy104); }
#line 1478 "zl_parser.c"
  yy_destructor(yypParser,7,&yymsp[-2].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
  yymsp[-3].minor.yy46 = yylhsminor.yy46;
        break;
      case 17: /* statement ::= ID ID SEMICOLON */
#line 89 "zl_parser.y"
{ yylhsminor.yy46 = new PushStatementNode(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0); }
#line 1486 "zl_parser.c"
  yy_destructor(yypParser,10,&yymsp[0].minor);
  yymsp[-2].minor.yy46 = yylhsminor.yy46;
        break;
      case 18: /* statement ::= ID ID SEMICOLON IF expression */
#line 90 "zl_parser.y"
{ yylhsminor.yy46 = new PushStatementNode(yymsp[-4].minor.yy0, yymsp[-3].minor.yy0, yymsp[0].minor.yy33); }
#line 1493 "zl_parser.c"
  yy_destructor(yypParser,10,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[-1].minor);
  yymsp[-4].minor.yy46 = yylhsminor.yy46;
        break;
      case 19: /* simple_expression ::= ID */
#line 94 "zl_parser.y"
{ yylhsminor.yy33 = new IdExpressionNode(yymsp[0].minor.yy0.payload.string); }
#line 1501 "zl_parser.c"
  yymsp[0].minor.yy33 = yylhsminor.yy33;
        break;
      case 20: /* simple_expression ::= INT_V */
#line 95 "zl_parser.y"
{ yylhsminor.yy33 = new IntLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1507 "zl_parser.c"
  yymsp[0].minor.yy33 = yylhsminor.yy33;
        break;
      case 21: /* simple_expression ::= FLOAT_V */
#line 96 "zl_parser.y"
{ yylhsminor.yy33 = new FloatLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1513 "zl_parser.c"
  yymsp[0].minor.yy33 = yylhsminor.yy33;
        break;
      case 22: /* simple_expression ::= STRING_V */
#line 97 "zl_parser.y"
{ yylhsminor.yy33 = new StringLiteralExpressionNode(yymsp[0].minor.yy0.payload.TODO); }
#line 1519 "zl_parser.c"
  yymsp[0].minor.yy33 = yylhsminor.yy33;
        break;
      case 23: /* simple_expression ::= TRUE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 98 "zl_parser.y"
{ yymsp[0].minor.yy33 = new BooleanLiteralExpressionNode(true); }
#line 1526 "zl_parser.c"
}
        break;
      case 24: /* simple_expression ::= FALSE */
{  yy_destructor(yypParser,16,&yymsp[0].minor);
#line 99 "zl_parser.y"
{ yymsp[0].minor.yy33 = new BooleanLiteralExpressionNode(false); }
#line 1533 "zl_parser.c"
}
        break;
      case 25: /* simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
{  yy_destructor(yypParser,7,&yymsp[-2].minor);
#line 100 "zl_parser.y"
{ yymsp[-2].minor.yy33 = yymsp[-1].minor.yy33; }
#line 1540 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[0].minor);
}
        break;
      case 26: /* postfix_expression ::= simple_expression */
      case 31: /* pow_expression ::= postfix_expression */ yytestcase(yyruleno==31);
      case 33: /* unary_expression ::= pow_expression */ yytestcase(yyruleno==33);
      case 37: /* multiplicative_expression ::= unary_expression */ yytestcase(yyruleno==37);
      case 41: /* additive_expression ::= multiplicative_expression */ yytestcase(yyruleno==41);
      case 44: /* bitwise_shift_expression ::= additive_expression */ yytestcase(yyruleno==44);
      case 47: /* comparison_expression ::= bitwise_shift_expression */ yytestcase(yyruleno==47);
      case 52: /* equality_expression ::= comparison_expression */ yytestcase(yyruleno==52);
      case 55: /* bitwise_and_expression ::= equality_expression */ yytestcase(yyruleno==55);
      case 57: /* bitwise_xor_expression ::= bitwise_and_expression */ yytestcase(yyruleno==57);
      case 59: /* bitwise_or_expression ::= bitwise_xor_expression */ yytestcase(yyruleno==59);
      case 61: /* and_expression ::= bitwise_or_expression */ yytestcase(yyruleno==61);
      case 63: /* or_expression ::= and_expression */ yytestcase(yyruleno==63);
      case 65: /* ternary_expression ::= or_expression */ yytestcase(yyruleno==65);
      case 67: /* assignment_expression ::= ternary_expression */ yytestcase(yyruleno==67);
      case 79: /* expression ::= assignment_expression */ yytestcase(yyruleno==79);
#line 104 "zl_parser.y"
{ yylhsminor.yy33 = yymsp[0].minor.yy33; }
#line 1562 "zl_parser.c"
  yymsp[0].minor.yy33 = yylhsminor.yy33;
        break;
      case 27: /* postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
#line 105 "zl_parser.y"
{ yylhsminor.yy33 = new IndexingExpressionNode(yymsp[-3].minor.yy33, yymsp[-1].minor.yy33); }
#line 1568 "zl_parser.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,18,&yymsp[0].minor);
  yymsp[-3].minor.yy33 = yylhsminor.yy33;
        break;
      case 28: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
#line 106 "zl_parser.y"
{ yylhsminor.yy33 = new FunctionCallExpressionNode(yymsp[-2].minor.yy33); }
#line 1576 "zl_parser.c"
  yy_destructor(yypParser,7,&yymsp[-1].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 29: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
#line 107 "zl_parser.y"
{ yylhsminor.yy33 = new FunctionCallExpressionNode(yymsp[-3].minor.yy33, yymsp[-1].minor.yy104); }
#line 1584 "zl_parser.c"
  yy_destructor(yypParser,7,&yymsp[-2].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
  yymsp[-3].minor.yy33 = yylhsminor.yy33;
        break;
      case 30: /* postfix_expression ::= postfix_expression DOT ID */
#line 108 "zl_parser.y"
{ yylhsminor.yy33 = new MemberAccessExpressionNode(yymsp[-2].minor.yy33, yymsp[0].minor.yy0); }
#line 1592 "zl_parser.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 32: /* pow_expression ::= postfix_expression POW pow_expression */
#line 114 "zl_parser.y"
{ yylhsminor.yy33 = new PowExpressionNode(yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1599 "zl_parser.c"
  yy_destructor(yypParser,20,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 34: /* unary_expression ::= MINUS unary_expression */
{  yy_destructor(yypParser,21,&yymsp[-1].minor);
#line 119 "zl_parser.y"
{ yymsp[-1].minor.yy33 = new UnaryExpressionNode(UnaryExpressionType::NEGATION, yymsp[0].minor.yy33); }
#line 1607 "zl_parser.c"
}
        break;
      case 35: /* unary_expression ::= BITWISE_INVERT unary_expression */
{  yy_destructor(yypParser,22,&yymsp[-1].minor);
#line 120 "zl_parser.y"
{ yymsp[-1].minor.yy33 = new UnaryExpressionNode(UnaryExpressionType::BITWISE_INVERT, yymsp[0].minor.yy33); }
#line 1614 "zl_parser.c"
}
        break;
      case 36: /* unary_expression ::= INVERT unary_expression */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 121 "zl_parser.y"
{ yymsp[-1].minor.yy33 = new UnaryExpressionNode(UnaryExpressionType::INVERT, yymsp[0].minor.yy33); }
#line 1621 "zl_parser.c"
}
        break;
      case 38: /* multiplicative_expression ::= multiplicative_expression MULTIPLY unary_expression */
#line 126 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::MULTIPLICATION, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1627 "zl_parser.c"
  yy_destructor(yypParser,24,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 39: /* multiplicative_expression ::= multiplicative_expression DIVIDE unary_expression */
#line 127 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::DIVISION, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1634 "zl_parser.c"
  yy_destructor(yypParser,25,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 40: /* multiplicative_expression ::= multiplicative_expression REMAINDER unary_expression */
#line 128 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::REMAINDER, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1641 "zl_parser.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 42: /* additive_expression ::= additive_expression PLUS multiplicative_expression */
#line 133 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ADDITION, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1648 "zl_parser.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 43: /* additive_expression ::= additive_expression MINUS multiplicative_expression */
#line 134 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::SUBTRACTION, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1655 "zl_parser.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 45: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
#line 139 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1662 "zl_parser.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 46: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
#line 140 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1669 "zl_parser.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 48: /* comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
#line 145 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1676 "zl_parser.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 49: /* comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
#line 146 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1683 "zl_parser.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 50: /* comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
#line 147 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::LESS_THAN_OR_EQUAL, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1690 "zl_parser.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 51: /* comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
#line 148 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::GREATER_THAN_OR_EQUAL, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1697 "zl_parser.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 53: /* equality_expression ::= equality_expression EQUALS comparison_expression */
#line 153 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::EQUAL, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1704 "zl_parser.c"
  yy_destructor(yypParser,3,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 54: /* equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
#line 154 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::NOT_EQUAL, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1711 "zl_parser.c"
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 56: /* bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
#line 159 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_AND, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1718 "zl_parser.c"
  yy_destructor(yypParser,35,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 58: /* bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
#line 164 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_XOR, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1725 "zl_parser.c"
  yy_destructor(yypParser,36,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 60: /* bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
#line 169 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::BITWISE_OR, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1732 "zl_parser.c"
  yy_destructor(yypParser,37,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 62: /* and_expression ::= and_expression AND bitwise_or_expression */
#line 174 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::AND, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1739 "zl_parser.c"
  yy_destructor(yypParser,38,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 64: /* or_expression ::= or_expression OR and_expression */
#line 179 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::OR, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1746 "zl_parser.c"
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 66: /* ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
#line 184 "zl_parser.y"
{ yylhsminor.yy33 = new TernaryExpressionNode(yymsp[-4].minor.yy33, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1753 "zl_parser.c"
  yy_destructor(yypParser,40,&yymsp[-3].minor);
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yymsp[-4].minor.yy33 = yylhsminor.yy33;
        break;
      case 68: /* assignment_expression ::= unary_expression ASSIGN assignment_expression */
#line 189 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1761 "zl_parser.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 69: /* assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
#line 190 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MULTIPLY, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1768 "zl_parser.c"
  yy_destructor(yypParser,43,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 70: /* assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
#line 191 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_DIVIDE, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1775 "zl_parser.c"
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 71: /* assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
#line 192 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_REMAINDER, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1782 "zl_parser.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 72: /* assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
#line 193 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_PLUS, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1789 "zl_parser.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 73: /* assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
#line 194 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_MINUS, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1796 "zl_parser.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 74: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
#line 195 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1803 "zl_parser.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 75: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
#line 196 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1810 "zl_parser.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 76: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
#line 197 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_AND, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1817 "zl_parser.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 77: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
#line 198 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_XOR, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1824 "zl_parser.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 78: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
#line 199 "zl_parser.y"
{ yylhsminor.yy33 = new BinaryExpressionNode(BinaryExpressionType::ASSIGN_BITWISE_OR, yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1831 "zl_parser.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
        break;
      case 80: /* expression ::= expression COMMA assignment_expression */
#line 204 "zl_parser.y"
{ yylhsminor.yy33 = new CommaExpressionNode(yymsp[-2].minor.yy33, yymsp[0].minor.yy33); }
#line 1838 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-1].minor);
  yymsp[-2].minor.yy33 = yylhsminor.yy33;
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
#line 30 "zl_parser.y"

    parser_onFatalSyntaxError(context);
#line 1887 "zl_parser.c"
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
#line 22 "zl_parser.y"

    parser_onSyntaxError(context, &TOKEN);
#line 1909 "zl_parser.c"
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
#line 26 "zl_parser.y"

    parser_onParsingFinished(context);
#line 1938 "zl_parser.c"
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
