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
#define YYNOCODE 83
#define YYACTIONTYPE unsigned short int
#define zl_parseTOKENTYPE Token
typedef union {
  int yyinit;
  zl_parseTOKENTYPE yy0;
  Definition* yy12;
  std::vector<Definition*> yy108;
  base_node_t* yy122;
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
#define YYNSTATE             101
#define YYNRULE              89
#define YYNTOKEN             56
#define YY_MAX_SHIFT         100
#define YY_MIN_SHIFTREDUCE   154
#define YY_MAX_SHIFTREDUCE   242
#define YY_ERROR_ACTION      243
#define YY_ACCEPT_ACTION     244
#define YY_NO_ACTION         245
#define YY_MIN_REDUCE        246
#define YY_MAX_REDUCE        334
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
#define YY_ACTTAB_COUNT (696)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    65,   65,   99,   63,   56,   56,  254,   55,  260,   62,
 /*    10 */    77,   76,   59,   69,   98,   97,   95,   93,   67,  290,
 /*    20 */   302,   64,   64,   99,  247,   56,   56,  254,   55,  260,
 /*    30 */    62,   77,   76,   59,   69,   98,   97,   95,   93,   67,
 /*    40 */   290,  302,  314,   99,   47,   56,   56,  254,   55,  260,
 /*    50 */    62,   77,   76,   59,   69,   98,   97,   95,   93,   67,
 /*    60 */   290,  302,   85,   48,   56,   56,  254,   55,  260,   62,
 /*    70 */    77,   76,   59,   69,   98,   97,   95,   93,   67,  290,
 /*    80 */   302,   89,   50,   56,   56,  254,   55,  260,   62,   77,
 /*    90 */    76,   59,   69,   98,   97,   95,   93,   67,  290,  302,
 /*   100 */    66,  218,   56,   56,  254,   55,  260,   62,   77,   76,
 /*   110 */    59,   69,   98,   97,   95,   93,   67,  290,  302,   78,
 /*   120 */    52,   56,   56,  254,   55,  260,   62,   77,   76,   59,
 /*   130 */    69,   98,   97,   95,   93,   67,  290,  302,   79,   53,
 /*   140 */    56,   56,  254,   55,  260,   62,   77,   76,   59,   69,
 /*   150 */    98,   97,   95,   93,   67,  290,  302,   56,   56,  254,
 /*   160 */    55,  260,   62,   77,   76,   59,   69,   98,   97,   95,
 /*   170 */    93,   67,  290,  301,   56,   56,  254,   55,  260,   62,
 /*   180 */    77,   76,   59,   69,   98,   97,   95,   93,   67,  290,
 /*   190 */   300,   56,   56,  254,   55,  260,   62,   77,   76,   59,
 /*   200 */    69,   98,   97,   95,   93,   67,  290,  299,   56,   56,
 /*   210 */   254,   55,  260,   62,   77,   76,   59,   69,   98,   97,
 /*   220 */    95,   93,   67,  290,  298,   56,   56,  254,   55,  260,
 /*   230 */    62,   77,   76,   59,   69,   98,   97,   95,   93,   67,
 /*   240 */   290,  297,   56,   56,  254,   55,  260,   62,   77,   76,
 /*   250 */    59,   69,   98,   97,   95,   93,   67,  290,  296,   56,
 /*   260 */    56,  254,   55,  260,   62,   77,   76,   59,   69,   98,
 /*   270 */    97,   95,   93,   67,  290,  295,   56,   56,  254,   55,
 /*   280 */   260,   62,   77,   76,   59,   69,   98,   97,   95,   93,
 /*   290 */    67,  290,  294,   56,   56,  254,   55,  260,   62,   77,
 /*   300 */    76,   59,   69,   98,   97,   95,   93,   67,  290,  293,
 /*   310 */    56,   56,  254,   55,  260,   62,   77,   76,   59,   69,
 /*   320 */    98,   97,   95,   93,   67,  290,  292,   56,   56,  254,
 /*   330 */    55,  260,   62,   77,   76,   59,   69,   98,   97,   95,
 /*   340 */    93,   67,  290,  291,   56,   56,  254,   55,  260,   62,
 /*   350 */    77,   76,   59,   69,   98,   97,   95,   93,   67,  290,
 /*   360 */   303,   56,   56,  254,  259,  260,   62,   77,   76,   59,
 /*   370 */    69,   98,   97,   95,   93,   67,  289,   90,  244,   51,
 /*   380 */     8,  238,   56,   56,  254,  259,  263,  230,  231,  232,
 /*   390 */   233,  234,   56,   56,  251,   45,   44,  316,   43,   42,
 /*   400 */    41,   40,   90,  304,  100,    8,  225,   56,   56,  254,
 /*   410 */   259,  262,  230,  231,  232,  233,  234,   39,   38,   37,
 /*   420 */    45,   44,    4,   43,   42,   41,   40,   56,   56,  254,
 /*   430 */   259,  260,   62,   77,   76,   59,   69,   98,   97,   95,
 /*   440 */    91,   90,  217,   80,    8,  213,   84,   56,   56,  254,
 /*   450 */   258,  230,  231,  232,  233,  234,   22,    6,  229,   45,
 /*   460 */    44,    8,   43,   42,   41,   40,   34,   33,  230,  231,
 /*   470 */   232,  233,  234,   80,   20,  157,   45,   44,   86,   43,
 /*   480 */    42,   41,   40,   56,   56,  254,  259,  260,   62,   77,
 /*   490 */    76,   59,   69,   98,   97,   92,   56,   56,  254,  259,
 /*   500 */   260,   62,   77,   76,   59,   69,   98,   94,   56,   56,
 /*   510 */   254,  259,  260,   62,   77,   76,   59,   69,   96,   80,
 /*   520 */     5,  156,   19,   18,   17,   16,   15,   14,   13,   12,
 /*   530 */    11,   10,    9,  240,   23,   56,   56,  254,  259,  260,
 /*   540 */    62,   77,   76,   59,   68,   24,   56,   56,  254,  259,
 /*   550 */   260,   62,   77,   76,   57,   56,   56,  254,  259,  260,
 /*   560 */    62,   77,   76,   58,  229,   20,   25,    8,   56,   56,
 /*   570 */   254,  259,  260,   60,  230,  231,  232,  233,  234,   83,
 /*   580 */    26,   82,   45,   44,   56,   56,  254,  259,  260,   62,
 /*   590 */    77,   70,   56,   56,  254,  259,  260,   62,   77,   71,
 /*   600 */    81,   21,   56,   56,  254,  259,  260,   62,   77,   72,
 /*   610 */    56,   56,  254,  259,  260,   62,   77,   73,   56,   56,
 /*   620 */   254,  259,  260,   62,   74,   56,   56,  254,  259,  260,
 /*   630 */    62,   75,    1,  245,   56,   56,  254,  259,  260,   61,
 /*   640 */    56,   56,  254,  257,    7,  245,   88,  241,  242,   46,
 /*   650 */    56,   56,  254,  259,  261,   56,   56,  254,  256,   56,
 /*   660 */    56,  254,  255,   56,   56,  254,  253,   28,  245,   56,
 /*   670 */    56,  254,  252,   32,   31,   30,   29,  226,  239,    3,
 /*   680 */     3,   20,   35,  235,   87,   20,   54,    2,   49,   36,
 /*   690 */   245,  237,  245,  245,  245,   27,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    62,   63,   64,   60,   66,   67,   68,   69,   70,   71,
 /*    10 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*    20 */    82,   62,   63,   64,   58,   66,   67,   68,   69,   70,
 /*    30 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*    40 */    81,   82,   63,   64,   59,   66,   67,   68,   69,   70,
 /*    50 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*    60 */    81,   82,   64,   59,   66,   67,   68,   69,   70,   71,
 /*    70 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*    80 */    82,   64,   59,   66,   67,   68,   69,   70,   71,   72,
 /*    90 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   100 */    64,    2,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   110 */    74,   75,   76,   77,   78,   79,   80,   81,   82,   64,
 /*   120 */     3,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   130 */    75,   76,   77,   78,   79,   80,   81,   82,   64,    3,
 /*   140 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   150 */    76,   77,   78,   79,   80,   81,   82,   66,   67,   68,
 /*   160 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   170 */    79,   80,   81,   82,   66,   67,   68,   69,   70,   71,
 /*   180 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*   190 */    82,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   200 */    75,   76,   77,   78,   79,   80,   81,   82,   66,   67,
 /*   210 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   220 */    78,   79,   80,   81,   82,   66,   67,   68,   69,   70,
 /*   230 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   240 */    81,   82,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   250 */    74,   75,   76,   77,   78,   79,   80,   81,   82,   66,
 /*   260 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   270 */    77,   78,   79,   80,   81,   82,   66,   67,   68,   69,
 /*   280 */    70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
 /*   290 */    80,   81,   82,   66,   67,   68,   69,   70,   71,   72,
 /*   300 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   310 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   320 */    76,   77,   78,   79,   80,   81,   82,   66,   67,   68,
 /*   330 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   340 */    79,   80,   81,   82,   66,   67,   68,   69,   70,   71,
 /*   350 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*   360 */    82,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   370 */    75,   76,   77,   78,   79,   80,   81,    2,   56,   57,
 /*   380 */     5,    6,   66,   67,   68,   69,   70,   12,   13,   14,
 /*   390 */    15,   16,   66,   67,   68,   20,   21,   65,   23,   24,
 /*   400 */    25,   26,    2,    0,    1,    5,    6,   66,   67,   68,
 /*   410 */    69,   70,   12,   13,   14,   15,   16,   27,   28,   29,
 /*   420 */    20,   21,   11,   23,   24,   25,   26,   66,   67,   68,
 /*   430 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   440 */    79,    2,    2,    2,    5,    4,    6,   66,   67,   68,
 /*   450 */    69,   12,   13,   14,   15,   16,   42,   43,    2,   20,
 /*   460 */    21,    5,   23,   24,   25,   26,   31,   32,   12,   13,
 /*   470 */    14,   15,   16,    2,    8,    4,   20,   21,   10,   23,
 /*   480 */    24,   25,   26,   66,   67,   68,   69,   70,   71,   72,
 /*   490 */    73,   74,   75,   76,   77,   78,   66,   67,   68,   69,
 /*   500 */    70,   71,   72,   73,   74,   75,   76,   77,   66,   67,
 /*   510 */    68,   69,   70,   71,   72,   73,   74,   75,   76,    2,
 /*   520 */     9,    4,   45,   46,   47,   48,   49,   50,   51,   52,
 /*   530 */    53,   54,   55,    2,   41,   66,   67,   68,   69,   70,
 /*   540 */    71,   72,   73,   74,   75,   40,   66,   67,   68,   69,
 /*   550 */    70,   71,   72,   73,   74,   66,   67,   68,   69,   70,
 /*   560 */    71,   72,   73,   74,    2,    8,   39,    5,   66,   67,
 /*   570 */    68,   69,   70,   71,   12,   13,   14,   15,   16,    6,
 /*   580 */    38,    8,   20,   21,   66,   67,   68,   69,   70,   71,
 /*   590 */    72,   73,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   600 */     2,   44,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   610 */    66,   67,   68,   69,   70,   71,   72,   73,   66,   67,
 /*   620 */    68,   69,   70,   71,   72,   66,   67,   68,   69,   70,
 /*   630 */    71,   72,    5,   83,   66,   67,   68,   69,   70,   71,
 /*   640 */    66,   67,   68,   69,   17,   83,   19,   20,   21,   22,
 /*   650 */    66,   67,   68,   69,   70,   66,   67,   68,   69,   66,
 /*   660 */    67,   68,   69,   66,   67,   68,   69,    9,   83,   66,
 /*   670 */    67,   68,   69,   33,   34,   35,   36,    6,    6,    8,
 /*   680 */     8,    8,   23,    6,    2,    8,    3,    5,    5,   30,
 /*   690 */    83,   18,   83,   83,   83,   37,   83,   83,   83,   83,
 /*   700 */    83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
 /*   710 */    83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
 /*   720 */    83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
 /*   730 */    83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
 /*   740 */    83,   83,   83,
};
#define YY_SHIFT_COUNT    (100)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (683)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   696,  375,  400,  439,  456,  456,  456,  456,  456,  456,
 /*    10 */   456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
 /*    20 */   456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
 /*    30 */   456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
 /*    40 */   456,  456,  456,  456,  456,  456,  562,  441,  471,  440,
 /*    50 */   517,  403,  696,  696,  696,  477,  627,  640,  640,  640,
 /*    60 */   390,  390,  390,  573,  671,  672,  557,  414,  658,  658,
 /*    70 */   435,  435,  435,  435,  659,  659,  435,  659,  673,  677,
 /*    80 */   682,  683,   99,  117,  136,  466,  411,  468,  531,  466,
 /*    90 */   511,  493,  505,  493,  527,  505,  542,  527,  542,  466,
 /*   100 */   598,
};
#define YY_REDUCE_COUNT (54)
#define YY_REDUCE_MIN   (-62)
#define YY_REDUCE_MAX   (603)
static const short yy_reduce_ofst[] = {
 /*     0 */   322,  -62,  -41,  -21,   -2,   17,   36,   55,   74,   91,
 /*    10 */   108,  125,  142,  159,  176,  193,  210,  227,  244,  261,
 /*    20 */   278,  295,  361,  417,  430,  442,  469,  480,  489,  518,
 /*    30 */   526,  536,  544,  552,  559,  502,  568,  316,  341,  584,
 /*    40 */   381,  574,  589,  593,  597,  603,  326,  332,  332,  -57,
 /*    50 */   332,  -34,  -15,    4,   23,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   246,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    10 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    20 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    30 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    40 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    50 */   243,  243,  315,  315,  315,  259,  250,  277,  276,  275,
 /*    60 */   266,  265,  264,  243,  243,  243,  243,  288,  279,  278,
 /*    70 */   274,  273,  272,  271,  269,  268,  270,  267,  243,  243,
 /*    80 */   243,  243,  243,  243,  243,  320,  319,  243,  243,  312,
 /*    90 */   321,  287,  285,  286,  283,  284,  281,  282,  280,  311,
 /*   100 */   243,
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
  /*   20 */ "INCREMENT",
  /*   21 */ "DECREMENT",
  /*   22 */ "POW",
  /*   23 */ "MINUS",
  /*   24 */ "BITWISE_INVERT",
  /*   25 */ "INVERT",
  /*   26 */ "SIZEOF",
  /*   27 */ "MULTIPLY",
  /*   28 */ "DIVIDE",
  /*   29 */ "REMAINDER",
  /*   30 */ "PLUS",
  /*   31 */ "BITWISE_SHIFT_LEFT",
  /*   32 */ "BITWISE_SHIFT_RIGHT",
  /*   33 */ "LESS_THAN",
  /*   34 */ "GREATER_THAN",
  /*   35 */ "LESS_THAN_OR_EQUALS",
  /*   36 */ "GREATER_THAN_OR_EQUALS",
  /*   37 */ "NOT_EQUALS",
  /*   38 */ "BITWISE_AND",
  /*   39 */ "BITWISE_XOR",
  /*   40 */ "BITWISE_OR",
  /*   41 */ "AND",
  /*   42 */ "OR",
  /*   43 */ "QUESTION_MARK",
  /*   44 */ "COLON",
  /*   45 */ "ASSIGN",
  /*   46 */ "ASSIGN_MULTIPLY",
  /*   47 */ "ASSIGN_DIVIDE",
  /*   48 */ "ASSIGN_REMAINDER",
  /*   49 */ "ASSIGN_PLUS",
  /*   50 */ "ASSIGN_MINUS",
  /*   51 */ "ASSIGN_BITWISE_SHIFT_LEFT",
  /*   52 */ "ASSIGN_BITWISE_SHIFT_RIGHT",
  /*   53 */ "ASSIGN_BITWISE_AND",
  /*   54 */ "ASSIGN_BITWISE_XOR",
  /*   55 */ "ASSIGN_BITWISE_OR",
  /*   56 */ "root",
  /*   57 */ "definition_list",
  /*   58 */ "definition",
  /*   59 */ "statement_list",
  /*   60 */ "formal_parameters",
  /*   61 */ "declaration",
  /*   62 */ "actual_parameters",
  /*   63 */ "actual_parameter",
  /*   64 */ "expression",
  /*   65 */ "statement",
  /*   66 */ "simple_expression",
  /*   67 */ "postfix_expression",
  /*   68 */ "pow_expression",
  /*   69 */ "unary_expression",
  /*   70 */ "cast_expression",
  /*   71 */ "multiplicative_expression",
  /*   72 */ "additive_expression",
  /*   73 */ "bitwise_shift_expression",
  /*   74 */ "comparison_expression",
  /*   75 */ "equality_expression",
  /*   76 */ "bitwise_and_expression",
  /*   77 */ "bitwise_xor_expression",
  /*   78 */ "bitwise_or_expression",
  /*   79 */ "and_expression",
  /*   80 */ "or_expression",
  /*   81 */ "ternary_expression",
  /*   82 */ "assignment_expression",
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
 /*   4 */ "pow_expression ::= postfix_expression",
 /*   5 */ "pow_expression ::= postfix_expression POW pow_expression",
 /*   6 */ "pow_expression ::= INCREMENT unary_expression",
 /*   7 */ "pow_expression ::= DECREMENT unary_expression",
 /*   8 */ "unary_expression ::= pow_expression",
 /*   9 */ "unary_expression ::= MINUS unary_expression",
 /*  10 */ "unary_expression ::= BITWISE_INVERT unary_expression",
 /*  11 */ "unary_expression ::= INVERT unary_expression",
 /*  12 */ "unary_expression ::= SIZEOF unary_expression",
 /*  13 */ "cast_expression ::= unary_expression",
 /*  14 */ "multiplicative_expression ::= cast_expression",
 /*  15 */ "multiplicative_expression ::= multiplicative_expression MULTIPLY cast_expression",
 /*  16 */ "multiplicative_expression ::= multiplicative_expression DIVIDE cast_expression",
 /*  17 */ "multiplicative_expression ::= multiplicative_expression REMAINDER cast_expression",
 /*  18 */ "additive_expression ::= multiplicative_expression",
 /*  19 */ "additive_expression ::= additive_expression PLUS multiplicative_expression",
 /*  20 */ "additive_expression ::= additive_expression MINUS multiplicative_expression",
 /*  21 */ "bitwise_shift_expression ::= additive_expression",
 /*  22 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression",
 /*  23 */ "bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression",
 /*  24 */ "comparison_expression ::= bitwise_shift_expression",
 /*  25 */ "comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression",
 /*  26 */ "comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression",
 /*  27 */ "comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression",
 /*  28 */ "comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression",
 /*  29 */ "equality_expression ::= comparison_expression",
 /*  30 */ "equality_expression ::= equality_expression EQUALS comparison_expression",
 /*  31 */ "equality_expression ::= equality_expression NOT_EQUALS comparison_expression",
 /*  32 */ "bitwise_and_expression ::= equality_expression",
 /*  33 */ "bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression",
 /*  34 */ "bitwise_xor_expression ::= bitwise_and_expression",
 /*  35 */ "bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression",
 /*  36 */ "bitwise_or_expression ::= bitwise_xor_expression",
 /*  37 */ "bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression",
 /*  38 */ "and_expression ::= bitwise_or_expression",
 /*  39 */ "and_expression ::= and_expression AND bitwise_or_expression",
 /*  40 */ "or_expression ::= and_expression",
 /*  41 */ "or_expression ::= or_expression OR and_expression",
 /*  42 */ "ternary_expression ::= or_expression",
 /*  43 */ "ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression",
 /*  44 */ "assignment_expression ::= ternary_expression",
 /*  45 */ "assignment_expression ::= unary_expression ASSIGN assignment_expression",
 /*  46 */ "assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression",
 /*  47 */ "assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression",
 /*  48 */ "assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression",
 /*  49 */ "assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression",
 /*  50 */ "assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression",
 /*  51 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression",
 /*  52 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression",
 /*  53 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression",
 /*  54 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression",
 /*  55 */ "assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression",
 /*  56 */ "expression ::= assignment_expression",
 /*  57 */ "expression ::= expression COMMA assignment_expression",
 /*  58 */ "root ::= definition_list",
 /*  59 */ "definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  60 */ "declaration ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE",
 /*  61 */ "declaration ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  62 */ "declaration ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE",
 /*  63 */ "formal_parameters ::= ID",
 /*  64 */ "formal_parameters ::= formal_parameters COMMA ID",
 /*  65 */ "actual_parameter ::= expression",
 /*  66 */ "actual_parameter ::= ID EQUALS expression",
 /*  67 */ "actual_parameters ::= actual_parameter",
 /*  68 */ "actual_parameters ::= actual_parameters COMMA actual_parameter",
 /*  69 */ "statement_list ::=",
 /*  70 */ "statement_list ::= statement_list statement",
 /*  71 */ "statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  72 */ "statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  73 */ "statement ::= ID ID SEMICOLON",
 /*  74 */ "statement ::= ID ID SEMICOLON IF expression",
 /*  75 */ "simple_expression ::= ID",
 /*  76 */ "simple_expression ::= INT_V",
 /*  77 */ "simple_expression ::= FLOAT_V",
 /*  78 */ "simple_expression ::= STRING_V",
 /*  79 */ "simple_expression ::= TRUE",
 /*  80 */ "simple_expression ::= FALSE",
 /*  81 */ "simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS",
 /*  82 */ "postfix_expression ::= simple_expression",
 /*  83 */ "postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET",
 /*  84 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS",
 /*  85 */ "postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS",
 /*  86 */ "postfix_expression ::= postfix_expression DOT ID",
 /*  87 */ "postfix_expression ::= postfix_expression INCREMENT",
 /*  88 */ "postfix_expression ::= postfix_expression DECREMENT",
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
    case 20: /* INCREMENT */
    case 21: /* DECREMENT */
    case 22: /* POW */
    case 23: /* MINUS */
    case 24: /* BITWISE_INVERT */
    case 25: /* INVERT */
    case 26: /* SIZEOF */
    case 27: /* MULTIPLY */
    case 28: /* DIVIDE */
    case 29: /* REMAINDER */
    case 30: /* PLUS */
    case 31: /* BITWISE_SHIFT_LEFT */
    case 32: /* BITWISE_SHIFT_RIGHT */
    case 33: /* LESS_THAN */
    case 34: /* GREATER_THAN */
    case 35: /* LESS_THAN_OR_EQUALS */
    case 36: /* GREATER_THAN_OR_EQUALS */
    case 37: /* NOT_EQUALS */
    case 38: /* BITWISE_AND */
    case 39: /* BITWISE_XOR */
    case 40: /* BITWISE_OR */
    case 41: /* AND */
    case 42: /* OR */
    case 43: /* QUESTION_MARK */
    case 44: /* COLON */
    case 45: /* ASSIGN */
    case 46: /* ASSIGN_MULTIPLY */
    case 47: /* ASSIGN_DIVIDE */
    case 48: /* ASSIGN_REMAINDER */
    case 49: /* ASSIGN_PLUS */
    case 50: /* ASSIGN_MINUS */
    case 51: /* ASSIGN_BITWISE_SHIFT_LEFT */
    case 52: /* ASSIGN_BITWISE_SHIFT_RIGHT */
    case 53: /* ASSIGN_BITWISE_AND */
    case 54: /* ASSIGN_BITWISE_XOR */
    case 55: /* ASSIGN_BITWISE_OR */
{
#line 6 "zl_parser.y"

    // TODO

#line 857 "zl_parser.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 56: /* root */
    case 57: /* definition_list */
    case 58: /* definition */
    case 59: /* statement_list */
    case 60: /* formal_parameters */
    case 61: /* declaration */
    case 62: /* actual_parameters */
    case 63: /* actual_parameter */
    case 64: /* expression */
    case 65: /* statement */
    case 66: /* simple_expression */
    case 67: /* postfix_expression */
    case 68: /* pow_expression */
    case 69: /* unary_expression */
    case 70: /* cast_expression */
    case 71: /* multiplicative_expression */
    case 72: /* additive_expression */
    case 73: /* bitwise_shift_expression */
    case 74: /* comparison_expression */
    case 75: /* equality_expression */
    case 76: /* bitwise_and_expression */
    case 77: /* bitwise_xor_expression */
    case 78: /* bitwise_or_expression */
    case 79: /* and_expression */
    case 80: /* or_expression */
    case 81: /* ternary_expression */
    case 82: /* assignment_expression */
{
#line 33 "zl_parser.y"

    ast_defaultDestructor((yypminor->yy122));

#line 893 "zl_parser.c"
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
#line 1117 "zl_parser.c"
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
  {   57,    0 }, /* (0) definition_list ::= */
  {   57,   -2 }, /* (1) definition_list ::= definition_list definition */
  {   58,   -5 }, /* (2) definition ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   58,   -7 }, /* (3) definition ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   68,   -1 }, /* (4) pow_expression ::= postfix_expression */
  {   68,   -3 }, /* (5) pow_expression ::= postfix_expression POW pow_expression */
  {   68,   -2 }, /* (6) pow_expression ::= INCREMENT unary_expression */
  {   68,   -2 }, /* (7) pow_expression ::= DECREMENT unary_expression */
  {   69,   -1 }, /* (8) unary_expression ::= pow_expression */
  {   69,   -2 }, /* (9) unary_expression ::= MINUS unary_expression */
  {   69,   -2 }, /* (10) unary_expression ::= BITWISE_INVERT unary_expression */
  {   69,   -2 }, /* (11) unary_expression ::= INVERT unary_expression */
  {   69,   -2 }, /* (12) unary_expression ::= SIZEOF unary_expression */
  {   70,   -1 }, /* (13) cast_expression ::= unary_expression */
  {   71,   -1 }, /* (14) multiplicative_expression ::= cast_expression */
  {   71,   -3 }, /* (15) multiplicative_expression ::= multiplicative_expression MULTIPLY cast_expression */
  {   71,   -3 }, /* (16) multiplicative_expression ::= multiplicative_expression DIVIDE cast_expression */
  {   71,   -3 }, /* (17) multiplicative_expression ::= multiplicative_expression REMAINDER cast_expression */
  {   72,   -1 }, /* (18) additive_expression ::= multiplicative_expression */
  {   72,   -3 }, /* (19) additive_expression ::= additive_expression PLUS multiplicative_expression */
  {   72,   -3 }, /* (20) additive_expression ::= additive_expression MINUS multiplicative_expression */
  {   73,   -1 }, /* (21) bitwise_shift_expression ::= additive_expression */
  {   73,   -3 }, /* (22) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
  {   73,   -3 }, /* (23) bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
  {   74,   -1 }, /* (24) comparison_expression ::= bitwise_shift_expression */
  {   74,   -3 }, /* (25) comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
  {   74,   -3 }, /* (26) comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
  {   74,   -3 }, /* (27) comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
  {   74,   -3 }, /* (28) comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
  {   75,   -1 }, /* (29) equality_expression ::= comparison_expression */
  {   75,   -3 }, /* (30) equality_expression ::= equality_expression EQUALS comparison_expression */
  {   75,   -3 }, /* (31) equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
  {   76,   -1 }, /* (32) bitwise_and_expression ::= equality_expression */
  {   76,   -3 }, /* (33) bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
  {   77,   -1 }, /* (34) bitwise_xor_expression ::= bitwise_and_expression */
  {   77,   -3 }, /* (35) bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
  {   78,   -1 }, /* (36) bitwise_or_expression ::= bitwise_xor_expression */
  {   78,   -3 }, /* (37) bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
  {   79,   -1 }, /* (38) and_expression ::= bitwise_or_expression */
  {   79,   -3 }, /* (39) and_expression ::= and_expression AND bitwise_or_expression */
  {   80,   -1 }, /* (40) or_expression ::= and_expression */
  {   80,   -3 }, /* (41) or_expression ::= or_expression OR and_expression */
  {   81,   -1 }, /* (42) ternary_expression ::= or_expression */
  {   81,   -5 }, /* (43) ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
  {   82,   -1 }, /* (44) assignment_expression ::= ternary_expression */
  {   82,   -3 }, /* (45) assignment_expression ::= unary_expression ASSIGN assignment_expression */
  {   82,   -3 }, /* (46) assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
  {   82,   -3 }, /* (47) assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
  {   82,   -3 }, /* (48) assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
  {   82,   -3 }, /* (49) assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
  {   82,   -3 }, /* (50) assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
  {   82,   -3 }, /* (51) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
  {   82,   -3 }, /* (52) assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
  {   82,   -3 }, /* (53) assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
  {   82,   -3 }, /* (54) assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
  {   82,   -3 }, /* (55) assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
  {   64,   -1 }, /* (56) expression ::= assignment_expression */
  {   64,   -3 }, /* (57) expression ::= expression COMMA assignment_expression */
  {   56,   -1 }, /* (58) root ::= definition_list */
  {   58,   -8 }, /* (59) definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   61,   -5 }, /* (60) declaration ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
  {   61,   -7 }, /* (61) declaration ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   61,   -8 }, /* (62) declaration ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
  {   60,   -1 }, /* (63) formal_parameters ::= ID */
  {   60,   -3 }, /* (64) formal_parameters ::= formal_parameters COMMA ID */
  {   63,   -1 }, /* (65) actual_parameter ::= expression */
  {   63,   -3 }, /* (66) actual_parameter ::= ID EQUALS expression */
  {   62,   -1 }, /* (67) actual_parameters ::= actual_parameter */
  {   62,   -3 }, /* (68) actual_parameters ::= actual_parameters COMMA actual_parameter */
  {   59,    0 }, /* (69) statement_list ::= */
  {   59,   -2 }, /* (70) statement_list ::= statement_list statement */
  {   65,   -3 }, /* (71) statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   65,   -4 }, /* (72) statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   65,   -3 }, /* (73) statement ::= ID ID SEMICOLON */
  {   65,   -5 }, /* (74) statement ::= ID ID SEMICOLON IF expression */
  {   66,   -1 }, /* (75) simple_expression ::= ID */
  {   66,   -1 }, /* (76) simple_expression ::= INT_V */
  {   66,   -1 }, /* (77) simple_expression ::= FLOAT_V */
  {   66,   -1 }, /* (78) simple_expression ::= STRING_V */
  {   66,   -1 }, /* (79) simple_expression ::= TRUE */
  {   66,   -1 }, /* (80) simple_expression ::= FALSE */
  {   66,   -3 }, /* (81) simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
  {   67,   -1 }, /* (82) postfix_expression ::= simple_expression */
  {   67,   -4 }, /* (83) postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
  {   67,   -3 }, /* (84) postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
  {   67,   -4 }, /* (85) postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
  {   67,   -3 }, /* (86) postfix_expression ::= postfix_expression DOT ID */
  {   67,   -2 }, /* (87) postfix_expression ::= postfix_expression INCREMENT */
  {   67,   -2 }, /* (88) postfix_expression ::= postfix_expression DECREMENT */
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
#line 1371 "zl_parser.c"
        break;
      case 1: /* definition_list ::= definition_list definition */
#line 55 "zl_parser.y"
{ yymsp[-1].minor.yy108.push_back(yymsp[0].minor.yy12); }
#line 1376 "zl_parser.c"
        break;
      case 2: /* definition ::= FN ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-4].minor);
#line 59 "zl_parser.y"
{ yymsp[-4].minor.yy12 = new Definition(yymsp[-1].minor.yy0); }
#line 1382 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 3: /* definition ::= FN ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-6].minor);
#line 60 "zl_parser.y"
{ yymsp[-6].minor.yy12 = new Definition(yymsp[-1].minor.yy0); }
#line 1392 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 4: /* pow_expression ::= postfix_expression */
#line 109 "zl_parser.y"
{ yylhsminor.yy122 = yymsp[0].minor.yy0; }
#line 1403 "zl_parser.c"
  yymsp[0].minor.yy122 = yylhsminor.yy122;
        break;
      case 5: /* pow_expression ::= postfix_expression POW pow_expression */
#line 110 "zl_parser.y"
{ // a ** b // right-associative => right recursion, this is not good
    AST_DEBUG("Pow expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_POW, yymsp[-2].minor.yy0, yymsp[0].minor.yy122);
}
#line 1412 "zl_parser.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 6: /* pow_expression ::= INCREMENT unary_expression */
{  yy_destructor(yypParser,20,&yymsp[-1].minor);
#line 114 "zl_parser.y"
{
    // pre-increment
    AST_DEBUG("Pre increment expression.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_PRE_INCREMENT, yymsp[0].minor.yy122);
}
#line 1424 "zl_parser.c"
}
        break;
      case 7: /* pow_expression ::= DECREMENT unary_expression */
{  yy_destructor(yypParser,21,&yymsp[-1].minor);
#line 119 "zl_parser.y"
{
    // pre-decrement
    AST_DEBUG("Pre decrement expression.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_PRE_DECREMENT, yymsp[0].minor.yy122);
}
#line 1435 "zl_parser.c"
}
        break;
      case 8: /* unary_expression ::= pow_expression */
      case 13: /* cast_expression ::= unary_expression */ yytestcase(yyruleno==13);
      case 14: /* multiplicative_expression ::= cast_expression */ yytestcase(yyruleno==14);
      case 18: /* additive_expression ::= multiplicative_expression */ yytestcase(yyruleno==18);
      case 21: /* bitwise_shift_expression ::= additive_expression */ yytestcase(yyruleno==21);
      case 24: /* comparison_expression ::= bitwise_shift_expression */ yytestcase(yyruleno==24);
      case 29: /* equality_expression ::= comparison_expression */ yytestcase(yyruleno==29);
      case 32: /* bitwise_and_expression ::= equality_expression */ yytestcase(yyruleno==32);
      case 34: /* bitwise_xor_expression ::= bitwise_and_expression */ yytestcase(yyruleno==34);
      case 36: /* bitwise_or_expression ::= bitwise_xor_expression */ yytestcase(yyruleno==36);
      case 38: /* and_expression ::= bitwise_or_expression */ yytestcase(yyruleno==38);
      case 40: /* or_expression ::= and_expression */ yytestcase(yyruleno==40);
      case 42: /* ternary_expression ::= or_expression */ yytestcase(yyruleno==42);
      case 44: /* assignment_expression ::= ternary_expression */ yytestcase(yyruleno==44);
      case 56: /* expression ::= assignment_expression */ yytestcase(yyruleno==56);
#line 127 "zl_parser.y"
{ yylhsminor.yy122 = yymsp[0].minor.yy122; }
#line 1455 "zl_parser.c"
  yymsp[0].minor.yy122 = yylhsminor.yy122;
        break;
      case 9: /* unary_expression ::= MINUS unary_expression */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 128 "zl_parser.y"
{ // - (unary)
    AST_DEBUG("Unary minus expression.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_MINUS, yymsp[0].minor.yy122);
}
#line 1465 "zl_parser.c"
}
        break;
      case 10: /* unary_expression ::= BITWISE_INVERT unary_expression */
{  yy_destructor(yypParser,24,&yymsp[-1].minor);
#line 132 "zl_parser.y"
{ // ~ (unary)
    AST_DEBUG("Unary bitwise invert expression.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_BITWISE_INVERT, yymsp[0].minor.yy122);
}
#line 1475 "zl_parser.c"
}
        break;
      case 11: /* unary_expression ::= INVERT unary_expression */
{  yy_destructor(yypParser,25,&yymsp[-1].minor);
#line 136 "zl_parser.y"
{ // ! (unary)
    AST_DEBUG("Unary logic invert.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_INVERT, yymsp[0].minor.yy122);
}
#line 1485 "zl_parser.c"
}
        break;
      case 12: /* unary_expression ::= SIZEOF unary_expression */
{  yy_destructor(yypParser,26,&yymsp[-1].minor);
#line 140 "zl_parser.y"
{ // sizeof a
    AST_DEBUG("Sizeof var expression.");
    yymsp[-1].minor.yy122 = (base_node_t*)ast_newUnaryExpressionNode(N_EXPRESSION_U_SIZEOF_VAR, yymsp[0].minor.yy122);
}
#line 1495 "zl_parser.c"
}
        break;
      case 15: /* multiplicative_expression ::= multiplicative_expression MULTIPLY cast_expression */
#line 160 "zl_parser.y"
{ // a * b
    AST_DEBUG("Multiply expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_MULTIPLY, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1504 "zl_parser.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 16: /* multiplicative_expression ::= multiplicative_expression DIVIDE cast_expression */
#line 164 "zl_parser.y"
{ // a / b
    AST_DEBUG("Divide expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_DIVIDE, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1514 "zl_parser.c"
  yy_destructor(yypParser,28,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 17: /* multiplicative_expression ::= multiplicative_expression REMAINDER cast_expression */
#line 168 "zl_parser.y"
{ // a % b
    AST_DEBUG("Remainder expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_REMAINDER, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1524 "zl_parser.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 19: /* additive_expression ::= additive_expression PLUS multiplicative_expression */
#line 176 "zl_parser.y"
{ // a + b
    AST_DEBUG("Plus expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_PLUS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1534 "zl_parser.c"
  yy_destructor(yypParser,30,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 20: /* additive_expression ::= additive_expression MINUS multiplicative_expression */
#line 180 "zl_parser.y"
{ // a - b
    AST_DEBUG("Minus expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_MINUS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1544 "zl_parser.c"
  yy_destructor(yypParser,23,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 22: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_LEFT additive_expression */
#line 188 "zl_parser.y"
{ // a << b
    AST_DEBUG("Bitwise shift left expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1554 "zl_parser.c"
  yy_destructor(yypParser,31,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 23: /* bitwise_shift_expression ::= bitwise_shift_expression BITWISE_SHIFT_RIGHT additive_expression */
#line 192 "zl_parser.y"
{ // a >> b
    AST_DEBUG("Bitwise shift right expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1564 "zl_parser.c"
  yy_destructor(yypParser,32,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 25: /* comparison_expression ::= comparison_expression LESS_THAN bitwise_shift_expression */
#line 200 "zl_parser.y"
{ // a < b
    AST_DEBUG("Less than expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_LESS_THAN, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1574 "zl_parser.c"
  yy_destructor(yypParser,33,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 26: /* comparison_expression ::= comparison_expression GREATER_THAN bitwise_shift_expression */
#line 204 "zl_parser.y"
{ // a > b
    AST_DEBUG("Greater than expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_GREATER_THAN, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1584 "zl_parser.c"
  yy_destructor(yypParser,34,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 27: /* comparison_expression ::= comparison_expression LESS_THAN_OR_EQUALS bitwise_shift_expression */
#line 208 "zl_parser.y"
{ // a <= b
    AST_DEBUG("Less than or equals expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_LESS_THAN_OR_EQUALS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1594 "zl_parser.c"
  yy_destructor(yypParser,35,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 28: /* comparison_expression ::= comparison_expression GREATER_THAN_OR_EQUALS bitwise_shift_expression */
#line 212 "zl_parser.y"
{ // a >= b
    AST_DEBUG("Greater than or equals expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_GREATER_THAN_OR_EQUALS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1604 "zl_parser.c"
  yy_destructor(yypParser,36,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 30: /* equality_expression ::= equality_expression EQUALS comparison_expression */
#line 220 "zl_parser.y"
{ // a == b
    AST_DEBUG("Equals expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_EQUALS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1614 "zl_parser.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 31: /* equality_expression ::= equality_expression NOT_EQUALS comparison_expression */
#line 224 "zl_parser.y"
{ // a != b
    AST_DEBUG("Not equals expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_NOT_EQUALS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1624 "zl_parser.c"
  yy_destructor(yypParser,37,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 33: /* bitwise_and_expression ::= bitwise_and_expression BITWISE_AND equality_expression */
#line 232 "zl_parser.y"
{ // a & b
    AST_DEBUG("Bitwise and expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_AND, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1634 "zl_parser.c"
  yy_destructor(yypParser,38,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 35: /* bitwise_xor_expression ::= bitwise_xor_expression BITWISE_XOR bitwise_and_expression */
#line 240 "zl_parser.y"
{ // a ^ b
    AST_DEBUG("Bitwise xor expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_XOR, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1644 "zl_parser.c"
  yy_destructor(yypParser,39,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 37: /* bitwise_or_expression ::= bitwise_or_expression BITWISE_OR bitwise_xor_expression */
#line 248 "zl_parser.y"
{ // a | b
    AST_DEBUG("Bitwise or expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_BITWISE_OR, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1654 "zl_parser.c"
  yy_destructor(yypParser,40,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 39: /* and_expression ::= and_expression AND bitwise_or_expression */
#line 256 "zl_parser.y"
{ // a && b
    AST_DEBUG("And expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_AND, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1664 "zl_parser.c"
  yy_destructor(yypParser,41,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 41: /* or_expression ::= or_expression OR and_expression */
#line 264 "zl_parser.y"
{ // a || b
    AST_DEBUG("Or expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_OR, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1674 "zl_parser.c"
  yy_destructor(yypParser,42,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 43: /* ternary_expression ::= or_expression QUESTION_MARK expression COLON ternary_expression */
#line 272 "zl_parser.y"
{ // a ? b : c
    AST_DEBUG("Ternary expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newTernaryExpressionNode(yymsp[-4].minor.yy122, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1684 "zl_parser.c"
  yy_destructor(yypParser,43,&yymsp[-3].minor);
  yy_destructor(yypParser,44,&yymsp[-1].minor);
  yymsp[-4].minor.yy122 = yylhsminor.yy122;
        break;
      case 45: /* assignment_expression ::= unary_expression ASSIGN assignment_expression */
#line 280 "zl_parser.y"
{ // a = b
    AST_DEBUG("Assign expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1695 "zl_parser.c"
  yy_destructor(yypParser,45,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 46: /* assignment_expression ::= unary_expression ASSIGN_MULTIPLY assignment_expression */
#line 284 "zl_parser.y"
{ // a *= b
    AST_DEBUG("Assign multiply expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_MULTIPLY, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1705 "zl_parser.c"
  yy_destructor(yypParser,46,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 47: /* assignment_expression ::= unary_expression ASSIGN_DIVIDE assignment_expression */
#line 288 "zl_parser.y"
{ // a /= b
    AST_DEBUG("Assign divide expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_DIVIDE, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1715 "zl_parser.c"
  yy_destructor(yypParser,47,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 48: /* assignment_expression ::= unary_expression ASSIGN_REMAINDER assignment_expression */
#line 292 "zl_parser.y"
{ // a %= b
    AST_DEBUG("Assign remainder expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_REMAINDER, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1725 "zl_parser.c"
  yy_destructor(yypParser,48,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 49: /* assignment_expression ::= unary_expression ASSIGN_PLUS assignment_expression */
#line 296 "zl_parser.y"
{ // a += b
    AST_DEBUG("Assign plus expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_PLUS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1735 "zl_parser.c"
  yy_destructor(yypParser,49,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 50: /* assignment_expression ::= unary_expression ASSIGN_MINUS assignment_expression */
#line 300 "zl_parser.y"
{ // a -= b
    AST_DEBUG("Assign minus expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_MINUS, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1745 "zl_parser.c"
  yy_destructor(yypParser,50,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 51: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_LEFT assignment_expression */
#line 304 "zl_parser.y"
{ // a <<= b
    AST_DEBUG("Assign bitwise shift left expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_SHIFT_LEFT, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1755 "zl_parser.c"
  yy_destructor(yypParser,51,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 52: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_SHIFT_RIGHT assignment_expression */
#line 308 "zl_parser.y"
{ // a >>= b
    AST_DEBUG("Assign bitwise shift right expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_SHIFT_RIGHT, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1765 "zl_parser.c"
  yy_destructor(yypParser,52,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 53: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_AND assignment_expression */
#line 312 "zl_parser.y"
{ // a &= b
    AST_DEBUG("Assign bitwise and expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_AND, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1775 "zl_parser.c"
  yy_destructor(yypParser,53,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 54: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_XOR assignment_expression */
#line 316 "zl_parser.y"
{ // a ^= b
    AST_DEBUG("Assign bitwise xor expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_XOR, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1785 "zl_parser.c"
  yy_destructor(yypParser,54,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 55: /* assignment_expression ::= unary_expression ASSIGN_BITWISE_OR assignment_expression */
#line 320 "zl_parser.y"
{ // a |= b
    AST_DEBUG("Assign bitwise or expression.");
    yylhsminor.yy122 = (base_node_t*)ast_newBinaryExpressionNode(N_EXPRESSION_ASSIGN_BITWISE_OR, yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1795 "zl_parser.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 57: /* expression ::= expression COMMA assignment_expression */
#line 328 "zl_parser.y"
{
    yylhsminor.yy122 = (base_node_t*)ast_newCommaExpressionNode(yymsp[-2].minor.yy122, yymsp[0].minor.yy122);
}
#line 1804 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yymsp[-2].minor.yy122 = yylhsminor.yy122;
        break;
      case 58: /* root ::= definition_list */
{  yy_destructor(yypParser,57,&yymsp[0].minor);
#line 51 "zl_parser.y"
{
}
#line 1813 "zl_parser.c"
}
        break;
      case 59: /* definition ::= FN ID LEFT_PARENTHESIS formal_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,1,&yymsp[-7].minor);
#line 61 "zl_parser.y"
{
}
#line 1821 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-6].minor);
  yy_destructor(yypParser,5,&yymsp[-5].minor);
  yy_destructor(yypParser,60,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 60: /* declaration ::= ON ID LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-4].minor);
#line 64 "zl_parser.y"
{
}
#line 1836 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 61: /* declaration ::= ON ID LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-6].minor);
#line 65 "zl_parser.y"
{
}
#line 1848 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 62: /* declaration ::= ON ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS LEFT_BRACE statement_list RIGHT_BRACE */
{  yy_destructor(yypParser,7,&yymsp[-7].minor);
#line 66 "zl_parser.y"
{
}
#line 1862 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-6].minor);
  yy_destructor(yypParser,5,&yymsp[-5].minor);
  yy_destructor(yypParser,62,&yymsp[-4].minor);
  yy_destructor(yypParser,6,&yymsp[-3].minor);
  yy_destructor(yypParser,3,&yymsp[-2].minor);
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yy_destructor(yypParser,4,&yymsp[0].minor);
}
        break;
      case 63: /* formal_parameters ::= ID */
{  yy_destructor(yypParser,2,&yymsp[0].minor);
#line 68 "zl_parser.y"
{
}
#line 1877 "zl_parser.c"
}
        break;
      case 64: /* formal_parameters ::= formal_parameters COMMA ID */
{  yy_destructor(yypParser,60,&yymsp[-2].minor);
#line 69 "zl_parser.y"
{
}
#line 1885 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 65: /* actual_parameter ::= expression */
{  yy_destructor(yypParser,64,&yymsp[0].minor);
#line 71 "zl_parser.y"
{
}
#line 1895 "zl_parser.c"
}
        break;
      case 66: /* actual_parameter ::= ID EQUALS expression */
{  yy_destructor(yypParser,2,&yymsp[-2].minor);
#line 72 "zl_parser.y"
{
}
#line 1903 "zl_parser.c"
  yy_destructor(yypParser,9,&yymsp[-1].minor);
  yy_destructor(yypParser,64,&yymsp[0].minor);
}
        break;
      case 67: /* actual_parameters ::= actual_parameter */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 74 "zl_parser.y"
{
}
#line 1913 "zl_parser.c"
}
        break;
      case 68: /* actual_parameters ::= actual_parameters COMMA actual_parameter */
{  yy_destructor(yypParser,62,&yymsp[-2].minor);
#line 75 "zl_parser.y"
{
}
#line 1921 "zl_parser.c"
  yy_destructor(yypParser,8,&yymsp[-1].minor);
  yy_destructor(yypParser,63,&yymsp[0].minor);
}
        break;
      case 70: /* statement_list ::= statement_list statement */
{  yy_destructor(yypParser,59,&yymsp[-1].minor);
#line 78 "zl_parser.y"
{
}
#line 1931 "zl_parser.c"
  yy_destructor(yypParser,65,&yymsp[0].minor);
}
        break;
      case 71: /* statement ::= ID LEFT_PARENTHESIS RIGHT_PARENTHESIS */
{  yy_destructor(yypParser,2,&yymsp[-2].minor);
#line 82 "zl_parser.y"
{
}
#line 1940 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 72: /* statement ::= ID LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
{  yy_destructor(yypParser,2,&yymsp[-3].minor);
#line 83 "zl_parser.y"
{
}
#line 1950 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,62,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 73: /* statement ::= ID ID SEMICOLON */
{  yy_destructor(yypParser,2,&yymsp[-2].minor);
#line 86 "zl_parser.y"
{
}
#line 1961 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-1].minor);
  yy_destructor(yypParser,10,&yymsp[0].minor);
}
        break;
      case 74: /* statement ::= ID ID SEMICOLON IF expression */
{  yy_destructor(yypParser,2,&yymsp[-4].minor);
#line 87 "zl_parser.y"
{
}
#line 1971 "zl_parser.c"
  yy_destructor(yypParser,2,&yymsp[-3].minor);
  yy_destructor(yypParser,10,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[-1].minor);
  yy_destructor(yypParser,64,&yymsp[0].minor);
}
        break;
      case 75: /* simple_expression ::= ID */
      case 76: /* simple_expression ::= INT_V */ yytestcase(yyruleno==76);
      case 77: /* simple_expression ::= FLOAT_V */ yytestcase(yyruleno==77);
      case 78: /* simple_expression ::= STRING_V */ yytestcase(yyruleno==78);
      case 82: /* postfix_expression ::= simple_expression */ yytestcase(yyruleno==82);
#line 90 "zl_parser.y"
{
}
#line 1986 "zl_parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 79: /* simple_expression ::= TRUE */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 94 "zl_parser.y"
{
}
#line 1994 "zl_parser.c"
}
        break;
      case 80: /* simple_expression ::= FALSE */
{  yy_destructor(yypParser,16,&yymsp[0].minor);
#line 95 "zl_parser.y"
{
}
#line 2002 "zl_parser.c"
}
        break;
      case 81: /* simple_expression ::= LEFT_PARENTHESIS expression RIGHT_PARENTHESIS */
{  yy_destructor(yypParser,5,&yymsp[-2].minor);
#line 96 "zl_parser.y"
{
}
#line 2010 "zl_parser.c"
  yy_destructor(yypParser,6,&yymsp[0].minor);
}
        break;
      case 83: /* postfix_expression ::= postfix_expression LEFT_BRACKET expression RIGHT_BRACKET */
#line 100 "zl_parser.y"
{
}
#line 2018 "zl_parser.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,18,&yymsp[0].minor);
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 84: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS RIGHT_PARENTHESIS */
#line 101 "zl_parser.y"
{
}
#line 2027 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 85: /* postfix_expression ::= postfix_expression LEFT_PARENTHESIS actual_parameters RIGHT_PARENTHESIS */
#line 102 "zl_parser.y"
{
}
#line 2036 "zl_parser.c"
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,6,&yymsp[0].minor);
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 86: /* postfix_expression ::= postfix_expression DOT ID */
#line 103 "zl_parser.y"
{
}
#line 2045 "zl_parser.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 87: /* postfix_expression ::= postfix_expression INCREMENT */
#line 104 "zl_parser.y"
{
}
#line 2053 "zl_parser.c"
  yy_destructor(yypParser,20,&yymsp[0].minor);
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 88: /* postfix_expression ::= postfix_expression DECREMENT */
#line 105 "zl_parser.y"
{
}
#line 2061 "zl_parser.c"
  yy_destructor(yypParser,21,&yymsp[0].minor);
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (69) statement_list ::= */ yytestcase(yyruleno==69);
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
#line 2111 "zl_parser.c"
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
#line 2133 "zl_parser.c"
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
#line 2162 "zl_parser.c"
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
