#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "Stack.h"
#include "Constants.h"

RPNNode* resolveRPN(STACK*);

STACK* rpn;
STACK* calcRpn;

RPNNode* resolveRPN(STACK* RPN) {
	rpn = RPN;
	calcRpn = malloc(sizeof(STACK));
	initSTACK(calcRpn);
	while (rpn->size > 0) {

	}
}