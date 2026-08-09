#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

typedef unsigned char u8;
typedef unsigned int u32;
typedef char s8;
typedef int s32;
typedef float f32;

struct Customer
{
    s32 customerID;
    s8 fullName[100];
    s8 phoneNumber[11];
    s8 email[100];
    s8 address[200];
    s8 nationalID[14];
    s8 registrationDate[20];
    u8 status;
    s8 notes[300];
};


struct employee
{
    s32 employeeID;
    s8 fullName[100];
    s8 phoneNumber[11];
    s8 email[100];
    s32 departmentID;
    s8 jobTitle[100];
    s32 managerID;
    s8 hiringDate[20];
    u8 employmentStatus;

};


struct department
{
    s32 departmentID;
    s8 departmentName[100];
    s32 departmentManagerID;
    s8 description[200];

};



#endif // CONFIG_H
