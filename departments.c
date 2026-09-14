#include <stdio.h>

#include "config.h"
#include "departments.h"
#include "employees.h"
#include "storage.h"
#include "validation.h"

/* ==================== Department Data ==================== */

struct department department_list[MAX_DEPARTMENTS] = {0};
s32 total_departments = 0;
s32 nextDepartmentID = 1;

/* ==================== Department Operations ==================== */

void addDepartment(void)
{
    struct department newDepartment;

    printf("\n");
    printf("========================================\n");
    printf("             ADD DEPARTMENT\n");
    printf("========================================\n");

    if (total_departments >= MAX_DEPARTMENTS)
    {
        printf(COLOR_RED
               "Maximum number of departments reached.\n"
               COLOR_RESET);
        return;
    }

    newDepartment.departmentID = nextDepartmentID;
    newDepartment.departmentManagerID = 0;

    printf("Department ID assigned automatically: %d\n",
           newDepartment.departmentID);

    while (!readString("Department Name: ",
                       newDepartment.departmentName,
                       sizeof(newDepartment.departmentName)))
    {
    }

    while (!readString("Department Description: ",
                       newDepartment.description,
                       sizeof(newDepartment.description)))
    {
    }

    department_list[total_departments] = newDepartment;
    total_departments++;
    nextDepartmentID++;

    saveDepartments();

    printf(COLOR_GREEN
           "\nDepartment added successfully!\n"
           COLOR_RESET);
}

void viewDepartment(void)
{
    s32 viewOption;
    s32 departmentID;
    s32 startIndex;
    s32 endIndex;
    s32 foundIndex;
    s32 index;

    viewOption = 0;
    departmentID = 0;
    startIndex = 0;
    endIndex = 0;
    foundIndex = -1;

    if (total_departments == 0)
    {
        printf("\n");
        printf("============================================================\n");
        printf(COLOR_YELLOW
               "                   DEPARTMENT INFORMATION\n"
               COLOR_RESET);
        printf("============================================================\n");
        printf("\nNo departments found.\n");
        printf("============================================================\n");
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_CYAN COLOR_BOLD
           "                 DEPARTMENT VIEW OPTIONS\n"
           COLOR_RESET);
    printf("============================================================\n");
    printf("  1. View Specific Department (by ID)\n");
    printf("  2. View All Departments\n");
    printf("============================================================\n\n");

    while (1)
    {
        if (readInt("Enter your choice (1-2): ", &viewOption) &&
                (viewOption == 1 || viewOption == 2))
        {
            break;
        }

        printf(COLOR_RED
               "Invalid choice! Please enter 1 or 2.\n"
               COLOR_RESET);
    }

    if (viewOption == 1)
    {
        while (1)
        {
            if (!readInt("Department ID you are searching for: ",
                         &departmentID))
            {
                continue;
            }

            if (departmentID <= 0)
            {
                printf(COLOR_RED
                       "Invalid Department ID! ID must be greater than 0.\n"
                       COLOR_RESET);
                continue;
            }

            break;
        }

        for (index = 0; index < total_departments; index++)
        {
            if (department_list[index].departmentID == departmentID)
            {
                foundIndex = index;
                break;
            }
        }

        if (foundIndex == -1)
        {
            printf(COLOR_RED
                   "\nDepartment ID %d not found.\n"
                   COLOR_RESET,
                   departmentID);
            return;
        }

        startIndex = foundIndex;
        endIndex = foundIndex + 1;
    }
    else
    {
        startIndex = 0;
        endIndex = total_departments;
    }

    for (index = startIndex; index < endIndex; index++)
    {
        printf("\n");
        printf("============================================================\n");
        printf(COLOR_CYAN COLOR_BOLD
               "                   DEPARTMENT INFORMATION\n"
               COLOR_RESET);
        printf("============================================================\n");
        printf("  Department ID         : %-31d\n",
               department_list[index].departmentID);
        printf("  Department Name       : %-31s\n",
               department_list[index].departmentName);
        printf("  Department Manager ID : %-31d\n",
               department_list[index].departmentManagerID);
        printf("  Description           : %-31s\n",
               department_list[index].description);
        printf("============================================================\n");
    }
}

