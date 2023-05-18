#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Constants.h"
#include "Stack.h"

RPNNode* solveRPN(Stack*);
void calc(Stack*, RPNNode);

RPNNode* sum(RPNNode*, RPNNode*);
RPNNode* sub(RPNNode*, RPNNode*);
RPNNode* mult(RPNNode*, RPNNode*);
RPNNode* div(RPNNode*, RPNNode*);
RPNNode* deg(RPNNode*, RPNNode*);

RPNNode* cosRpn(RPNNode*);
RPNNode* sinRpn(RPNNode*);
RPNNode* tgRpn(RPNNode*);
RPNNode* ctgRpn(RPNNode*);
RPNNode* logRpn(RPNNode*);
RPNNode* lnRpn(RPNNode*);
RPNNode* sqrtRpn(RPNNode*);
RPNNode* absRpn(RPNNode*);
RPNNode* expRpn(RPNNode*);
RPNNode* realRpn(RPNNode*);
RPNNode* imagRpn(RPNNode*);
RPNNode* magRpn(RPNNode*);
RPNNode* phaseRpn(RPNNode*);


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

	RPNNode result = pop_Stack(calcRpn);
	return &result;
}

void calc(Stack* calcRpn, RPNNode func) {
	RPNNode oper2 = pop_Stack(calcRpn);
	RPNNode* result;

	if (func.type == FUNCTION) {
		switch (func.type) {
		case SIN:
			result = sinRpn(&oper2);
			break;
		case COS:
			result = cosRpn(&oper2);
			break;
		case TG:
			result = tgRpn(&oper2);
			break;
		case CTG:
			result = ctgRpn(&oper2);
			break;
		case LOG:
			result = logRpn(&oper2);
			break;
		case LN:
			result = lnRpn(&oper2);
			break;
		case SQRT:
			result = sqrtRpn(&oper2);
			break;
		case ABS:
			result = absRpn(&oper2);
			break;
		case EXP:
			result = expRpn(&oper2);
			break;
		case REAL:
			result = realRpn(&oper2);
			break;
		case IMAG:
			result = imagRpn(&oper2);
			break;
		case MAG:
			result = magRpn(&oper2);
			break;
		case PHASE:
			result = phaseRpn(&oper2);
			break;
		}
	}
	else if(func.type == OPERATOR){
		RPNNode oper1 = pop_Stack(calcRpn);
		switch (func.function) {
		case PLUS:
			result = sum(&oper1, &oper2);
			break;
		case MINUS:
			result = sub(&oper1, &oper2);
			break;
		case MULT:
			result = mult(&oper1, &oper2);
			break;
		case DIV:
			result = div(&oper1, &oper2);
			break;
		case POW:
			result = deg(&oper1, &oper2);
			break;
		}
	}

	push_Stack(calcRpn, result);
}

RPNNode* sum(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double sum = oper1->real_number + oper2->real_number;
			RPNNode res = { REAL_NUMBER, sum };
			return &res;
		}
		else {
			long double sum = oper1->real_number + cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, sum} };
			return &res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double sum = cimagl(oper1->complex_number) + oper2->real_number;
			RPNNode res = { COMPLEX_NUMBER, {0, sum} };
			return &res;
		}
		else {
			long double sum = cimagl(oper1->complex_number) + cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, sum} };
			return &res;
		}
	}
}

RPNNode* sub(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double sub = oper1->real_number - oper2->real_number;
			RPNNode res = { REAL_NUMBER, sub };
			return &res;
		}
		else {
			long double sub = oper1->real_number - cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, sub} };
			return &res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double sub = cimagl(oper1->complex_number) - oper2->real_number;
			RPNNode res = { COMPLEX_NUMBER, {0, sub} };
			return &res;
		}
		else {
			long double sub = cimagl(oper1->complex_number) - cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, sub} };
			return &res;
		}
	}
}

RPNNode* mult(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double mult = oper1->real_number * oper2->real_number;
			RPNNode res = { REAL_NUMBER, mult };
			return &res;
		}
		else {
			long double mult = oper1->real_number * cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, mult} };
			return &res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double mult = cimagl(oper1->complex_number) * oper2->real_number;
			RPNNode res = { COMPLEX_NUMBER, {0, mult} };
			return &res;
		}
		else {
			long double mult = cimagl(oper1->complex_number) * cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, -mult };
			return &res;
		}
	}
}

RPNNode* div(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double div = oper1->real_number / oper2->real_number;
			RPNNode res = { REAL_NUMBER, div };
			return &res;
		}
		else {
			long double div = oper1->real_number / cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {0, -div} };
			return &res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double div = cimagl(oper1->complex_number) / oper2->real_number;
			RPNNode res = { COMPLEX_NUMBER, {0, div} };
			return &res;
		}
		else {
			long double div = cimagl(oper1->complex_number) / cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, div };
			return &res;
		}
	}
}

RPNNode* deg(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double deg = pow(oper1->real_number, oper2->real_number);
			RPNNode res = { REAL_NUMBER, deg };
			return &res;
		}
		else {
			_Lcomplex op1 = { oper1->real_number, 0 };
			_Lcomplex deg = cpowl(op1, oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, deg};
			return &res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			_Lcomplex op2 = { oper2->real_number, 0 };
			_Lcomplex deg = cpowl(oper1->complex_number, op2);
			RPNNode res = { COMPLEX_NUMBER, deg };
			return &res;
		}
		else {
			_Lcomplex deg = cpowl(oper1->complex_number, oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, deg };
			return &res;
		}
	}
}

RPNNode* cosRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = cos(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(ccosl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
}

RPNNode* sinRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = sin(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(csinl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* tgRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = tan(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(ctanl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* ctgRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = 1 / tan(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = 1 / creall(ctanl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* logRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = log(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(clogl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* lnRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = log10(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(clog10l(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* sqrtRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = sqrt(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(csqrtl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* absRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = abs(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = cabsl(oper->complex_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* expRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = exp(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}
	else {
		long double rslt = creall(cexpl(oper->complex_number));
		RPNNode res = { REAL_NUMBER, rslt };
		return &res;
	}

}

RPNNode* realRpn(RPNNode* oper) {
	long double rslt = creall(oper->complex_number);
	RPNNode res = { REAL_NUMBER, rslt };
	return &res;
}

RPNNode* imagRpn(RPNNode* oper) {
	long double rslt = cimagl(oper->complex_number);
	RPNNode res = { REAL_NUMBER, rslt };
	return &res;
}
RPNNode* magRpn(RPNNode* oper) {	
	long double rslt = sqrt(pow(creall(oper->complex_number), 2) + pow(cimagl(oper->complex_number), 2));
	RPNNode res = { REAL_NUMBER, rslt };
	return &res;
}

RPNNode* phaseRpn(RPNNode* oper) {
	long double rslt = atan(cimagl(oper->complex_number) / creall(oper->complex_number));
	RPNNode res = { REAL_NUMBER, rslt };
	return &res;
}
