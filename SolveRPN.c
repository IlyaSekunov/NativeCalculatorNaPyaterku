#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Constants.h"
#include "Stack.h"

RPNNode* solveRPN(Stack*);
void calc(Stack*, RPNNode);

RPNNode* sum(RPNNode*, RPNNode*, int func);
RPNNode* sub(RPNNode*, RPNNode*, int func);
RPNNode* mult(RPNNode*, RPNNode*, int func);
RPNNode* div(RPNNode*, RPNNode*, int func);
RPNNode* deg(RPNNode*, RPNNode*, int func);

RPNNode* cos(RPNNode*, int func);
RPNNode* sin(RPNNode*, int func);
RPNNode* tg(RPNNode*, int func);
RPNNode* ctg(RPNNode*, int func);
RPNNode* log(RPNNode*, int func);
RPNNode* ln(RPNNode*, int func);
RPNNode* sqrt(RPNNode*, int func);
RPNNode* pow(RPNNode*, int func);
RPNNode* abs(RPNNode*, int func);
RPNNode* exp(RPNNode*, int func);
RPNNode* real(RPNNode*, int func);
RPNNode* imag(RPNNode*, int func);
RPNNode* mag(RPNNode*, int func);
RPNNode* phase(RPNNode*, int func);


RPNNode* solveRPN(Stack* rpn) {
	Stack* calcRpn = malloc(sizeof(Stack));
	init_Stack(calcRpn);

	while(rpn->size) {
		RPNNode next = rpn->pop(rpn);
		if (next.type == REAL_NUMBER || next.type == COMPLEX_NUMBER) {
			calcRpn->push(calcRpn, &next);
		}
		else {
			calc(calcRpn, next);
		}
	}
}

void calc(Stack* calcRpn, RPNNode func) {
	RPNNode oper1 = pop_Stack(calcRpn);
	RPNNode* result;

	if (func.type == FUNCTION) {
		switch (func.type) {
		case SIN:
			result = sin(&oper1, func.function);
			break;
		case COS:
			result = cos(&oper1, func.function);
			break;
		case TG:
			result = tg(&oper1, func.function);
			break;
		case CTG:
			result = ctg(&oper1, func.function);
			break;
		case LOG:
			result = log(&oper1, func.function);
			break;
		case LN:
			result = ln(&oper1, func.function);
			break;
		case SQRT:
			result = sqrt(&oper1, func.function);
			break;
		case POW:
			result = pow(&oper1, func.function);
			break;
		case ABS:
			result = abs(&oper1, func.function);
			break;
		case EXP:
			result = exp(&oper1, func.function);
			break;
		case REAL:
			result = real(&oper1, func.function);
			break;
		case IMAG:
			result = imag(&oper1, func.function);
			break;
		case MAG:
			result = mag(&oper1, func.function);
			break;
		case PHASE:
			result = phase(&oper1, func.function);
			break;
		}
	}
	else {
		RPNNode oper2 = pop_Stack(calcRpn);
		switch (func.function) {
		case PLUS:
			result = sum(&oper1, &oper2, func.function);
			break;
		case MINUS:
			result = sub(&oper1, &oper2, func.function);
			break;
		case MULT:
			result = mult(&oper1, &oper2, func.function);
			break;
		case DIV:
			result = div(&oper1, &oper2, func.function);
			break;
		case DEG:
			result = deg(&oper1, &oper2, func.function);
			break;
		}
	}

	push_Stack(calcRpn, result);
}

