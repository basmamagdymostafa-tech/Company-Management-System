#include <stdio.h>

#include "config.h"
#include "customers.h"
#include "departments.h"
#include "employees.h"
#include "hierarchy.h"
#include "storage.h"
#include "validation.h"

/* ==================== Main Menu ==================== */

int main(void)
{
    s32 choice;

    loadNextIDs();
    loadEmployee();
    loadCustomers();
    loadDepartments();

    choice = -1;

    do
    {
        clearScreen();

        printf("=========================================\n");
        printf(COLOR_CYAN COLOR_BOLD
               "      COMPANY MANAGEMENT SYSTEM\n"
               COLOR_RESET);
        printf("=========================================\n");

        printf("\n");
        printf("  1. Add Customer\n");
        printf("  2. Delete Customer\n");
        printf("  3. View Customer\n");
        printf("  4. View All Customers\n");
        printf("  5. Update Customer\n");

        printf("\n");
        printf("  6. Add Employee\n");
        printf("  7. View Employee\n");

        printf("\n");
        printf("  8. Add Department\n");
        printf("  9. View Department\n");
        printf(" 10. Assign Department Manager\n");
        printf(" 11. View Department Employees\n");

        printf("\n");
        printf(" 12. View Direct Reports\n");
        printf(" 13. View Employee Hierarchy\n");

        printf("\n");
        printf("  0. Exit\n");
        printf("=========================================\n");

        if (!readInt("\nEnter your choice: ", &choice))
        {
            pauseScreen();
            continue;
        }

        switch (choice)
        {
        case 1:
            clearScreen();
            addCustomer();
            pauseScreen();
            break;

        case 2:
            clearScreen();
            deleteCustomer();
            pauseScreen();
            break;

        case 3:
            clearScreen();
            viewCustomer();
            pauseScreen();
            break;

        case 4:
            clearScreen();
            viewAllCustomers();
            pauseScreen();
            break;

        case 5:
            clearScreen();
            updateCustomer();
            pauseScreen();
            break;

        case 6:
            clearScreen();
            addEmployee();
            pauseScreen();
            break;

        case 7:
            clearScreen();
            viewEmployee();
            pauseScreen();
            break;

        case 8:
            clearScreen();
            addDepartment();
            pauseScreen();
            break;

        case 9:
            clearScreen();
            viewDepartment();
            pauseScreen();
            break;

        case 10:
            clearScreen();
            assignDepartmentManager();
            pauseScreen();
            break;

        case 11:
            clearScreen();
            viewDepartmentEmployees();
            pauseScreen();
            break;

        case 12:
            clearScreen();
            viewDirectReports();
            pauseScreen();
            break;

        case 13:
            clearScreen();
            viewEmployeeHierarchy();
            pauseScreen();
            break;

        case 0:
            saveEmployee();
            saveCustomers();
            saveDepartments();

            printf("\n");
            printf(COLOR_GREEN
                   "Exiting...\n"
                   "Thank you for using our company management system :)\n"
                   COLOR_RESET);
            break;

        default:
            printf(COLOR_RED
                   "\nInvalid choice. Please choose a number from 0 to 13.\n"
                   COLOR_RESET);
            pauseScreen();
            break;
        }
    }
    while (choice != 0);

    return 0;
}
