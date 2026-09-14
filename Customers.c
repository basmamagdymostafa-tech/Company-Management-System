#include <stdio.h>

#include "customers.h"
#include "storage.h"
#include "validation.h"

/* ==================== Customer Data ==================== */

struct Customer customers[MAX_CUSTOMERS] = {0};
s32 customerCount = 0;
s32 nextCustomerID = 1;

/* ==================== Customer Operations ==================== */

s32 findCustomerByID(s32 customerID)
{
    s32 index;

    for (index = 0; index < customerCount; index++)
    {
        if (customers[index].customerID == customerID)
        {
            return index;
        }
    }

    return -1;
}

void addCustomer(void)
{
    s32 registrationDay;
    s32 registrationMonth;
    s32 registrationYear;
    s32 status;

    printf("\n");
    printf("========================================\n");
    printf("              ADD CUSTOMER\n");
    printf("========================================\n");

    if (customerCount >= MAX_CUSTOMERS)
    {
        printf(COLOR_RED "Customer list is full!\n" COLOR_RESET);
        return;
    }

    customers[customerCount].customerID = nextCustomerID;
    nextCustomerID++;

    printf("Customer ID assigned automatically: %d\n",
           customers[customerCount].customerID);

    while (!readString("Full Name: ",
                       customers[customerCount].fullName,
                       sizeof(customers[customerCount].fullName)))
    {
    }

    while (!readString("Phone Number: ",
                       customers[customerCount].phoneNumber,
                       13))
    {
    }

    while (!validatePhone(customers[customerCount].phoneNumber))
    {
        while (!readString("Phone Number: ",
                           customers[customerCount].phoneNumber,
                           13))
        {
        }
    }

    while (!readOptionalString(
                "Email (Optional - press Enter to skip): ",
                customers[customerCount].email,
                sizeof(customers[customerCount].email)))
    {
    }

    while (customers[customerCount].email[0] != '\0' &&
            !validateEmail(customers[customerCount].email))
    {
        while (!readOptionalString(
                    "Email (Optional - press Enter to skip): ",
                    customers[customerCount].email,
                    sizeof(customers[customerCount].email)))
        {
        }
    }

    while (!readOptionalString(
                "Address (Optional - press Enter to skip): ",
                customers[customerCount].address,
                sizeof(customers[customerCount].address)))
    {
    }

    while (!readOptionalString(
                "National ID (Optional - press Enter to skip): ",
                customers[customerCount].nationalID,
                16))
    {
    }

    while (customers[customerCount].nationalID[0] != '\0' &&
            !validateNationalID(customers[customerCount].nationalID))
    {
        while (!readOptionalString(
                    "National ID (Optional - press Enter to skip): ",
                    customers[customerCount].nationalID,
                    16))
        {
        }
    }

    do
    {
        printf("\n--- Registration Date (Required) ---\n");

        while (!readInt("Enter Day (1-31): ", &registrationDay))
        {
        }

        while (!readInt("Enter Month (1-12): ", &registrationMonth))
        {
        }

        while (!readInt("Enter Year (e.g. 2026): ", &registrationYear))
        {
        }
    }
    while (!validateDate(registrationDay,
                         registrationMonth,
                         registrationYear));

    snprintf(customers[customerCount].registrationDate,
             sizeof(customers[customerCount].registrationDate),
             "%02d/%02d/%04d",
             registrationDay,
             registrationMonth,
             registrationYear);

    do
    {
        while (!readInt("Status (1 = Active, 0 = Inactive): ", &status))
        {
        }

        if (status != 0 && status != 1)
        {
            printf(COLOR_RED
                   "Invalid status! Enter 1 or 0.\n"
                   COLOR_RESET);
        }
    }
    while (status != 0 && status != 1);

    customers[customerCount].status = (u8)status;

    while (!readOptionalString(
                "Notes (Optional - press Enter to skip): ",
                customers[customerCount].notes,
                sizeof(customers[customerCount].notes)))
    {
    }

    customerCount++;
    saveCustomers();

    printf(COLOR_GREEN
           "\nCustomer added successfully!\n"
           COLOR_RESET);
}

