#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define VAR_SIZE 100
#define size 1000
#define OPERATOR(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/' || (x) == '^')
#define SIGN 4932823

enum StackStatus {
	EMPTY,
	FULL
};

long double MainStack[size];
int CurMain = -1;

void PrintStack() {
	printf("Reverse Polish Notation:\n");
	for (int i = 0; i <= CurMain; ++i) {
		if (OPERATOR((int)MainStack[i] - SIGN)) {
			printf("%c ", (int)MainStack[i] - SIGN);
		}
		else {
			printf("%lf ", MainStack[i]);
		}
	}
	printf("\n");
}

long double pop(long double stack[], int* cur) {
	return stack[(*cur)--];
}

long double GetNumber(int* i, char* s) {
	double result = 0;
	int dot = 0, exp = 1;
	for (; (s[*i] >= '0' && s[*i] <= '9' || s[*i] == '.' || s[*i] == ',') && *i < strlen(s); ++(*i)) {
		if (s[*i] == '.' || s[*i] == ',') {
			dot = 1;
			continue;
		}
		if (dot == 0) {
			result = result * 10 + s[*i] - '0';
		}
		else {
			result += (s[*i] - '0') / pow(10, exp);
			++exp;
		}
	}
	--(*i);
	return result;
}

int CountVars(char* s) {
	int count_vars = 0;
	for (int i = 0; i < strlen(s); ++i) {
		if (isalpha(s[i])) {
			++count_vars;
			for (; !OPERATOR(s[i]); ++i);
		}
	}
	return count_vars;
}

char* ReplaceVariables(int count_vars, char* s) {
	int newSLen = 0;
	char* newS = (char*)calloc(size, sizeof(char));
	typedef struct VAR {
		char name[VAR_SIZE];
		char value[VAR_SIZE];
	} VAR;
	VAR* vars = (VAR*)calloc(count_vars, sizeof(VAR));
	for (int i = 0; i < count_vars; ++i) {
		char* var = (char*)calloc(VAR_SIZE, sizeof(char));
		gets(var);
		int j = 0, cur = 0;
		for (; var[j] != '='; ++j) {
			if (var[j] == ' ') continue;
			vars[i].name[cur++] = var[j];
		}
		vars[i].name[cur] = '\0';
		cur = 0;
		vars[i].value[cur++] = '(';
		for (; j < strlen(var); ++j) {
			if (var[j] == ' ' || var[j] == '=') continue;
			vars[i].value[cur++] = var[j];
		}
		vars[i].value[cur++] = ')';
		vars[i].value[cur] = '\0';
		free(var);
	}
	for (int i = 0; i < strlen(s); ++i) {
		if (isalpha(s[i])) {
			char* var = (char*)calloc(VAR_SIZE, sizeof(char));
			int j = 0;
			while (!(OPERATOR(s[i]) || s[i] == ' ') && i < strlen(s)) {
				var[j++] = s[i];
				++i;
			}
			var[j] = '\0';
			for (j = 0; j < count_vars; ++j) {
				if (!strcmp(vars[j].name, var)) {
					strcat(newS, vars[j].value);
					newSLen = strlen(newS);
				}
			}
			free(var);
		}
		newS[newSLen++] = s[i];
	}
	printf("%s\n", newS);
	free(vars);
	free(s);
	return newS;
}

//Возращает 1, если op1 приоритетнее или такой же приоритетности как op2, иначе - 0
int priority(int op1, int op2) {
	if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-')) {
		return 1;
	}
	if ((op1 == '*' || op2 == '/') && (op2 == '*' || op2 == '/' || op2 == '+' || op2 == '-')) {
		return 1;
	}
	if (op1 == '^' && (op2 == '^' || op2 == '*' || op2 == '/' || op2 == '+' || op2 == '-')) {
		return 1;
	}
	return 0;
}

long double* Transform_to_Polish(char* s) {
	int operation[size], CurOperation = -1;
	printf("Expression:\n%s\n", s);
	for (int i = 0; i < strlen(s); ++i) {
		if (s[i] == ' ') continue;
		if (s[i] == '(') {
			operation[++CurOperation] = s[i];
		}
		if (s[i] == ')') {
			while (operation[CurOperation] != '(') {
				MainStack[++CurMain] = operation[CurOperation--] + SIGN;
			}
			operation[CurOperation--];
		}
		if (OPERATOR(s[i])) {
			//Обработка унарного минуса
			if (s[i] == '-' && (i == 0 || s[i - 1] == '(')) {
				++i;
				MainStack[++CurMain] = -GetNumber(&i, s);
				continue;
			}
			//Выгрузка оператора более низкого приоритета из стэка операторов в главный стэк
			if (CurOperation != -1 && priority(operation[CurOperation], s[i])) {
				MainStack[++CurMain] = operation[CurOperation--] + SIGN;
			}
			operation[++CurOperation] = s[i];
			//
		}
		if (s[i] >= '0' && s[i] <= '9') {
			MainStack[++CurMain] = GetNumber(&i, s);
		}
	}
	while (CurOperation != -1) {
		MainStack[++CurMain] = operation[CurOperation--] + SIGN;
	}
	free(s);
}

long double Count() {
	long double result[size];
	int cur = -1;
	for (int i = 0; i <= CurMain; ++i) {
		if (OPERATOR((int)(MainStack[i] - SIGN))) {
			long double b = pop(result, &cur);
			long double a = pop(result, &cur);
			switch ((int)(MainStack[i] - SIGN)) {
			case '+':
				result[++cur] = a + b;
				break;
			case '-':
				result[++cur] = a - b;
				break;
			case '*':
				result[++cur] = a * b;
				break;
			case '/':
				result[++cur] = a / b;
				break;
			case '^':
				result[++cur] = pow(a, b);
				break;
			}
		}
		else {
			result[++cur] = MainStack[i];
		}
	}
	return result[0];
}

int main() {
	char* s = (char*)calloc(size, sizeof(char));
	gets(s);
	if (count_vars > 0) {
		s = ReplaceVariables(count_vars, s);
	}
	Transform_to_Polish(s, MainStack);
	PrintStack();
	printf("Result:\n%lf", Count());
}