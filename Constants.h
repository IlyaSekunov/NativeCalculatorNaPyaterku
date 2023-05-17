#ifndef CONSTANTS
#define CONSTANTS

#define OPERATOR_HELP(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/' || (x) == '^')
#define OPERATOR_HIGH_PRIORITY(x) ((x) == '*' || (x) == '/' || (x) == '^')
#define OPERATOR_LOW_PRIORITY(x) ((x) == '+' || (x) == '-')

#define REAL_NUMBER 0
#define COMPLEX_NUMBER 1
#define OPERATOR 2
#define FUNCTION 3

#define SIN 4
#define COS 5
#define TG 6
#define CTG 7
#define LOG 8
#define LN 9
#define SQRT 10
#define POW 11
#define ABS 12
#define EXP 13
#define REAL 14
#define IMAG 15
#define MAG 16
#define PHASE 17
#define PLUS 18
#define MINUS 19
#define MULT 20
#define DIV 21
#define DEG 22

#define IS_FUNCTION(x) ((x) >= SIN && (x) <= PHASE)
#define IS_OPERATOR(x) ((x) >= PLUS && (x) <= DEG)



#endif
