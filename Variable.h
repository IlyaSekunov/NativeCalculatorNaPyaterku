#include "Constants.h"
#ifndef VARIABLE
#define VARIABLE
typedef struct variable {
	char name[VARIABLES_NAME_LEN];
	char data[VARIABLES_DATA_LEN];
}variable;
#endif