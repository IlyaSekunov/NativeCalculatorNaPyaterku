#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "Constants.h"

RPNNode solveRPN(Stack* rpn);
void Transform_to_Polish(Stack* mainStack, char* source);
int CollectDataV(variable variables[COUNT_VARIABLES]);
int StringBuilder(char instring[INPUT_STRING_LEN], variable variables[COUNT_VARIABLES], int varlen, char outstring[OUTPUT_STRING_LEN], int posOUT);

int main() {
	Stack mainStack;
	init_Stack(&mainStack);
	
	char instring[INPUT_STRING_LEN];
	variable variables[COUNT_VARIABLES];
	printf("Enter a mathematical expression:\n");
	
	char tmp = '0';
	int tmpIter = 0;
	while ((tmp = getchar()) != '\n') {
		if (tmp != ' ') {
			instring[tmpIter++] = tmp;
		}
	}
	instring[tmpIter] = '\0';

	printf("Initialize constants:(before the expression <all>)\n");

	int varlen = CollectDataV(variables);
	
	char outstring[OUTPUT_STRING_LEN];
	int posOUT = 0;
	int final = StringBuilder(instring, variables, varlen, outstring, posOUT); //starter string | set of variables
	outstring[final] = '\0';

	char* s = outstring;
	
	Transform_to_Polish(&mainStack, s);

	RPNNode res = solveRPN(&mainStack);

	printf("Result:\n");
	if (res.type == REAL_NUMBER) {
		if (fabs(res.real_number - round(res.real_number)) < 0.00000001) printf("%d", (int)res.real_number);
		else printf("%lf", res.real_number);
	}
	else {
		int real = fabs(creall(res.complex_number) - round(creall(res.complex_number))) < 0.00000001 ? 1 : 0;
		int image = fabs(cimagl(res.complex_number) - round(cimagl(res.complex_number))) < 0.00000001 ? 1 : 0;

		int realNotZero = 0;
		int imagNotZero = 0;

		if (real && (int)round(creall(res.complex_number)) != 0) {
			printf("%d ", (int)round(creall(res.complex_number)));
			realNotZero = 1;
		}
		else if (fabs(creall(res.complex_number)) > 0.00000001) {
			printf("%f ", creall(res.complex_number));
			realNotZero = 1;
		}

		if (realNotZero && fabs(cimagl(res.complex_number)) > 0.00000001) {
			if (cimagl(res.complex_number) > 0) {
				printf("+ ");
			}
			else {
				printf("- ");
			}

			imagNotZero = 1;
		}
		else if (fabs(cimagl(res.complex_number)) > 0.00000001) {
			if (cimagl(res.complex_number) < 0) {
				printf("-");
			}

			imagNotZero = 1;
		}

		if (imagNotZero) {
			if (image && abs((int)round(cimagl(res.complex_number))) != 1) {
				printf("%dj", abs((int)round(cimagl(res.complex_number))));
			}
			else if (!image) {
				printf("%lfj", fabs(cimagl(res.complex_number)));
			}
			else {
				printf("j");
			}
		}
	}
	if (fabs(cimagl(res.complex_number)) < 0.00000001 && fabs(creall(res.complex_number)) < 0.00000001) printf("0");
}