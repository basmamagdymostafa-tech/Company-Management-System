#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "config.h"

extern struct employee employees[MAX_EMPLOYEES];
extern s32 nextEmployeeID;

void addEmployee(void);
void viewEmployee(void);

#endif /* EMPLOYEES_H */
