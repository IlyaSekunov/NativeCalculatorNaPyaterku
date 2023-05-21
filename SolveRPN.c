#define _USE_MATH_DEFINES
#include "Constants.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>


RPNNode solveRPN(Stack*);

void calc(Stack*, RPNNode);

RPNNode sum(RPNNode*, RPNNode*);
RPNNode sub(RPNNode*, RPNNode*);
RPNNode mult(RPNNode*, RPNNode*);
RPNNode divRpn(RPNNode*, RPNNode*);
RPNNode deg(RPNNode*, RPNNode*);

RPNNode cosRpn(RPNNode*);
RPNNode sinRpn(RPNNode*);
RPNNode tgRpn(RPNNode*);
RPNNode ctgRpn(RPNNode*);
RPNNode logRpn(RPNNode*);
RPNNode lnRpn(RPNNode*);
RPNNode sqrtRpn(RPNNode*);
RPNNode absRpn(RPNNode*);
RPNNode expRpn(RPNNode*);
RPNNode realRpn(RPNNode*);
RPNNode imagRpn(RPNNode*);
RPNNode magRpn(RPNNode*);
RPNNode phaseRpn(RPNNode*);

RPNNode solveRPN(Stack* rpn) {
	Stack* calcRpn = malloc(sizeof(Stack));
	init_Stack(calcRpn);

	while (rpn->size) {
		RPNNode next = pop_head_Stack(rpn);
		if (next.type == REAL_NUMBER || next.type == COMPLEX_NUMBER) {
			push_Stack(calcRpn, next);
		}
		else {
			calc(calcRpn, next);
		}
	}

	RPNNode result = pop_Stack(calcRpn);
	return result;
}

void calc(Stack* calcRpn, RPNNode func) {
	RPNNode oper2 = pop_Stack(calcRpn);
	RPNNode result;

	if (func.type == FUNCTION) {
		switch (func.function) {
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
	else if (func.type == OPERATOR) {
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
			result = divRpn(&oper1, &oper2);
			break;
		case POW:
			result = deg(&oper1, &oper2);
			break;
		}

	}

	push_Stack(calcRpn, result);
}

RPNNode sum(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double rslt = oper1->real_number + oper2->real_number;
			RPNNode res = { REAL_NUMBER, rslt };
			return res;
		}
		else {
			long double resReal = oper1->real_number + creall(oper2->complex_number);
			long double resImag = cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double resReal = creall(oper1->complex_number) + oper2->real_number;
			long double resImag = cimagl(oper1->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
		else {
			long double resReal = creall(oper1->complex_number) + creall(oper2->complex_number);
			long double resImag = cimagl(oper1->complex_number) + cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
	}
}

RPNNode sub(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double rslt = oper1->real_number - oper2->real_number;
			RPNNode res = { REAL_NUMBER, rslt };
			return res;
		}
		else {
			long double resReal = oper1->real_number - creall(oper2->complex_number);
			long double resImag = cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, -resImag} };
			return res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double resReal = creall(oper1->complex_number) - oper2->real_number;
			long double resImag = cimagl(oper1->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
		else {
			long double resReal = creall(oper1->complex_number) - creall(oper2->complex_number);
			long double resImag = cimagl(oper1->complex_number) - cimagl(oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
	}
}

RPNNode mult(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double rslt = oper1->real_number * oper2->real_number;
			RPNNode res = { REAL_NUMBER, rslt };
			return res;
		}
		else {
			_Lcomplex rslt = _LCmulcr(oper2->complex_number, oper1->real_number);
			RPNNode res = { COMPLEX_NUMBER, rslt };
			return res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			_Lcomplex rslt = _LCmulcr(oper1->complex_number, oper2->real_number);
			RPNNode res = { COMPLEX_NUMBER, rslt };
			return res;
		}
		else {
			_Lcomplex rslt = _LCmulcc(oper1->complex_number, oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, rslt };
			return res;
		}
	}
}

