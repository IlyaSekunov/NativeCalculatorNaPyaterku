#ifndef CONSTANTS
#define CONSTANTS

#define size 10000
#define OPERATOR(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/')
#define OPERATOR_HIGH_PRIORITY(x) ((x) == '*' || (x) == '/')
#define OPERATOR_LOW_PRIORITY(x) ((x) == '+' || (x) == '-')

#define REAL_NUMBER 0
#define COMPLEX_NUMBER 1
#define FUNCTION 2
#define SIN 3
#define COS 4
#define TG 5
#define CTG 6
#define LOG 7
#define LN 8
#define SQRT 9
#define POW 10
#define ABS 11
#define EXP 12
#define REAL 13
#define IMAG 14
#define MAG 15
#define PHASE 16

#endif