void assignDepartmentManager(void)
{
    s32 targetDeptID;
    s32 targetEmployeeID;
    s32 deptIndex = -1;
    s32 employeeIndex = -1;
    s32 i;

    printf("\n");
    printf("============================================================\n");
    printf("                 ASSIGN DEPARTMENT MANAGER\n");
    printf("============================================================\n");


    /* =========================================================
       Department prerequisite
       ========================================================= */

    if (total_departments == 0)
    {
        printf("\n");
        printf(COLOR_YELLOW
               "No departments are currently available.\n"
               COLOR_RESET);

        printf("\nRecommended setup sequence:\n");
        printf("  1. Add a Department\n");
        printf("  2. Add Employees to the Department\n");
        printf("  3. Assign a Department Manager\n");

        return;
    }


    /* =========================================================
       Employee prerequisite
       ========================================================= */

    if (employees[0].employeeID == 0)
    {
        printf("\n");
        printf(COLOR_YELLOW
               "No employees are currently available.\n"
               COLOR_RESET);

        printf("\nYou must add employees before assigning a department manager.\n");

        printf("\nRecommended setup sequence:\n");
        printf("  1. Add a Department\n");
        printf("  2. Add Employees to the Department\n");
        printf("  3. Assign a Department Manager\n");

        return;
    }


    /* =========================================================
       Explain manager requirements
       ========================================================= */

    printf("\nA Department Manager must satisfy ALL of the following:\n");
    printf("  1. The department must already exist.\n");
    printf("  2. The employee must already exist.\n");
    printf("  3. The employee must belong to this department.\n");
    printf("  4. The employee must have no manager.\n");
    printf("     Manager ID must be 0.\n");
    printf("  5. Therefore, the employee must be top-level.\n");


    /* =========================================================
       Find Department
       ========================================================= */

    while (deptIndex == -1)
    {
        while (!readInt("\nDepartment ID: ", &targetDeptID))
        {
        }

        for (i = 0; i < total_departments; i++)
        {
            if (department_list[i].departmentID == targetDeptID)
            {
                deptIndex = i;
                break;
            }
        }

        if (deptIndex == -1)
        {
            printf(COLOR_RED
                   "Department ID %d does not exist.\n"
                   COLOR_RESET,
                   targetDeptID);
        }
    }


    /* =========================================================
       Display Current Department Information
       ========================================================= */

    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("Department : %s\n",
           department_list[deptIndex].departmentName);

    if (department_list[deptIndex].departmentManagerID == 0)
    {
        printf("Manager    : Not assigned\n");
    }
    else
    {
        printf("Manager ID : %d\n",
               department_list[deptIndex].departmentManagerID);
    }

    printf("------------------------------------------------------------\n");


    /* =========================================================
       Check that the department has employees
       ========================================================= */

    {
        s32 employeeCount = 0;

        for (i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].employeeID == 0)
            {
                break;
            }

            if (employees[i].departmentID == targetDeptID)
            {
                employeeCount++;
            }
        }

        if (employeeCount == 0)
        {
            printf("\n");
            printf(COLOR_YELLOW
                   "This department has no employees yet.\n"
                   COLOR_RESET);

            printf("Add at least one employee to this department before\n");
            printf("assigning a Department Manager.\n");

            return;
        }
    }


    /* =========================================================
       Display Employees Belonging to Department
       ========================================================= */

    printf("\nEmployees belonging to this department:\n\n");

    printf("------------------------------------------------------------\n");
    printf("| %-8s | %-25s | %-12s |\n",
           "ID",
           "Name",
           "Manager ID");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i].employeeID == 0)
        {
            break;
        }

        if (employees[i].departmentID == targetDeptID)
        {
            printf("| %-8d | %-25s | %-12d |\n",
                   employees[i].employeeID,
                   employees[i].fullName,
                   employees[i].managerID);
        }
    }

    printf("------------------------------------------------------------\n");

    printf("\n");
    printf(COLOR_YELLOW
           "Only employees with Manager ID = 0 can become\n"
           "the Department Manager.\n"
           COLOR_RESET);


    /* =========================================================
       Select Employee
       ========================================================= */

    while (employeeIndex == -1)
    {
        while (!readInt("\nEmployee ID to assign as manager: ",
                        &targetEmployeeID))
        {
        }

        for (i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].employeeID == 0)
            {
                break;
            }

            if (employees[i].employeeID == targetEmployeeID)
            {
                employeeIndex = i;
                break;
            }
        }

        if (employeeIndex == -1)
        {
            printf(COLOR_RED
                   "Employee ID %d does not exist.\n"
                   COLOR_RESET,
                   targetEmployeeID);
            continue;
        }


        /* Employee must belong to selected department */

        if (employees[employeeIndex].departmentID != targetDeptID)
        {
            printf(COLOR_RED
                   "\nThis employee does not belong to the selected department.\n"
                   COLOR_RESET);

            printf("The Department Manager must belong to the same department.\n");

            employeeIndex = -1;
            continue;
        }


        /* Employee must be top-level */

        if (employees[employeeIndex].managerID != 0)
        {
            printf(COLOR_RED
                   "\nThis employee cannot become the Department Manager.\n"
                   COLOR_RESET);

            printf("Employee: %s\n",
                   employees[employeeIndex].fullName);

            printf("Current Manager ID: %d\n",
                   employees[employeeIndex].managerID);

            printf("\nA Department Manager must be a top-level employee.\n");
            printf("The employee's Manager ID must be 0.\n");

            employeeIndex = -1;
            continue;
        }
    }


    /* =========================================================
       Assign Manager
       ========================================================= */

    department_list[deptIndex].departmentManagerID =
        targetEmployeeID;

    saveDepartments();


    /* =========================================================
       Success Message
       ========================================================= */

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_GREEN
           "             MANAGER ASSIGNED SUCCESSFULLY\n"
           COLOR_RESET);
    printf("============================================================\n");

    printf(" Department ID   : %-21d\n",
           targetDeptID);

    printf(" Department Name : %-21s\n",
           department_list[deptIndex].departmentName);

    printf(" Manager ID      : %-21d\n",
           targetEmployeeID);

    printf(" Manager Name    : %-21s\n",
           employees[employeeIndex].fullName);

    printf("============================================================\n");
}
void viewDepartmentEmployees(void)
{
    s32 departmentID;
    s32 departmentIndex;
    s32 foundAnyone;
    s32 index;

    departmentIndex = -1;
    foundAnyone = 0;

    if (total_departments == 0)
    {
        printf("\n");
        printf("============================================================\n");
        printf(COLOR_YELLOW
               "                DEPARTMENT EMPLOYEES\n"
               COLOR_RESET);
        printf("============================================================\n");
        printf("\nNo departments found.\n");
        printf("============================================================\n");
        return;
    }

    while (1)
    {
        if (!readInt("Department ID: ", &departmentID))
        {
            continue;
        }

        if (departmentID <= 0)
        {
            printf(COLOR_RED
                   "Invalid Department ID! ID must be greater than 0.\n"
                   COLOR_RESET);
            continue;
        }

        break;
    }

    for (index = 0; index < total_departments; index++)
    {
        if (department_list[index].departmentID == departmentID)
        {
            departmentIndex = index;
            break;
        }
    }

    if (departmentIndex == -1)
    {
        printf(COLOR_RED
               "\nDepartment ID %d not found.\n"
               COLOR_RESET,
               departmentID);
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_CYAN COLOR_BOLD
           "              EMPLOYEES IN DEPARTMENT\n"
           COLOR_RESET);
    printf("============================================================\n");

    printf("\nManager: ");

    if (department_list[departmentIndex].departmentManagerID == 0)
    {
        printf(COLOR_YELLOW
               "No department manager has been assigned.\n"
               COLOR_RESET);
    }
    else
    {
        for (index = 0;
                index < MAX_EMPLOYEES && employees[index].employeeID != 0;
                index++)
        {
            if (employees[index].employeeID ==
                    department_list[departmentIndex].departmentManagerID)
            {
                printf("%s\n", employees[index].fullName);
                break;
            }
        }
    }

    printf("Department ID   : %-38d\n",
           department_list[departmentIndex].departmentID);
    printf("Department Name : %-38s\n",
           department_list[departmentIndex].departmentName);

    printf("\n------------------------------------------------------------\n");
    printf(COLOR_CYAN COLOR_BOLD
           "  %-8s | %-25s | %-20s\n"
           COLOR_RESET,
           "ID", "Name", "Job Title");
    printf("------------------------------------------------------------\n");

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        if (employees[index].departmentID == departmentID)
        {
            printf("| %-8d | %-25s | %-20s\n",
                   employees[index].employeeID,
                   employees[index].fullName,
                   employees[index].jobTitle);
            foundAnyone = 1;
        }
    }

    if (!foundAnyone)
    {
        printf(COLOR_YELLOW
               "| No employees found in this department.                |\n"
               COLOR_RESET);
    }

    printf("------------------------------------------------------------\n");
    printf("============================================================\n");
}
