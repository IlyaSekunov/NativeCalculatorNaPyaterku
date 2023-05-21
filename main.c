#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "Constants.h"
#include "Variable.h"

RPNNode solveRPN(Stack* rpn);
void Transform_to_Polish(Stack* mainStack, char* source);

int main() {
	Stack mainStack;

	init_Stack(&mainStack);
	//
	char instring[INPUT_STRING_LEN]; //starter string with input information
	variable variables[COUNT_VARIABLES]; //Place where we contains data about variables(peremennie)
	printf("Enter a mathematical expression:\n");
	scanf("%s", &instring);
	printf("Initialize constants:(before the expression <all>)\n");

	int varlen = CollectDataV(variables);
	
	/*char outstring[OUTPUT_STRING_LEN] =*/
	char outstring[OUTPUT_STRING_LEN];
	int posOUT = 0;
	int final = StringBuilder(instring, variables, varlen, outstring, posOUT); //starter string | set of variables
	outstring[final] = '\0';
	//printf("%s", outstring);


	char* s = outstring;
	//
	Transform_to_Polish(&mainStack, s);

	RPNNode res = solveRPN(&mainStack);

	printf("Result:\n");
	if (res.type == REAL_NUMBER) {
		printf("%f", res.real_number);
	}
	else {
		printf("%f + (%f)j", creall(res.complex_number), cimagl(res.complex_number));
	}
	//printf("%d", mainStack.size);
}