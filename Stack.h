#ifndef stackH
#define stackH
#include <complex.h>

typedef struct RPNNode {
	int type;
	union {
		_Lcomplex complex_number;
		long double real_number;
		int function;
	};
}RPNNode;

typedef struct stackList {
	RPNNode node;
	struct stackList* next;
} stackList;

typedef struct Stack {
	stackList* head;
	int size;
	void (*push)(struct Stack* stack, RPNNode node);
	RPNNode (*pop)(struct Stack* stack);
	RPNNode(*popHead) (struct Stack* stack);
	int (*empty)(const struct Stack stack);
	RPNNode (*top)(struct Stack stack);
	void (*print)(const struct Stack stack);
} Stack;

void push_Stack(Stack* stack, RPNNode node);
RPNNode pop_Stack(Stack* stack);
RPNNode pop_head_Stack(Stack* stack);
RPNNode top_Stack(const Stack stack);
void print_Stack(const Stack stack);
int empty_Stack(const Stack stack);
void init_Stack(Stack* stack);

#endif



