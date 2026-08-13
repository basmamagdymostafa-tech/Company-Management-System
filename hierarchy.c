#include <stdio.h>
#include <string.h>
#include "Config.h"
#include "hierarchy.h"

void viewDirectReports(void)
{
    int target_id;
    int i;
    int found_anyone = 0;

    printf("\n--- View Direct Reports ---\n");
    printf("Enter the Manager's Employee ID: ");
    scanf("%d", &target_id);
    printf("\nEmployees who report directly to Manager ID %d:\n", target_id);
    printf("ID \t Name \t\t Job Title\n");
    printf("----------------------------------------------------\n");
    for (i = 0; i < total_employees; i++) {
        
        if (employee_list[i].managerID == target_id) {
            printf("%d \t %s \t %s\n", 
                   employee_list[i].employeeID, 
                   employee_list[i].fullName, 
                   employee_list[i].jobTitle);
            found_anyone = 1; 
        }
    }

    if (found_anyone == 0) {
        printf("This employee has no direct subordinates.\n");
    }
}

void printSubordinates(int manager_id, int level)
{
    int i;
    int j;

    for (i = 0; i < total_employees; i++) {
        
        if (employee_list[i].managerID == manager_id) {
            for (j = 0; j < level; j++) {
                printf("    ");
            }
            printf("|-- %s (ID: %d)\n", employee_list[i].fullName, employee_list[i].employeeID);
            printSubordinates(employee_list[i].employeeID, level + 1);
        }
    }
}



void viewEmployeeHierarchy(void)
{
    int target_id;
    int i;
    int found_manager = 0;
    printf("\n--- View Full Employee Hierarchy ---\n");
    printf("Enter the Top Manager's Employee ID: ");
    scanf("%d", &target_id);
    for (i = 0; i < total_employees; i++) {
        if (employee_list[i].employeeID == target_id) {
            printf("\nHierarchy for: %s (Department ID: %d)\n", 
                   employee_list[i].fullName, 
                   employee_list[i].departmentID);
            found_manager = 1;
        }
    }

    if (found_manager == 0) {
        printf("Error: Employee ID %d not found in the system.\n", target_id);
        return;
    }
    printSubordinates(target_id, 1);
}
