#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <string.h>
#include <math.h>

RPNNode* create_RPNNode(int type) {
	RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
	if (type == REAL_NUMBER) {

	}
	else if (IS_OPERATOR(type)) {
		newNode->type = OPERATOR;
		newNode->operator = type;
	}
}

RPNNode get_number(int* i, char* source) {
	double result = 0;
	int dot = 0, exp = 1;
	for (; (source[*i] >= '0' && source[*i] <= '9' || source[*i] == '.' || source[*i] == ',') && *i < strlen(source); ++(*i)) {
		if (source[*i] == '.' || source[*i] == ',') {
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
	--(*i);
	RPNNode tmp;
	tmp.type = REAL_NUMBER;
	tmp.real_number = result;
	return tmp;
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

void Transform_to_Polish(Stack *mainStack, char* source) {
	Stack operators;
	init_Stack(&operators);

	//printf("Expression:\n%source\n", source);
	int len = strlen(source);

	for (int i = 0; i < len; ++i) {

		if (source[i] == ' ') continue;

		if (source[i] == '(') {
			//operation[++CurOperation] = source[i];
			//operators.push()
			RPNNode newNode;
			newNode.operator = source[i];
			newNode.type = OPERATOR;
			operators.push(&operators, &newNode);
		}

		if (source[i] == ')') {
			/*while (operation[CurOperation] != '(') {
				MainStack[++CurMain] = operation[CurOperation--] + SIGN;
			}
			operation[CurOperation--];*/
			while (operators.top(operators).operator != '(') {
				RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
				*newNode = operators.pop(&operators);
				mainStack->push(mainStack, newNode);
			}
		}

		if (OPERATOR_HELP(source[i])) {
			//Обработка унарного минуса
			if (source[i] == '-' && (i == 0 || source[i - 1] == '(')) {
				++i;
				//MainStack[++CurMain] = -GetNumber(&i, source);
				RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
				*newNode = get_number(&i, source);
				newNode->real_number *= -1;
				continue;
			}
			//Выгрузка оператора более низкого приоритета из стэка операторов в главный стэк
			/*if (CurOperation != -1 && priority(operation[CurOperation], source[i])) {
				MainStack[++CurMain] = operation[CurOperation--] + SIGN;
			}
			operation[++CurOperation] = source[i];*/
			if (!operators.empty(operators) && priority(operators.top(operators).operator, source[i])) {
				RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
				*newNode = operators.pop(&operators);
				mainStack->push(mainStack, newNode);
			}
			RPNNode tmp;
			tmp.operator = source[i];
			operators.push(&operators, &tmp);
		}
		if (source[i] >= '0' && source[i] <= '9') {
			//MainStack[++CurMain] = GetNumber(&i, source);
			RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
			*newNode = get_number(&i, source);
			mainStack->push(mainStack, newNode);
		}
	}
	/*while (CurOperation != -1) {
		MainStack[++CurMain] = operation[CurOperation--] + SIGN;
	}*/
	while (!operators.empty(operators)) {
		RPNNode* newNode = (RPNNode*)malloc(sizeof(RPNNode));
		*newNode = operators.pop(&operators);
		mainStack->push(mainStack, newNode);
	}
	free(source);
}

int main() {
	Stack mainStack;
	
	init_Stack(&mainStack);

	RPNNode node1, node2;
	node1.type = REAL_NUMBER;
	node2.type = REAL_NUMBER;
	node1.real_number = 1;
	node2.real_number = 2;

	mainStack.push(&mainStack, &node1);
	mainStack.push(&mainStack, &node2);
	mainStack.print(mainStack);

	/*printf("%lf\n", mainStack.popHead(&mainStack).real_number);
	mainStack.print(mainStack);

	printf("%lf\n", mainStack.popHead(&mainStack).real_number);
	mainStack.print(mainStack);

	printf("%lf\n", mainStack.popHead(&mainStack).real_number);
	mainStack.print(mainStack);*/

	printf("%lf\n", mainStack.pop(&mainStack).real_number);
	mainStack.print(mainStack);

	printf("%lf\n", mainStack.pop(&mainStack).real_number);
	mainStack.print(mainStack);

	printf("%lf\n", mainStack.pop(&mainStack).real_number);
	mainStack.print(mainStack);

}