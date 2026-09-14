#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include "config.h"

extern struct department department_list[MAX_DEPARTMENTS];
extern s32 total_departments;
extern s32 nextDepartmentID;

void addDepartment(void);
void viewDepartment(void);
void assignDepartmentManager(void);
void viewDepartmentEmployees(void);

#endif /* DEPARTMENTS_H */
