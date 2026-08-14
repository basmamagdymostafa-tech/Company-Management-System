#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "Config.h"
struct employee employees[100];
void clearInputBuffer(void);
int readString(const char *, char *, int);
int readInt(const char *, int *);
int validatePhone(const char *);
int validateEmail(const char *);
int validateEmployeeID(int , int);
int validateDepartmentID(int );
int validateManagerID(int , int , int );
int checkCircular(int , int , int );
int validateDate(int, int, int );
void addEmployee(void);
void viewEmployee(void);
#endif // EMPLOYEES_H
