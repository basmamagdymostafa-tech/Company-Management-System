#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

#include "Customers.h"
#include "departments.h"
#include "Employees.h"
#include "hierarchy.h"
#include "Storage.h"


int main()
{
    loadEmployee();
    loadCustomers();
    loadDepartments();

    int choice;


    do
    {
        clearScreen();

        printf("=========================================\n");
        printf("      COMPANY MANAGEMENT SYSTEM          \n");
        printf("=========================================\n");

        /* ================= CUSTOMER ================= */
        printf("  1. Add Customer\n");
        printf("  2. Delete Customer\n");
        printf("  3. View Customer\n");
        printf("  4. View All Customers\n");
        printf("  5. Update Customer\n");

        /* ================= EMPLOYEE ================= */
        printf("  6. Add Employee\n");
        printf("  7. View Employee\n");

        /* ================= DEPARTMENT ================ */
        printf("  8. Add Department\n");
        printf("  9. View Department\n");

        /* ================= HIERARCHY ================= */
        printf(" 10. View Employee Hierarchy\n");
        printf(" 11. View Department Employees\n");

        printf("  0. Exit\n");

        printf("=========================================\n");


        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            /* Handle malformed character inputs gracefully */
            clearInputBuffer();

            printf("Invalid input! Please enter a number.\n");

            pauseScreen();

            continue;
        }

        clearInputBuffer();


        switch (choice)
        {
            /* =================================================
               CUSTOMER OPTIONS
               ================================================= */

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


            /* =================================================
               EMPLOYEE OPTIONS
               ================================================= */

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


            /* =================================================
               DEPARTMENT OPTIONS
               ================================================= */

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


            /* =================================================
               HIERARCHY OPTIONS
               ================================================= */

            case 10:

                clearScreen();

                viewEmployeeHierarchy();

                pauseScreen();

                break;


            case 11:

                clearScreen();

                viewDepartmentEmployees();

                pauseScreen();

                break;


            /* =================================================
               EXIT
               ================================================= */

            case 0:

                saveEmployee();
                saveCustomers();
                saveDepartments();

                printf("\nExiting...\n");

                printf("Thank you for using our company management system :)\n");

                break;


            /* =================================================
               INVALID CHOICE
               ================================================= */

            default:

                printf("\nInvalid choice. Please return to the main menu "
                       "and choose between 0 and 11.\n");

                pauseScreen();

                break;
        }

    }
    while (choice != 0);


    return 0;
}