void deleteCustomer(void)
{
    s32 customerID;
    s32 index;
    s32 shiftIndex;
    s8 choice[10];

    printf("\n");
    printf("========================================\n");
    printf("              DELETE CUSTOMER\n");
    printf("========================================\n");

    while (!readInt("Customer ID: ", &customerID))
    {
    }

    index = findCustomerByID(customerID);

    if (index == -1)
    {
        printf(COLOR_RED "Customer not found!\n" COLOR_RESET);
        return;
    }

    printf("\n========== CUSTOMER TO DELETE ==========\n");
    printf("Customer ID       : %d\n", customers[index].customerID);
    printf("Full Name         : %s\n", customers[index].fullName);
    printf("Phone Number      : %s\n", customers[index].phoneNumber);
    printf("Email             : %s\n", customers[index].email);
    printf("Address           : %s\n", customers[index].address);
    printf("National ID       : %s\n", customers[index].nationalID);
    printf("Registration Date : %s\n",
           customers[index].registrationDate);
    printf("Status            : %s\n",
           customers[index].status ? "Active" : "Inactive");
    printf("Notes             : %s\n", customers[index].notes);
    printf("========================================\n");

    while (1)
    {
        if (!readString("\nAre you sure you want to delete? (Y/N): ",
                        choice,
                        sizeof(choice)))
        {
            continue;
        }

        if (choice[0] == 'Y' || choice[0] == 'y')
        {
            break;
        }

        if (choice[0] == 'N' || choice[0] == 'n')
        {
            printf(COLOR_YELLOW
                   "Delete operation cancelled.\n"
                   COLOR_RESET);
            return;
        }

        printf(COLOR_RED
               "Invalid choice! Please enter Y or N.\n"
               COLOR_RESET);
    }

    for (shiftIndex = index; shiftIndex < customerCount - 1; shiftIndex++)
    {
        customers[shiftIndex] = customers[shiftIndex + 1];
    }

    customerCount--;
    customers[customerCount].customerID = 0;

    saveCustomers();

    printf(COLOR_GREEN
           "Customer deleted successfully!\n"
           COLOR_RESET);
}

void viewCustomer(void)
{
    s32 customerID;
    s32 index;

    printf("\n");
    printf("========================================\n");
    printf("              VIEW CUSTOMER\n");
    printf("========================================\n");

    if (customerCount == 0)
    {
        printf(COLOR_YELLOW "\nNo customers found.\n" COLOR_RESET);
        return;
    }

    while (!readInt("Customer ID: ", &customerID))
    {
    }

    index = findCustomerByID(customerID);

    if (index == -1)
    {
        printf(COLOR_RED "Customer not found!\n" COLOR_RESET);
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_CYAN COLOR_BOLD
           "                    CUSTOMER INFORMATION\n"
           COLOR_RESET);
    printf("============================================================\n");
    printf("  Customer ID       : %-36d\n",
           customers[index].customerID);
    printf("  Full Name         : %-36s\n",
           customers[index].fullName);
    printf("  Phone Number      : %-36s\n",
           customers[index].phoneNumber);
    printf("  Email             : %-36s\n",
           customers[index].email);
    printf("  Address           : %-36s\n",
           customers[index].address);
    printf("  National ID       : %-36s\n",
           customers[index].nationalID);
    printf("  Registration Date : %-36s\n",
           customers[index].registrationDate);
    printf("  Status            : %-36s\n",
           customers[index].status ? "Active" : "Inactive");
    printf("  Notes             : %-36s\n",
           customers[index].notes);
    printf("============================================================\n");
}

