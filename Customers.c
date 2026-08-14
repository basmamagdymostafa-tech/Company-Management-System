#include "Customers.h"
#include <stdio.h>
#include <string.h>


struct Customer customers[MAX_CUSTOMERS];
int customerCount = 0;
int validateNationalID(const char *id)
{
    int len = strlen(id);

    if (len != 14)
    {
        printf("National ID must contain exactly 14 digits.\n");
        return 0;
    }

    for (int i = 0; id[i] != '\0'; i++)
    {
        if (id[i] < '0' || id[i] > '9')
        {
            printf("National ID must contain numbers only.\n");
            return 0;
        }
    }

    return 1;
}
/* Find customer by ID */
int findCustomerByID(s32 id)
{
    int i;

    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == id)
        {
            return i;
        }
    }

    return -1;
}



/* Add Customer */
void addCustomer(void)
{
    printf("\n");
printf("========================================\n");
printf("              ADD CUSTOMER\n");
printf("========================================\n");
    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("Customer list is full!\n");
        return;
    }

    /* =========================================================
       1. Customer ID - REQUIRED
       ========================================================= */
    do
    {
        while (!readInt("Customer ID (Required): ",
                        &customers[customerCount].customerID))
        {
        }

        if (customers[customerCount].customerID <= 0)
        {
            printf("ID must be greater than 0.\n");
            continue;
        }

        if (findCustomerByID(customers[customerCount].customerID) != -1)
        {
            printf("Error: Customer ID already exists!\n");
            continue;
        }

        break;

    } while (1);


    /* =========================================================
       2. Customer Full Name - REQUIRED
       ========================================================= */
    while (!readString("Full Name (Required): ",
                       customers[customerCount].fullName,
                       sizeof(customers[customerCount].fullName)))
    {
    }


    /* =========================================================
       3. Customer Phone Number - REQUIRED
       ========================================================= */
    while (1)
    {
        printf("Phone Number (Required): ");

        if (fgets(customers[customerCount].phoneNumber,
                  13,
                  stdin) == NULL)
        {
            continue;
        }

        /* Check whether input was too long */
        if (strchr(customers[customerCount].phoneNumber, '\n') == NULL)
        {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Invalid phone! Must be exactly 11 digits.\n");
            continue;
        }

        /* Remove newline */
        customers[customerCount].phoneNumber[
            strcspn(customers[customerCount].phoneNumber, "\n")
        ] = '\0';

        if (validatePhone(customers[customerCount].phoneNumber))
        {
            break;
        }
    }


    /* =========================================================
       4. Customer Email - OPTIONAL
       ========================================================= */
    while (1)
    {
        printf("Email (Optional - press Enter to skip): ");

        if (fgets(customers[customerCount].email,
                  sizeof(customers[customerCount].email),
                  stdin) == NULL)
        {
            continue;
        }

        /* Remove newline */
        customers[customerCount].email[
            strcspn(customers[customerCount].email, "\n")
        ] = '\0';

        /* Empty input is allowed because this field is optional */
        if (customers[customerCount].email[0] == '\0')
        {
            break;
        }

        /* If something was entered, it must be a valid email */
        if (validateEmail(customers[customerCount].email))
        {
            break;
        }
    }


    /* =========================================================
       5. Customer Address - OPTIONAL
       ========================================================= */
    while (1)
    {
        printf("Address (Optional - press Enter to skip): ");

        if (fgets(customers[customerCount].address,
                  sizeof(customers[customerCount].address),
                  stdin) == NULL)
        {
            continue;
        }

        /* Remove newline */
        customers[customerCount].address[
            strcspn(customers[customerCount].address, "\n")
        ] = '\0';

        /* Empty input is allowed */
        if (customers[customerCount].address[0] == '\0')
        {
            break;
        }

        /*
         * If the user entered something, make sure it is not
         * only spaces or tabs.
         */
        int hasChar = 0;

        for (int i = 0;
             customers[customerCount].address[i] != '\0';
             i++)
        {
            if (customers[customerCount].address[i] != ' ' &&
                customers[customerCount].address[i] != '\t')
            {
                hasChar = 1;
                break;
            }
        }

        if (hasChar)
        {
            break;
        }

        printf("Address cannot contain only spaces.\n");
    }


    /* =========================================================
       6. National ID - OPTIONAL
       ========================================================= */
    while (1)
    {
        printf("National ID (Optional - press Enter to skip): ");

        if (fgets(customers[customerCount].nationalID,
                  16,
                  stdin) == NULL)
        {
            continue;
        }

        /* Check for input longer than the buffer */
        if (strchr(customers[customerCount].nationalID, '\n') == NULL)
        {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Invalid National ID! Must be exactly 14 digits.\n");
            continue;
        }

        /* Remove newline */
        customers[customerCount].nationalID[
            strcspn(customers[customerCount].nationalID, "\n")
        ] = '\0';

        /* Empty input is allowed */
        if (customers[customerCount].nationalID[0] == '\0')
        {
            break;
        }

        /* If entered, it must pass National ID validation */
        if (validateNationalID(customers[customerCount].nationalID))
        {
            break;
        }
    }


    /* =========================================================
       7. Registration Date - REQUIRED
       ========================================================= */
    int registrationDay;
    int registrationMonth;
    int registrationYear;

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

    } while (!validateDate(registrationDay,
                           registrationMonth,
                           registrationYear));

    sprintf(customers[customerCount].registrationDate,
            "%02d/%02d/%04d",
            registrationDay,
            registrationMonth,
            registrationYear);


    /* =========================================================
       8. Customer Status - REQUIRED
       ========================================================= */
    do
    {
        while (!readInt("Status (Required - 1 = Active, 0 = Inactive): ",
                        &customers[customerCount].status))
        {
        }

        if (customers[customerCount].status != 0 &&
            customers[customerCount].status != 1)
        {
            printf("Invalid status! Enter 1 or 0.\n");
        }

    } while (customers[customerCount].status != 0 &&
             customers[customerCount].status != 1);


    /* =========================================================
       9. Notes - OPTIONAL
       ========================================================= */
    while (1)
    {
        printf("Notes (Optional - press Enter to skip): ");

        if (fgets(customers[customerCount].notes,
                  sizeof(customers[customerCount].notes),
                  stdin) == NULL)
        {
            continue;
        }

        /* Remove newline */
        customers[customerCount].notes[
            strcspn(customers[customerCount].notes, "\n")
        ] = '\0';

        /* Empty input is allowed */
        if (customers[customerCount].notes[0] == '\0')
        {
            break;
        }

        /* Do not allow notes consisting only of spaces */
        int hasChar = 0;

        for (int i = 0;
             customers[customerCount].notes[i] != '\0';
             i++)
        {
            if (customers[customerCount].notes[i] != ' ' &&
                customers[customerCount].notes[i] != '\t')
            {
                hasChar = 1;
                break;
            }
        }

        if (hasChar)
        {
            break;
        }

        printf("Notes cannot contain only spaces.\n");
    }


    /* =========================================================
       Save Customer
       ========================================================= */
    customerCount++;

    saveCustomers();

    printf("\nCustomer added successfully!\n");
}



