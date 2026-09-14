#include <stdio.h>
#include <string.h>

#include "employees.h"
#include "departments.h"
#include "storage.h"
#include "validation.h"

/* ==================== Employee Data ==================== */

struct employee employees[MAX_EMPLOYEES] = {0};
s32 nextEmployeeID = 1;

/* ==================== Employee Operations ==================== */

void addEmployee(void)
{
    s32 targetIndex;
    s32 index;
    s32 departmentID;
    s32 hiringDay;
    s32 hiringMonth;
    s32 hiringYear;

    targetIndex = -1;

    printf("\n");
    printf("========================================\n");
    printf("              ADD EMPLOYEE\n");
    printf("========================================\n");

    /* =========================================================
    Department prerequisite
    ========================================================= */

    if (total_departments == 0)
    {
        printf("\n");
        printf(COLOR_YELLOW
               "No departments are currently available.\n"
               COLOR_RESET);

        printf("\nAn employee must belong to an existing department.\n");

        printf("\nRecommended setup sequence:\n");
        printf("  1. Add a Department\n");
        printf("  2. Add Employees to the Department\n");
        printf("  3. Assign a Department Manager\n");

        printf("\nPlease add a department before adding an employee.\n");

        return;
    }

    /* =========================================================
       Find an empty employee slot
       ========================================================= */

    for (index = 0; index < MAX_EMPLOYEES; index++)
    {
        if (employees[index].employeeID == 0)
        {
            targetIndex = index;
            break;
        }
    }

    if (targetIndex == -1)
    {
        printf(COLOR_RED "Employee list is full!\n" COLOR_RESET);
        return;
    }

    employees[targetIndex].employeeID = nextEmployeeID;

    printf("Employee ID assigned automatically: %d\n",
           employees[targetIndex].employeeID);

    /* Required employee information */
    while (!readString("Full name: ",
                       employees[targetIndex].fullName,
                       sizeof(employees[targetIndex].fullName)))
    {
    }

    do
    {
        while (!readString("Phone Number: ",
                           employees[targetIndex].phoneNumber,
                           sizeof(employees[targetIndex].phoneNumber)))
        {
        }
    }
    while (!validatePhone(employees[targetIndex].phoneNumber));

    do
    {
        while (!readString("Email: ",
                           employees[targetIndex].email,
                           sizeof(employees[targetIndex].email)))
        {
        }
    }
    while (!validateEmail(employees[targetIndex].email));

    do
    {
        while (!readInt("Department ID: ", &departmentID))
        {
        }
    }
    while (!validateDepartmentID(departmentID));

    employees[targetIndex].departmentID = departmentID;

    while (!readString("Job title: ",
                       employees[targetIndex].jobTitle,
                       sizeof(employees[targetIndex].jobTitle)))
    {
    }

    do
    {
        while (!readInt("Manager ID (0 for top manager): ",
                        &employees[targetIndex].managerID))
        {
        }
    }
    while (!validateManagerID(employees[targetIndex].managerID,
                              targetIndex,
                              employees[targetIndex].employeeID,
                              employees[targetIndex].departmentID) ||
            checkCircular(targetIndex,
                          employees[targetIndex].employeeID,
                          employees[targetIndex].managerID));

    do
    {
        printf("\n--- Hiring Date ---\n");

        while (!readInt("Enter Day (1-31): ", &hiringDay))
        {
        }

        while (!readInt("Enter Month (1-12): ", &hiringMonth))
        {
        }

        while (!readInt("Enter Year (e.g. 2026): ", &hiringYear))
        {
        }
    }
    while (!validateDate(hiringDay, hiringMonth, hiringYear));

    snprintf(employees[targetIndex].hiringDate,
             sizeof(employees[targetIndex].hiringDate),
             "%02d/%02d/%04d",
             hiringDay,
             hiringMonth,
             hiringYear);

    while (!readString("Employment status (e.g. full-time, part-time): ",
                       employees[targetIndex].employmentStatus,
                       sizeof(employees[targetIndex].employmentStatus)))
    {
    }

    nextEmployeeID++;
    saveEmployee();

    printf(COLOR_GREEN
           "Employee added successfully!\n"
           COLOR_RESET);
}

void viewEmployee(void)
{
    s32 viewOption;
    s32 employeeID;
    s32 startIndex;
    s32 endIndex;
    s32 foundIndex;
    s32 index;

    viewOption = 0;
    employeeID = 0;
    startIndex = 0;
    endIndex = 0;
    foundIndex = -1;

    if (employees[0].employeeID == 0)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                    EMPLOYEE INFORMATION\n");
        printf("============================================================\n");
        printf("\nNo employees to view.\n");
        printf("============================================================\n");
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf("                  EMPLOYEE VIEW OPTIONS\n");
    printf("============================================================\n");
    printf("  1. View Specific Employee (by ID)\n");
    printf("  2. View All Employees\n");
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
            if (!readInt("Employee ID you are searching for: ",
                         &employeeID))
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
                foundIndex = index;
                break;
            }
        }

        if (foundIndex == -1)
        {
            printf(COLOR_RED
                   "\nEmployee ID %d not found.\n"
                   COLOR_RESET,
                   employeeID);
            return;
        }

        startIndex = foundIndex;
        endIndex = foundIndex + 1;
    }
    else
    {
        startIndex = 0;
        endIndex = MAX_EMPLOYEES;
    }

    for (index = startIndex;
            index < endIndex && employees[index].employeeID != 0;
            index++)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                    EMPLOYEE %d INFORMATION\n", index + 1);
        printf("============================================================\n");
        printf("  Employee ID        : %-34d\n",
               employees[index].employeeID);
        printf("  Full Name          : %-34s\n",
               employees[index].fullName);
        printf("  Phone Number       : %-34s\n",
               employees[index].phoneNumber);
        printf("  Email              : %-34s\n",
               employees[index].email);
        printf("  Department ID      : %-34d\n",
               employees[index].departmentID);
        printf("  Job Title          : %-34s\n",
               employees[index].jobTitle);
        printf("  Employment Status  : %-34s\n",
               employees[index].employmentStatus);
        printf("  Hiring Date        : %-34s\n",
               employees[index].hiringDate);

        if (employees[index].managerID == 0)
        {
            printf("  Manager ID         : %-34s\n", "None");
        }
        else
        {
            printf("  Manager ID         : %-34d\n",
                   employees[index].managerID);
        }

        printf("============================================================\n");
    }
}
