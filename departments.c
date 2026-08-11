#include <stdio.h>
#include <string.h>
#include "Config.h"
#include "departments.h"
struct department department_list[50];
int total_departments = 0;

void addDepartment(void)
{
    struct department new_dept;
    int is_duplicate = 0;
    int i;

    printf("\n--- Add New Department ---\n");
    if (total_departments >= 50) {
        printf("Error: Maximum number of departments reached.\n");
        return;
    }

    printf("Enter unique Department ID: ");
    scanf("%d", &new_dept.departmentID);

    for (i = 0; i < total_departments; i++) {
        if (department_list[i].departmentID == new_dept.departmentID) {
            is_duplicate = 1;
        }
    }

    if (is_duplicate == 1) {
        printf("Error: Department ID %d already exists!\n", new_dept.departmentID);
        return;
    }
    printf("Enter Department Name: ");
    scanf(" %[^\n]", new_dept.departmentName);
    printf("Enter Department Description: ");
    scanf(" %[^\n]", new_dept.description);
    new_dept.departmentManagerID = 0;
    department_list[total_departments] = new_dept;
    total_departments++;

    printf("Success! Department added.\n");
}


void viewDepartment(void)
{
    int i;
    if (total_departments == 0) {
        printf("No departments found. The database is empty.\n");
        return;
    }

    printf("\n--- Department List ---\n");
    printf("ID \t Name \t\t Manager ID \t Description\n");
    printf("----------------------------------------------------\n");

    for (i = 0; i < total_departments; i++) {
        printf("%d \t %s \t %d \t\t %s\n",
               department_list[i].departmentID,
               department_list[i].departmentName,
               department_list[i].departmentManagerID,
               department_list[i].description);
    }
}
