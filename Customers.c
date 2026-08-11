#include "Customers.h"
#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100

struct Customer customers[MAX_CUSTOMERS];
int customerCount = 0;


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


/* Read string */
void readString(char str[], int size)
{
    fgets(str, size, stdin);

    str[strcspn(str, "\n")] = '\0';
}


/* Add Customer */
void addCustomer(void)
{
    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("Customer list is full!\n");
        return;
    }

    s32 id;

    printf("\nEnter Customer ID: ");
    scanf("%d", &id);
    getchar();

    if (findCustomerByID(id) != -1)
    {
        printf("Error: Customer ID already exists!\n");
        return;
    }

    customers[customerCount].customerID = id;

    printf("Enter Full Name: ");
    readString(customers[customerCount].fullName, 100);

    printf("Enter Phone Number: ");
    readString(customers[customerCount].phoneNumber, 11);

    printf("Enter Email: ");
    readString(customers[customerCount].email, 100);

    printf("Enter Address: ");
    readString(customers[customerCount].address, 200);

    printf("Enter National ID: ");
    readString(customers[customerCount].nationalID, 14);

    printf("Enter Registration Date: ");
    readString(customers[customerCount].registrationDate, 20);

    printf("Enter Status (1 = Active, 0 = Inactive): ");
    scanf("%hhu", &customers[customerCount].status);
    getchar();

    printf("Enter Notes: ");
    readString(customers[customerCount].notes, 300);

    customerCount++;

    printf("\nCustomer added successfully!\n");
}


/* Delete Customer */
void deleteCustomer(void)
{
    s32 id;
    int index;
    int i;
    char choice;

    printf("\nEnter Customer ID to delete: ");
    scanf("%d", &id);
    getchar();

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("\nCustomer found:\n");
    printf("ID: %d\n", customers[index].customerID);
    printf("Name: %s\n", customers[index].fullName);
    printf("Phone: %s\n", customers[index].phoneNumber);

    printf("\nAre you sure you want to delete? (Y/N): ");
    scanf("%c", &choice);
    getchar();

    if (choice == 'Y' || choice == 'y')
    {
        for (i = index; i < customerCount - 1; i++)
        {
            customers[i] = customers[i + 1];
        }

        customerCount--;

        printf("Customer deleted successfully!\n");
    }
    else
    {
        printf("Delete operation cancelled.\n");
    }
}


/* View One Customer */
void viewCustomer(void)
{
    s32 id;
    int index;

    printf("\nEnter Customer ID: ");
    scanf("%d", &id);
    getchar();

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("\n========== CUSTOMER ==========\n");

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

    printf("==============================\n");
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

    printf("\n========== ALL CUSTOMERS ==========\n");

    for (i = 0; i < customerCount; i++)
    {
        printf("\nCustomer %d\n", i + 1);

        printf("ID    : %d\n", customers[i].customerID);
        printf("Name  : %s\n", customers[i].fullName);
        printf("Phone : %s\n", customers[i].phoneNumber);
        printf("Email : %s\n", customers[i].email);
        printf("Status: %s\n",
               customers[i].status ? "Active" : "Inactive");
    }

    printf("\n===================================\n");
}


/* Update Customer */
void updateCustomer(void)
{
    s32 id;
    int index;
    int choice;

    printf("\nEnter Customer ID: ");
    scanf("%d", &id);
    getchar();

    index = findCustomerByID(id);

    if (index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("\nCustomer found: %s\n",
           customers[index].fullName);

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

    printf("Choose field: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
            printf("Enter new Full Name: ");
            readString(customers[index].fullName, 100);
            break;

        case 2:
            printf("Enter new Phone Number: ");
            readString(customers[index].phoneNumber, 11);
            break;

        case 3:
            printf("Enter new Email: ");
            readString(customers[index].email, 100);
            break;

        case 4:
            printf("Enter new Address: ");
            readString(customers[index].address, 200);
            break;

        case 5:
            printf("Enter new National ID: ");
            readString(customers[index].nationalID, 14);
            break;

        case 6:
            printf("Enter new Registration Date: ");
            readString(customers[index].registrationDate, 20);
            break;

        case 7:
            printf("Enter new Status (1 = Active, 0 = Inactive): ");
            scanf("%hhu", &customers[index].status);
            getchar();
            break;

        case 8:
            printf("Enter new Notes: ");
            readString(customers[index].notes, 300);
            break;

        case 0:
            printf("Update cancelled.\n");
            return;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("Customer updated successfully!\n");
}