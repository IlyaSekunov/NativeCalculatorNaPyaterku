#include "Stack.h"
#include "Constants.h"
#include <stdlib.h>

void push_Stack(Stack* stack, RPNNode node) {
	stackList* newNode = (stackList*)malloc(sizeof(stackList));
	if (newNode) {
		newNode->node = node;
		newNode->next = NULL;
		if (!stack->head) {
			stack->head = newNode;
			++(stack->size);
			return;
		}
		stackList* iter = stack->head;
		while (iter->next) iter = iter->next;
		iter->next = newNode;
		++(stack->size);
	}
}

RPNNode pop_Stack(Stack* stack) {
	if (!stack->head) return;
	RPNNode popped;
	if (!stack->head->next) {
		--(stack->size);
		popped = stack->head->node;
		free(stack->head);
		stack->head = NULL;
		return popped;
	}
	stackList* prev = stack->head;
	stackList* next = stack->head;
	while (next->next) {
		prev = next;
		next = next->next;
	}
	popped = next->node;
	prev->next = NULL;
	free(next);
	--(stack->size);
	return popped;
}

RPNNode pop_head_Stack(Stack* stack) {
	if (!stack->head) return;
	RPNNode popped;
	if (!stack->head->next) {
		popped = stack->head->node;
		free(stack->head);
		stack->head = NULL;
		--(stack->size);
		return popped;
	}
	stackList* head = stack->head;
	popped = head->node;
	stack->head = head->next;
	free(head);
	--(stack->size);
	return popped;
}

RPNNode top_Stack(const Stack stack) {
	if (!stack.head) return;
	stackList* iter = stack.head;
	while (iter->next) iter = iter->next;
	return iter->node;
}

int empty_Stack(const Stack stack) {
	return stack.size > 0 ? 0 : 1;
}

void init_Stack(Stack* stack) {
	stack->head = NULL;
	stack->size = 0;
	stack->push = push_Stack;
	stack->pop = pop_Stack;
	stack->top = top_Stack;
	//stack->print = print_Stack;
	stack->empty = empty_Stack;
	stack->popHead = pop_head_Stack;
}