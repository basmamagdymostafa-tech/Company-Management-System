#include <stdio.h>

#include "hierarchy.h"
#include "employees.h"
#include "validation.h"

/* ==================== Hierarchy Display ==================== */

void printHierarchy(s32 managerID, s32 level)
{
    s32 index;
    s32 indentation;

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        if (employees[index].managerID == managerID)
        {
            for (indentation = 0; indentation < level; indentation++)
            {
                printf("    ");
            }

            printf("|--- [%d] %-25s | %-20s\n",
                   employees[index].employeeID,
                   employees[index].fullName,
                   employees[index].jobTitle);

            printHierarchy(employees[index].employeeID, level + 1);
        }
    }
}

void viewEmployeeHierarchy(void)
{
    s32 employeeID;
    s32 employeeIndex;
    s32 hasReports;
    s32 index;

    employeeIndex = -1;
    hasReports = 0;

    printf("\n");
    printf("============================================================\n");
    printf("                  REPORTING HIERARCHY\n");
    printf("============================================================\n");

    printf("\nA Reporting Hierarchy shows the selected employee and\n");
    printf("all employees below them in the reporting structure.\n");

    printf("\nUnlike Direct Reports, this includes indirect reports.\n");

    printf("\nExample:\n");
    printf("Manager\n");
    printf("  |----Employee A       <- Direct Report\n");
    printf("  |     |--- Employee B <- Indirect Report\n");
    printf("  |--- Employee C       <- Direct Report\n");
    if (employees[0].employeeID == 0)
    {
        printf("\nNo employees found.\n");
        printf("============================================================\n");
        return;
    }


    while (1)
    {
        if (!readInt("\nEmployee ID: ", &employeeID))
        {
            continue;
        }

        if (employeeID <= 0)
        {
            printf(COLOR_RED
                   "Invalid Employee ID! ID must be greater than 0.\n"
                   COLOR_RESET);
            continue;
        }

        break;
    }

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        if (employees[index].employeeID == employeeID)
        {
            employeeIndex = index;
            break;
        }
    }

    if (employeeIndex == -1)
    {
        printf(COLOR_RED
               "\nEmployee ID %d not found.\n"
               COLOR_RESET,
               employeeID);
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_CYAN COLOR_BOLD
           "                    EMPLOYEE INFORMATION\n"
           COLOR_RESET);
    printf("============================================================\n");
    printf("| Employee ID        : %-34d |\n",
           employees[employeeIndex].employeeID);
    printf("| Full Name          : %-34s |\n",
           employees[employeeIndex].fullName);
    printf("| Job Title          : %-34s |\n",
           employees[employeeIndex].jobTitle);
    printf("============================================================\n");

    printf("\nReporting Structure:\n\n");

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        if (employees[index].managerID == employeeID)
        {
            hasReports = 1;
            break;
        }
    }

    if (!hasReports)
    {
        printf("This employee has no direct or indirect subordinates.\n");
        printf("============================================================\n");
        return;
    }

    printHierarchy(employeeID, 1);

    printf("\n============================================================\n");
}

void viewDirectReports(void)
{
    s32 targetID;
    s32 managerIndex = -1;
    s32 i;
    u8 foundAnyone = 0;

    printf("\n");
    printf("============================================================\n");
    printf("                     DIRECT REPORTS\n");
    printf("============================================================\n");

    printf("\nDirect Reports are employees who report directly to\n");
    printf("the selected employee.\n");

    printf("\nExample:\n");
    printf("Manager\n");
    printf("  |---Employee A       <- Direct Report\n");
    printf("  |     |--- Employee B <- NOT a Direct Report\n");
    printf("  |---Employee C       <- Direct Report\n");


    /* =========================================================
       Employee prerequisite
       ========================================================= */

    if (employees[0].employeeID == 0)
    {
        printf("\n");
        printf(COLOR_YELLOW
               "No employees are currently available.\n"
               COLOR_RESET);

        return;
    }


    /* =========================================================
       Get Employee ID
       ========================================================= */

    while (1)
    {
        if (!readInt("\nEmployee ID: ", &targetID))
        {
            continue;
        }

        if (targetID <= 0)
        {
            printf(COLOR_RED
                   "Employee ID must be greater than 0.\n"
                   COLOR_RESET);
            continue;
        }

        break;
    }


    /* =========================================================
       Find Employee
       ========================================================= */

    for (i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i].employeeID == 0)
        {
            break;
        }

        if (employees[i].employeeID == targetID)
        {
            managerIndex = i;
            break;
        }
    }


    if (managerIndex == -1)
    {
        printf(COLOR_RED
               "\nEmployee ID %d was not found.\n"
               COLOR_RESET,
               targetID);

        return;
    }


    /* =========================================================
       Display Employee
       ========================================================= */

    printf("\n");
    printf("Employee ID   : %d\n",
           employees[managerIndex].employeeID);

    printf("Employee Name : %s\n",
           employees[managerIndex].fullName);

    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("                     DIRECT REPORTS\n");
    printf("------------------------------------------------------------\n");

    printf("| %-8s | %-25s | %-20s |\n",
           "ID",
           "Name",
           "Job Title");

    printf("------------------------------------------------------------\n");


    /* =========================================================
       Display Direct Reports
       ========================================================= */

    for (i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i].employeeID == 0)
        {
            break;
        }

        if (employees[i].managerID == targetID)
        {
            printf("| %-8d | %-25s | %-20s |\n",
                   employees[i].employeeID,
                   employees[i].fullName,
                   employees[i].jobTitle);

            foundAnyone = 1;
        }
    }


    if (!foundAnyone)
    {
        printf("| %-56s |\n",
               "This employee has no direct reports.");
    }

    printf("------------------------------------------------------------\n");
}
