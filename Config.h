#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>

/* ==================== Project Limits ==================== */

#define MAX_EMPLOYEES    100
#define MAX_CUSTOMERS   100
#define MAX_DEPARTMENTS 50

/* ==================== Console Colors ==================== */

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"

/* ==================== Common Data Types ==================== */

typedef unsigned char u8;
typedef unsigned int  u32;
typedef char          s8;
typedef int           s32;
typedef float         f32;

/* ==================== Data Structures ==================== */

struct Customer
{
    s32 customerID;
    s8  fullName[100];
    s8  phoneNumber[12];
    s8  email[100];
    s8  address[200];
    s8  nationalID[15];
    s8  registrationDate[20];
    u8  status;
    s8  notes[300];
};

struct employee
{
    s32 employeeID;
    s8  fullName[100];
    s8  phoneNumber[20];
    s8  email[100];
    s32 departmentID;
    s8  jobTitle[100];
    s32 managerID;
    s8  hiringDate[20];
    s8  employmentStatus[100];
};

struct department
{
    s32 departmentID;
    s8  departmentName[100];
    s32 departmentManagerID;
    s8  description[200];
};

/* ==================== Common Console Functions ==================== */

void clearScreen(void);
void pauseScreen(void);

#endif /* CONFIG_H */
