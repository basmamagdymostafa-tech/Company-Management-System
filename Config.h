#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_CUSTOMERS 100
#define MAX_DEPARTMENTS 50

static inline void clearScreen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

static inline void pauseScreen(void) {
    printf("\nPress [Enter] to return to the main menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*void printCentered(const char *text) {
    int consoleWidth = 80; // Standard console width
    int textLength = strlen(text);

    // Calculate required left padding
    int padding = (consoleWidth - textLength) / 2;
    if (padding < 0) padding = 0;

    // Print the dynamic spaces followed by the text
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}*/

// Standard Type Aliases
typedef unsigned char u8;
typedef unsigned int  u32;
typedef char          s8;
typedef int           s32;
typedef float         f32;

// Struct Definitions
struct Customer
{
    s32 customerID;
    s8 fullName[100];
    s8 phoneNumber[12];
    s8 email[100];
    s8 address[200];
    s8 nationalID[15];
    s8 registrationDate[20];
    u8 status;
    s8 notes[300];
};

struct employee
{
    s32 employeeID;
    s8 fullName[100];
    s8 phoneNumber[20];
    s8 email[100];
    s32 departmentID;
    s8 jobTitle[100];
    s32 managerID;
    s8 hiringDate[20];
    s8 employmentStatus[100];
};

struct department
{
    s32 departmentID;
    s8 departmentName[100];
    s32 departmentManagerID;
    s8 description[200];
};



#endif
