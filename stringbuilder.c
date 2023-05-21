#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "Constants.h"
#include "Variable.h"
int CollectDataV(variable variables[COUNT_VARIABLES]) {
	int varLen = 0;
	char prefix[VARIABLES_NAME_LEN];
	char postfix[VARIABLES_DATA_LEN];
	for (int i = 0; ; i++) { //collect data
		scanf("%s", &prefix);
		if (strcmp(prefix, "finish") == 0) return varLen;
		scanf(" = %s", &postfix);
		if (strcmp(postfix, "finish") == 0) return varLen;
		strcpy(variables[i].name, prefix);
		strcpy(variables[i].data, postfix);
		varLen++;
	} 
	//return lenght of array that contain variables
}

char* CheckWord(int nowpos, char instring[INPUT_STRING_LEN], variable variables[COUNT_VARIABLES], int varlen) {
	//check word
	char buffer[100];
	int iterator = 0;
	for (int i = nowpos; ((instring[i] < 39 || instring[i] > 47) && instring[i] != '^') && instring[i] != '\0'; i++) {
		buffer[iterator] = instring[i];
		iterator++;
	}
	buffer[iterator] = '\0';
	//if this array with variables contain this word
	int checkcode = 0;
	for (int i = 0; i < varlen; i++) {
		if (strcmp(variables[i].name, buffer) == 0) {
			return i; //it return number of variable, else return -1
		}
	}
	return -1;
	//printf("%s\n", buffer);
}
//int BuildInVariable(variable variable)

int StringBuilder(char instring[INPUT_STRING_LEN], variable variables[COUNT_VARIABLES], int varlen, char outstring[OUTPUT_STRING_LEN], int posOUT) {
	/*char outstring[OUTPUT_STRING_LEN];
	int posOUT = 0;*/
	outstring[posOUT] = '(';
	posOUT++;
	for (int posIN = 0; instring[posIN] != '\0'; posIN++) {
		if ((instring[posIN] > 64 && instring[posIN] < 91) || (instring[posIN] > 96 && instring[posIN] < 123)) { //if this is char
			int var = CheckWord(posIN, instring, variables, varlen);
			if (var == -1) {
				for (; (instring[posIN] < 42 || instring[posIN] > 47)&& instring[posIN] != '\0'; posOUT++, posIN++) {
					outstring[posOUT] = instring[posIN];
				}
				posIN--;
			}
			else {
				posOUT = StringBuilder(variables[var].data, variables, varlen, outstring, posOUT);
				while (((instring[posIN] < 42 || instring[posIN] > 47) && instring[posIN] != '^') && instring[posIN] != '\0') {
					posIN++;
				}
				posIN--;
			}
		}
		else {
			outstring[posOUT] = instring[posIN];
			posOUT++;
		}
	}
	outstring[posOUT] = ')';
	posOUT++;
	return posOUT;
	
}
