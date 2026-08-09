#include <stdio.h>
#include <stdlib.h>

# include "Customers.h"
# include "departments.h"
# include "Employees.h"
# include "hierarchy.h"
# include "Storage.h"

int main()
{
    int choice;

    do
    {
        printf("\n===== COMPANY MANAGEMENT SYSTEM =====\n");

        printf("1. Add Customer\n");
        printf("2. Delete Customer\n");
        printf("3. View Customer\n");
        printf("4. View All Customers\n");
        printf("5. Update Customer\n");
        printf("6. Add Employee\n");
        printf("7. View Employee\n");
        printf("8. View Employee Hierarchy\n");
        printf("9. View Department Employees\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addCustomer();
                break;

            case 2:
                deleteCustomer();
                break;

            case 3:
                viewCustomer();
                break;

            case 4:
                viewAllCustomers();
                break;

            case 5:
                updateCustomer();
                break;

            case 6:
                addEmployee();
                break;

            case 7:
                viewEmployee();
                break;

            case 8:
                viewEmployeeHierarchy();
                break;

            case 9:
                viewDepartmentEmployees();
                break;

            case 0:
                printf("Exiting...\n");
                printf("Thank you for using our company management system :)\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
    return 0;
}
