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
	char stroka[10000];
	for (int i = 0; ; i++) { //collect data
		char prefix[VARIABLES_NAME_LEN];
		char postfix[VARIABLES_DATA_LEN];
		int prefixID = 0;
		int postfixID = 0;
		gets(stroka);

		int flag = 0;
		for (int i = 0; stroka[i - 1] != '\0'; i++) {

			if (flag == 0 && stroka[i] != ' ') {
				prefix[prefixID++] = stroka[i];
			}
			else {
				if (strcmp(prefix, "finish") == 0) return varLen;
				if (flag == 0) {
					prefix[prefixID] = '\0';
				}
				flag = 1;
			}
			if (flag == 1 && stroka[i] != '=' && stroka[i] != ' ') {
				postfix[postfixID++] = stroka[i];
			}
		}
		postfix[postfixID] = '\0';
		if (strcmp(prefix, "finish") == 0) return varLen;
		strcpy(variables[i].name, prefix);
		strcpy(variables[i].data, postfix);
		varLen++;
	}
	//return lenght of array that contain variables
}
//ln((phase(k-c)*(e-d)/e-b^pow(tg(a-e)^c)-d,c*(c-log(e))^e*cos(d/c))
//	a = 1
//	b = a+1
//	c = b*(b/b)
//	d = c/b
//	e = d*(c-d)^a+b
//	k = b-e+d*i
//	finish
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
				for (; (instring[posIN] < 39 || instring[posIN] > 47) && instring[posIN] != '\0'; posOUT++, posIN++) {
					outstring[posOUT] = instring[posIN];
				}
				posIN--;
			}
			else {
				posOUT = StringBuilder(variables[var].data, variables, varlen, outstring, posOUT);
				while (((instring[posIN] < 39 || instring[posIN] > 47) && instring[posIN] != '^') && instring[posIN] != '\0') {
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