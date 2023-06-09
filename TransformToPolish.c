﻿#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include "Stack.h"
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "Constants.h"

RPNNode solveRPN(Stack* rpn);

int get_func_type(char* source, int* i) {
	if (source[*i] == 's') {
		if (source[++(*i)] == 'i') {
			++(*i);
			return SIN;
		}
		else {
			(*i) += 2;
			return SQRT;
		}
	}
	else if (source[*i] == 'c') {
		if (source[++(*i)] == 'o') {
			++(*i);
			return COS;
		}
		else {
			++(*i);
			return CTG;
		}
	}
	else if (source[*i] == 't') {
		++(*i);
		return TG;
	}
	else if (source[*i] == 'l') {
		if (source[++(*i)] == 'o') {
			++(*i);
			return LOG;
		}
		else return LN;
	}
	else if (source[*i] == 'p') {
		if (source[++(*i)] == 'o') {
			++(*i);
			return POW;
		}
		else {
			(*i) += 3;
			return PHASE;
		}
	}
	else if (source[*i] == 'a') {
		(*i) += 2;
		return ABS;
	}
	else if (source[*i] == 'e') {
		(*i) += 2;
		return EXP;
	}
	else if (source[*i] == 'r') {
		(*i) += 3;
		return REAL;
	}
	else if (source[*i] == 'i') {
		(*i) += 3;
		return IMAG;
	}
	else if (source[*i] == 'm') {
		(*i) += 2;
		return MAG;
	}
}


RPNNode get_number(int* i, char* source) {
	long double result = 0;
	int dot = 0, exp = 1, len = strlen(source);
	for (; (source[*i] >= '0' && source[*i] <= '9' || source[*i] == '.') && *i < len; ++(*i)) {
		if (source[*i] == '.') {
			dot = 1;
			continue;
		}
		if (dot == 0) {
			result = result * 10 + source[*i] - '0';
		}
		else {
			result += (source[*i] - '0') / pow(10, exp);
			++exp;
		}
	}
	RPNNode tmp;
	if (source[*i] == 'j') {
		tmp.type = COMPLEX_NUMBER;
		tmp.complex_number._Val[0] = 0;
		tmp.complex_number._Val[1] = result;
	}
	else {
		tmp.type = REAL_NUMBER;
		tmp.real_number = result;
		--(*i);
	}
	return tmp;
}

int priority(int op1, int op2) {
	if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-')) {
		return 1;
	}
	if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/' || op2 == '+' || op2 == '-')) {
		return 1;
	}
	if (op1 == '^' && (op2 == '^' || op2 == '*' || op2 == '/' || op2 == '+' || op2 == '-')) {
		return 1;
	}
	return 0;
}

void Transform_to_Polish(Stack* mainStack, char* source) {
	Stack operators;
	init_Stack(&operators);

	int len = strlen(source);

	for (int i = 0; i < len; ++i) {

		if (source[i] == ' ') continue;

		else if (source[i] == ',') {
			while (!operators.empty(operators) && operators.top(operators).function != '(') {
				mainStack->push(mainStack, operators.pop(&operators));
			}
		}

		else if (source[i] == '(') {
			RPNNode newNode;
			newNode.type = -1;
			newNode.function = '(';
			operators.push(&operators, newNode);
		}

		else if (source[i] == ')') {
			while (operators.top(operators).function != '(') {
				mainStack->push(mainStack, operators.pop(&operators));
			}
			operators.pop(&operators);

			if (operators.top(operators).type == FUNCTION) {
				mainStack->push(mainStack, operators.pop(&operators));
			}
		}

		else if (IS_OPERATOR(source[i])) {

			int j = i - 1;
			while (j > 0 && source[j] == ' ') --j;
			if (source[i] == '-' && (i == 0 || source[j] == '(')) {
				RPNNode help;
				help.type = REAL_NUMBER;
				help.real_number = -1;
				mainStack->push(mainStack, help);
				help.type = OPERATOR;
				help.function = '*';
				operators.push(&operators, help);
				continue;
			}
			while (!operators.empty(operators) && operators.top(operators).type == OPERATOR && priority(operators.top(operators).function, source[i])) {
				mainStack->push(mainStack, operators.pop(&operators));
			}
			RPNNode tmp;
			tmp.type = OPERATOR;
			tmp.function = source[i];
			operators.push(&operators, tmp);
		}

		else if (source[i] >= '0' && source[i] <= '9') {
			mainStack->push(mainStack, get_number(&i, source));
		}

		else if (source[i] == 'j' || source[i] == 'P') {
			RPNNode newNode;
			if (source[i] == 'j') {
				newNode.type = COMPLEX_NUMBER;
				newNode.complex_number._Val[0] = 0;
				newNode.complex_number._Val[1] = 1;
				mainStack->push(mainStack, newNode);
			}
			else if (source[i++] == 'P') {
				newNode.type = REAL_NUMBER;
				newNode.real_number = M_PI;
				mainStack->push(mainStack, newNode);
			}
		}

		else {
			RPNNode newNode;
			if (source[i] == 'e' && source[i + 1] != 'x') {
				newNode.type = REAL_NUMBER;
				newNode.real_number = M_E;
				mainStack->push(mainStack, newNode);
			}
			else {
				newNode.type = FUNCTION;
				newNode.function = get_func_type(source, &i);
				if (newNode.function == POW) newNode.type = OPERATOR;
				operators.push(&operators, newNode);
			}
		}
	}
	while (!operators.empty(operators)) {
		mainStack->push(mainStack, operators.pop(&operators));
	}
}

