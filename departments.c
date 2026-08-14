#include <stdio.h>
#include <string.h>

#include "Config.h"
#include "departments.h"
extern struct employee employees[100];

/* =========================================================
   Department Data
   ========================================================= */

struct department department_list[MAX_DEPARTMENTS];
int total_departments = 0;


/* =========================================================
   Add Department
   ========================================================= */

void addDepartment(void)
{
    struct department new_dept;
    int i;

    printf("\n========== ADD DEPARTMENT ==========\n");

    if (total_departments >= MAX_DEPARTMENTS)
    {
        printf("Error: Maximum number of departments reached.\n");
        pauseScreen();
        return;
    }

    /* ================= Department ID ================= */

    while (1)
    {
        while (!readInt("Department ID: ",
                        &new_dept.departmentID))
        {
        }

        if (new_dept.departmentID <= 0)
        {
            printf("Invalid Department ID! ID must be greater than 0.\n");
            continue;
        }

        for (i = 0; i < total_departments; i++)
        {
            if (department_list[i].departmentID ==
                new_dept.departmentID)
            {
                printf("Error: Department ID %d already exists!\n",
                       new_dept.departmentID);
                break;
            }
        }

        if (i == total_departments)
        {
            break;
        }
    }

    /* ================= Department Name ================= */

    while (!readString("Department Name: ",
                       new_dept.departmentName,
                       sizeof(new_dept.departmentName)))
    {
    }

    /* ================= Description ================= */

    while (!readString("Department Description: ",
                       new_dept.description,
                       sizeof(new_dept.description)))
    {
    }

    /* ================= Manager ID ================= */

    new_dept.departmentManagerID = 0;

    /* ================= Save Department ================= */

    department_list[total_departments] = new_dept;
    total_departments++;

    saveDepartments();

    printf("\nDepartment added successfully!\n");


}

void viewDepartment(void)
{
    int viewOption = 0;
    int findDept = 0;
    int startIndex = 0;
    int endIndex = 0;
    int foundIndex = -1;
    int i;

    if (total_departments == 0)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                   DEPARTMENT INFORMATION\n");
        printf("============================================================\n");
        printf("\nNo departments found.\n");
        printf("============================================================\n");
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf("                 DEPARTMENT VIEW OPTIONS\n");
    printf("============================================================\n");
    printf("| 1. View Specific Department (by ID)                       |\n");
    printf("| 2. View All Departments                                   |\n");
    printf("============================================================\n\n");

    while (1)
    {
        if (readInt("Enter your choice (1-2): ", &viewOption))
        {
            if (viewOption == 1 || viewOption == 2)
            {
                break;
            }
        }

        printf("Invalid choice! Please enter 1 or 2.\n");
    }

    switch (viewOption)
    {
        case 1:
            while (1)
            {
                if (!readInt("Department ID you are searching for: ",
                             &findDept))
                {
                    continue;
                }

                if (findDept <= 0)
                {
                    printf("Invalid Department ID! ID must be greater than 0.\n");
                    continue;
                }

                break;
            }

            for (i = 0; i < total_departments; i++)
            {
                if (department_list[i].departmentID == findDept)
                {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex == -1)
            {
                printf("\nDepartment ID %d not found.\n", findDept);
                return;
            }

            startIndex = foundIndex;
            endIndex = foundIndex + 1;
            break;

        case 2:
            startIndex = 0;
            endIndex = total_departments;
            break;

        default:
            return;
    }

    for (i = startIndex; i < endIndex; i++)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                   DEPARTMENT INFORMATION\n");
        printf("============================================================\n");
        printf("  Department ID         : %-31d  \n",
               department_list[i].departmentID);
        printf("  Department Name       : %-31s  \n",
               department_list[i].departmentName);
        printf("  Department Manager ID : %-31d  \n",
               department_list[i].departmentManagerID);
        printf("  Description           : %-31s  \n",
               department_list[i].description);
        printf("============================================================\n");
    }
}
/* =========================================================
   Assign Department Manager
   ========================================================= */

void assignDepartmentManager(void)
{
    int target_dept_id;
    int target_emp_id;
    int dept_index = -1;
    int emp_index = -1;
    int i;

    printf("\n========== ASSIGN DEPARTMENT MANAGER ==========\n");

    if (total_departments == 0)
    {
        printf("No departments available. Please add a department first.\n");
        return;
    }

    /* ================= 1. Find Department ================= */
    while (1)
    {
        if (!readInt("Enter Department ID to update: ", &target_dept_id))
        {
            continue;
        }

        for (i = 0; i < total_departments; i++)
        {
            if (department_list[i].departmentID == target_dept_id)
            {
                dept_index = i;
                break;
            }
        }

        if (dept_index != -1)
        {
            break; 
        }
        else
        {
            printf("Error: Department ID %d not found. Please try again.\n", target_dept_id);
        }
    }

    /* ================= 2. Find Employee ================= */
    while (1)
    {
        if (!readInt("Enter Employee ID to assign as manager: ", &target_emp_id))
        {
            continue;
        }

        for (i = 0; i < 100 && employees[i].employeeID != 0; i++)
        {
            if (employees[i].employeeID == target_emp_id)
            {
                emp_index = i;
                break;
            }
        }

        if (emp_index != -1)
        {
            break; 
        }
        else
        {
            printf("Error: Employee ID %d not found in the system. Please try again.\n", target_emp_id);
        }
    }
    department_list[dept_index].departmentManagerID = target_emp_id;
    saveDepartments();

    printf("\nSuccess! Employee %d is now the manager of Department %d.\n", target_emp_id, target_dept_id);
}
/* =========================================================
   View Department Employees
   ========================================================= */

void viewDepartmentEmployees(void)
{
    int target_dept_id;
    int found_anyone = 0;
    int i;

    printf("\n========== VIEW DEPARTMENT EMPLOYEES ==========\n");

    while (1)
    {
        if (readInt("Enter Department ID to view its employees: ", &target_dept_id))
        {
            break;
        }
    }

    printf("\n");
    printf("============================================================\n");
    printf("              EMPLOYEES IN DEPARTMENT %d\n", target_dept_id);
    printf("============================================================\n");
    printf(" %-10s | %-20s | %-20s\n", "ID", "Name", "Job Title");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < 100 && employees[i].employeeID != 0; i++)
    {
        if (employees[i].departmentID == target_dept_id)
        {
            printf(" %-10d | %-20s | %-20s\n", 
                   employees[i].employeeID, 
                   employees[i].fullName, 
                   employees[i].jobTitle);
            found_anyone = 1;
        }
    }

    if (found_anyone == 0)
    {
        printf(" No employees found working in this department.\n");
    }
    printf("============================================================\n");
}