/* Delete Customer */
void deleteCustomer(void)
{
    printf("\n");
printf("========================================\n");
printf("              Delete CUSTOMER\n");
printf("========================================\n");
    s32 id;
    int index;
    int i;
    char choice[10];

    /* =========================================================
       Find Customer
       ========================================================= */
    while (!readInt("Customer ID: ", &id))
    {
    }

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }


    /* =========================================================
       Display Customer
       ========================================================= */
    printf("\n========== CUSTOMER TO DELETE ==========\n");

    printf("Customer ID       : %d\n",
           customers[index].customerID);

    printf("Full Name         : %s\n",
           customers[index].fullName);

    printf("Phone Number      : %s\n",
           customers[index].phoneNumber);

    printf("Email             : %s\n",
           customers[index].email);

    printf("Address           : %s\n",
           customers[index].address);

    printf("National ID       : %s\n",
           customers[index].nationalID);

    printf("Registration Date : %s\n",
           customers[index].registrationDate);

    printf("Status            : %s\n",
           customers[index].status ? "Active" : "Inactive");

    printf("Notes             : %s\n",
           customers[index].notes);

    printf("========================================\n");


    /* =========================================================
       Confirmation
       ========================================================= */
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
            printf("Delete operation cancelled.\n");
            return;
        }

        printf("Invalid choice! Please enter Y or N.\n");
    }


    /* =========================================================
       Delete Customer
       ========================================================= */
    for (i = index; i < customerCount - 1; i++)
    {
        customers[i] = customers[i + 1];
    }

    customerCount--;

    saveCustomers();

    printf("Customer deleted successfully!\n");
}

/* View One Customer */
void viewCustomer(void)
{
    printf("\n");
printf("========================================\n");
printf("              View CUSTOMER by ID\n");
printf("========================================\n");
    s32 id;
    int index;

    /* =========================================================
       Find Customer
       ========================================================= */
    while (!readInt("Customer ID: ", &id))
    {
    }

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }


    /* =========================================================
       Display Customer
       ========================================================= */
    printf("\n");
printf("============================================================\n");
printf("                    CUSTOMER INFORMATION\n");
printf("============================================================\n");
printf("  Customer ID       : %-36d  \n", customers[index].customerID);
printf("  Full Name         : %-36s  \n", customers[index].fullName);
printf("  Phone Number      : %-36s  \n", customers[index].phoneNumber);
printf("  Email             : %-36s  \n", customers[index].email);
printf("  Address           : %-36s  \n", customers[index].address);
printf("  National ID       : %-36s  \n", customers[index].nationalID);
printf("  Registration Date : %-36s  \n", customers[index].registrationDate);
printf("  Status            : %-36s  \n",
       customers[index].status ? "Active" : "Inactive");
printf("  Notes             : %-36s  \n", customers[index].notes);
printf("============================================================\n");
}


