#ifndef CONSTANTS
#define CONSTANTS

#define IS_OPERATOR(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/' || (x) == '^')

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
#define POW '^'
#define ABS 12
#define EXP 13
#define REAL 14
#define IMAG 15
#define MAG 16
#define PHASE 17
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIV '/'

#define IS_FUNCTION(x) ((x) >= SIN && (x) <= PHASE)

#define INPUT_STRING_LEN 1000
#define OUTPUT_STRING_LEN 10000
#define VARIABLES_NAME_LEN 100
#define VARIABLES_DATA_LEN 900
#define COUNT_VARIABLES 100
#define INPUT_STRING_LEN 1000


#endif