RPNNode divRpn(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double div = oper1->real_number / oper2->real_number;
			RPNNode res = { REAL_NUMBER, div };
			return res;
		}
		else {
			long double resReal = (oper1->real_number * creall(oper2->complex_number)) / (creall(oper2->complex_number) * creall(oper2->complex_number) + cimagl(oper2->complex_number) * cimagl(oper2->complex_number));
			long double resImag = (oper1->real_number * cimagl(oper2->complex_number)) / (creall(oper2->complex_number) * creall(oper2->complex_number) + cimagl(oper2->complex_number) * cimagl(oper2->complex_number));
			RPNNode res = { COMPLEX_NUMBER, {resReal, -resImag} };
			return res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			long double resReal = creall(oper1->complex_number) / oper2->real_number;
			long double resImag = cimagl(oper1->complex_number) / oper2->real_number;
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
		else {
			long double resReal = (creall(oper1->complex_number) * creall(oper2->complex_number) + cimagl(oper1->complex_number) * cimagl(oper2->complex_number)) / (creall(oper2->complex_number) * creall(oper2->complex_number) + cimagl(oper2->complex_number) * cimagl(oper2->complex_number));
			long double resImag = (cimagl(oper1->complex_number) * creall(oper2->complex_number) - creall(oper1->complex_number) * cimagl(oper2->complex_number)) / (creall(oper2->complex_number) * creall(oper2->complex_number) + cimagl(oper2->complex_number) * cimagl(oper2->complex_number));
			RPNNode res = { COMPLEX_NUMBER, {resReal, resImag} };
			return res;
		}
	}
}

RPNNode deg(RPNNode* oper1, RPNNode* oper2) {
	if (oper1->type == REAL_NUMBER) {
		if (oper2->type == REAL_NUMBER) {
			long double deg = pow(oper1->real_number, oper2->real_number);
			RPNNode res = { REAL_NUMBER, deg };
			return res;
		}
		else {
			_Lcomplex op1 = { oper1->real_number, 0 };
			_Lcomplex deg = cpowl(op1, oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, deg };
			return res;
		}
	}
	else {
		if (oper2->type == REAL_NUMBER) {
			_Lcomplex op2 = { oper2->real_number, 0 };
			_Lcomplex deg = cpowl(oper1->complex_number, op2);
			RPNNode res = { COMPLEX_NUMBER, deg };
			return res;
		}
		else {
			_Lcomplex deg = cpowl(oper1->complex_number, oper2->complex_number);
			RPNNode res = { COMPLEX_NUMBER, deg };
			return res;
		}
	}
}

RPNNode cosRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = cos(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = ccosl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}
}

RPNNode sinRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = sin(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = csinl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode tgRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = tan(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = ctanl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode ctgRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = 1 / tan(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		RPNNode del = { REAL_NUMBER, 1.0 };
		RPNNode tanRes = { COMPLEX_NUMBER, ctanl(oper->complex_number) };
		RPNNode res = divRpn(&del, &tanRes);
		return res;
	}
}

RPNNode logRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = log10(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = clog10l(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode lnRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = log(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = clogl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode sqrtRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = sqrt(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = csqrtl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode absRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = fabs(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		long double rslt = cabsl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode expRpn(RPNNode* oper) {
	if (oper->type == REAL_NUMBER) {
		long double rslt = exp(oper->real_number);
		RPNNode res = { REAL_NUMBER, rslt };
		return res;
	}
	else {
		_Lcomplex rslt = cexpl(oper->complex_number);
		RPNNode res = { COMPLEX_NUMBER, rslt };
		return res;
	}

}

RPNNode realRpn(RPNNode* oper) {
	long double rslt;
	if (oper->type = COMPLEX_NUMBER) {
		rslt = creall(oper->complex_number);
	}
	else {
		rslt = oper->real_number;
	}
	RPNNode res = { REAL_NUMBER, rslt };
	return res;
}

RPNNode imagRpn(RPNNode* oper) {
	long double rslt;
	if (oper->type = COMPLEX_NUMBER) {
		rslt = cimagl(oper->complex_number);
	}
	else {
		rslt = 0;
	}
	RPNNode res = { REAL_NUMBER, rslt };
	return res;
}

RPNNode magRpn(RPNNode* oper) {
	long double rslt;
	if (oper->type = COMPLEX_NUMBER) {
		rslt = cabsl(oper->complex_number);
	}
	else {
		rslt = oper->real_number;
	}
	RPNNode res = { REAL_NUMBER, rslt };
	return res;
}

RPNNode phaseRpn(RPNNode* oper) {
	RPNNode rslt = { REAL_NUMBER, 0 };
	if (oper->type == COMPLEX_NUMBER) {
		rslt.real_number = cargl(oper->complex_number);
	}
	else {
		if (fabs(creall(oper->complex_number)) > 0.00001) {
			if (creall(oper->complex_number) < 0) {
				rslt.real_number = M_PI / (-2);
			}
			else {
				rslt.real_number = M_PI / 2;
			}
		}
	}
	return rslt;
}