/* View All Customers */
void viewAllCustomers(void)
{
    int i;

    if (customerCount == 0)
    {
        printf("\nNo customers found.\n");
        return;
    }

    printf("\n");
printf("============================================================\n");
printf("                     ALL CUSTOMERS\n");
printf("============================================================\n");

for (i = 0; i < customerCount; i++)
{
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf(" Customer %d                                              \n",
           i + 1);
    printf("----------------------------------------------------------\n");
    printf("  Customer ID       : %-36d  \n", customers[i].customerID);
    printf("  Full Name         : %-36s  \n", customers[i].fullName);
    printf("  Phone Number      : %-36s  \n", customers[i].phoneNumber);
    printf("  Email             : %-36s  \n", customers[i].email);
    printf("  Address           : %-36s  \n", customers[i].address);
    printf("  National ID       : %-36s  \n", customers[i].nationalID);
    printf("  Registration Date : %-36s  \n", customers[i].registrationDate);
    printf("  Status            : %-36s  \n",
           customers[i].status ? "Active" : "Inactive");
    printf("  Notes             : %-36s  \n", customers[i].notes);
    printf("---------------------------------------------------------- \n");
}

printf("============================================================\n");
}

/* Update Customer */
void updateCustomer(void)
{
    printf("\n");
printf("========================================\n");
printf("              Update CUSTOMER\n");
printf("========================================\n");
    s32 id;
    int index;
    int choice;

    /* =========================================================
       Find Customer
       ========================================================= */
    while (!readInt("Customer ID: ", &id))
    {
    }

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("\nCustomer found: %s\n",
           customers[index].fullName);


    /* =========================================================
       Update Menu
       ========================================================= */
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
        /* =====================================================
           1. Full Name
           ===================================================== */
        case 1:

            while (!readString("New Full Name: ",
                               customers[index].fullName,
                               sizeof(customers[index].fullName)))
            {
            }

            break;


        /* =====================================================
           2. Phone Number
           ===================================================== */
        case 2:

            while (1)
            {
                printf("New Phone Number: ");

                if (fgets(customers[index].phoneNumber,
                          13,
                          stdin) == NULL)
                {
                    continue;
                }

                /* Check whether input was too long */
                if (strchr(customers[index].phoneNumber, '\n') == NULL)
                {
                    int ch;

                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }

                    printf("Invalid phone! Must be exactly 11 digits.\n");
                    continue;
                }

                /* Remove newline */
                customers[index].phoneNumber[
                    strcspn(customers[index].phoneNumber, "\n")
                ] = '\0';

                /* Validate phone number */
                if (validatePhone(customers[index].phoneNumber))
                {
                    break;
                }
            }

            break;


        /* =====================================================
           3. Email
           ===================================================== */
        case 3:

            while (1)
            {
                while (!readString("New Email: ",
                                   customers[index].email,
                                   sizeof(customers[index].email)))
                {
                }

                if (validateEmail(customers[index].email))
                {
                    break;
                }
            }

            break;


        /* =====================================================
           4. Address
           ===================================================== */
        case 4:

            while (!readString("New Address: ",
                               customers[index].address,
                               sizeof(customers[index].address)))
            {
            }

            break;


        /* =====================================================
           5. National ID
           ===================================================== */
        /* =====================================================
   5. National ID
   ===================================================== */
case 5:

    while (1)
    {
        printf("New National ID: ");

        if (fgets(customers[index].nationalID,
                  16,
                  stdin) == NULL)
        {
            continue;
        }

        /* Check whether input was too long */
        if (strchr(customers[index].nationalID, '\n') == NULL)
        {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Invalid National ID! Must be exactly 14 digits.\n");
            continue;
        }

        /* Remove newline */
        customers[index].nationalID[
            strcspn(customers[index].nationalID, "\n")
        ] = '\0';

        /* Validate National ID */
        if (validateNationalID(customers[index].nationalID))
        {
            break;
        }
    }

    break;


        /* =====================================================
           6. Registration Date
           ===================================================== */
        case 6:
        {
            int registrationDay;
            int registrationMonth;
            int registrationYear;

            do
            {
                printf("\n--- New Registration Date ---\n");

                while (!readInt("Enter Day (1-31): ",
                                &registrationDay))
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

            sprintf(customers[index].registrationDate,
                    "%02d/%02d/%04d",
                    registrationDay,
                    registrationMonth,
                    registrationYear);

            break;
        }


        /* =====================================================
           7. Status
           ===================================================== */
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
                    printf("Invalid status! Enter 1 or 0.\n");
                }

            }
            while (choice != 0 && choice != 1);

            customers[index].status = (u8)choice;

            break;


        /* =====================================================
           8. Notes
           ===================================================== */
        case 8:

            while (!readString("New Notes: ",
                               customers[index].notes,
                               sizeof(customers[index].notes)))
            {
            }

            break;


        /* =====================================================
           0. Cancel
           ===================================================== */
        case 0:

            printf("Update cancelled.\n");
            return;


        /* =====================================================
           Invalid Choice
           ===================================================== */
        default:

            printf("Invalid choice!\n");
            return;
    }


    /* =========================================================
       Save Updated Customer
       ========================================================= */
    saveCustomers();

    printf("Customer updated successfully!\n");
}