void viewAllCustomers(void)
{
    s32 index;

    if (customerCount == 0)
    {
        printf(COLOR_YELLOW "\nNo customers found.\n" COLOR_RESET);
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf(COLOR_CYAN COLOR_BOLD
           "                     ALL CUSTOMERS\n"
           COLOR_RESET);
    printf("============================================================\n");

    for (index = 0; index < customerCount; index++)
    {
        printf("\n");
        printf("------------------------------------------------------------\n");
        printf(" Customer %d\n", index + 1);
        printf("------------------------------------------------------------\n");
        printf("  Customer ID       : %-36d\n",
               customers[index].customerID);
        printf("  Full Name         : %-36s\n",
               customers[index].fullName);
        printf("  Phone Number      : %-36s\n",
               customers[index].phoneNumber);
        printf("  Email             : %-36s\n",
               customers[index].email);
        printf("  Address           : %-36s\n",
               customers[index].address);
        printf("  National ID       : %-36s\n",
               customers[index].nationalID);
        printf("  Registration Date : %-36s\n",
               customers[index].registrationDate);
        printf("  Status            : %-36s\n",
               customers[index].status ? "Active" : "Inactive");
        printf("  Notes             : %-36s\n",
               customers[index].notes);
        printf("------------------------------------------------------------\n");
    }

    printf("============================================================\n");
}

void updateCustomer(void)
{
    s32 customerID;
    s32 index;
    s32 choice;
    s32 registrationDay;
    s32 registrationMonth;
    s32 registrationYear;

    printf("\n");
    printf("========================================\n");
    printf("              UPDATE CUSTOMER\n");
    printf("========================================\n");

    while (!readInt("Customer ID: ", &customerID))
    {
    }

    index = findCustomerByID(customerID);

    if (index == -1)
    {
        printf(COLOR_RED "Customer not found!\n" COLOR_RESET);
        return;
    }

    printf("\nCustomer found: %s\n", customers[index].fullName);

    printf("\n========== UPDATE MENU ==========\n");
    printf("1. Full Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Address\n");
    printf("5. National ID\n");
    printf("6. Registration Date\n");
    printf("7. Status\n");
    printf("8. Notes\n");
    printf("0. Cancel\n");

    while (!readInt("Choose field: ", &choice))
    {
    }

    switch (choice)
    {
    case 1:
        while (!readString("New Full Name: ",
                           customers[index].fullName,
                           sizeof(customers[index].fullName)))
        {
        }
        break;

    case 2:
        while (!readString("New Phone Number: ",
                           customers[index].phoneNumber,
                           13))
        {
        }

        while (!validatePhone(customers[index].phoneNumber))
        {
            while (!readString("New Phone Number: ",
                               customers[index].phoneNumber,
                               13))
            {
            }
            break;

        case 3:
            while (!readString("New Email: ",
                               customers[index].email,
                               sizeof(customers[index].email)))
            {
            }

            while (!validateEmail(customers[index].email))
            {
                while (!readString("New Email: ",
                                   customers[index].email,
                                   sizeof(customers[index].email)))
                {
                }
            }
            break;

        case 4:
            while (!readString("New Address: ",
                               customers[index].address,
                               sizeof(customers[index].address)))
            {
            }
            break;

        case 5:
            while (!readString("New National ID: ",
                               customers[index].nationalID,
                               16))
            {
            }

            while (!validateNationalID(customers[index].nationalID))
            {
                while (!readString("New National ID: ",
                                   customers[index].nationalID,
                                   16))
                {
                }
            }
            break;

        case 6:
            do
            {
                printf("\n--- New Registration Date ---\n");

                while (!readInt("Enter Day (1-31): ", &registrationDay))
                {
                }

                while (!readInt("Enter Month (1-12): ",
                                &registrationMonth))
                {
                }

                while (!readInt("Enter Year (e.g. 2026): ",
                                &registrationYear))
                {
                }
            }
            while (!validateDate(registrationDay,
                                 registrationMonth,
                                 registrationYear));

            snprintf(customers[index].registrationDate,
                     sizeof(customers[index].registrationDate),
                     "%02d/%02d/%04d",
                     registrationDay,
                     registrationMonth,
                     registrationYear);
            break;

        case 7:
            do
            {
                while (!readInt(
                            "New Status (1 = Active, 0 = Inactive): ",
                            &choice))
                {
                }

                if (choice != 0 && choice != 1)
                {
                    printf(COLOR_RED
                           "Invalid status! Enter 1 or 0.\n"
                           COLOR_RESET);
                }
            }
            while (choice != 0 && choice != 1);

            customers[index].status = (u8)choice;
            break;

        case 8:
            while (!readString("New Notes: ",
                               customers[index].notes,
                               sizeof(customers[index].notes)))
            {
            }
            break;

        case 0:
            printf(COLOR_YELLOW
                   "Update cancelled.\n"
                   COLOR_RESET);
            return;

        default:
            printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
            return;
        }

        saveCustomers();

        printf(COLOR_GREEN
               "Customer updated successfully!\n"
               COLOR_RESET);
    }
}




