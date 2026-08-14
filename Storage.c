#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Storage.h"
#include "Employees.h"
#include "Customers.h"
#include "departments.h"

int saveEmployee(void)
{
    FILE *file;
    int i;

    file = fopen("employees.txt", "w");

    if (file == NULL)
    {
        printf("Error: Could not open employee file for saving.\n");
        return 0;
    }

    for (i = 0; i < 100; i++)
    {
        if (employees[i].employeeID == 0)
        {
            break;
        }

        // Order: ID, Name, Phone, Email, Dept, JobTitle, ManagerID, HiringDate, Status
        fprintf(file, "%d|%s|%s|%s|%d|%s|%d|%s|%s\n",
                employees[i].employeeID,
                employees[i].fullName,
                employees[i].phoneNumber,
                employees[i].email,
                employees[i].departmentID,
                employees[i].jobTitle,
                employees[i].managerID,
                employees[i].hiringDate,
                employees[i].employmentStatus);
    }

    fclose(file);
    return 1;
}

int loadEmployee(void)
{
    FILE *file;
    int i = 0;

    file = fopen("employees.txt", "r");

    if (file == NULL)
    {
        /* No file means there are no saved employees */
        for (i = 0; i < 100; i++)
        {
            employees[i].employeeID = 0;
        }
        return 0;
    }

    /* Clear the array before loading */
    for (i = 0; i < 100; i++)
    {
        employees[i].employeeID = 0;
    }

    i = 0;

    while (i < 100)
    {
        int result;

        // Corrected format string to read all 9 attributes matching fprintf exactly
        result = fscanf(file,
                        "%d|%99[^|]|%99[^|]|%99[^|]|%d|%99[^|]|%d|%99[^|]|%99[^\n]\n",
                        &employees[i].employeeID,
                        employees[i].fullName,
                        employees[i].phoneNumber,
                        employees[i].email,
                        &employees[i].departmentID,
                        employees[i].jobTitle,
                        &employees[i].managerID,
                        employees[i].hiringDate,
                        employees[i].employmentStatus);

        // Must check for 9 successful matches instead of 7
        if (result != 9)
        {
            break;
        }

        i++;
    }

    fclose(file);
    return 1;
}
/*-------------------------------------------------------------------*/
int saveCustomers(void)
{
    FILE *file;
    int i;

    file = fopen("customers.txt", "w");

    if (file == NULL)
    {
        printf("Error: Could not open customer file for saving.\n");
        return 0;
    }

    for (i = 0; i < customerCount; i++)
    {
        fprintf(file,
                "%d|%s|%s|%s|%s|%s|%s|%u|%s\n",
                customers[i].customerID,
                customers[i].fullName,
                customers[i].phoneNumber,
                customers[i].email,
                customers[i].address,
                customers[i].nationalID,
                customers[i].registrationDate,
                customers[i].status,
                customers[i].notes);
    }

    fclose(file);

    return 1;
}

/*---------------------------------------------------------------------*/
int loadCustomers(void)
{
    FILE *file;
    char line[1000];
    int i = 0;

    file = fopen("customers.txt", "r");

    if (file == NULL)
    {
        customerCount = 0;
        return 0;
    }

    customerCount = 0;

    while (i < MAX_CUSTOMERS && fgets(line, sizeof(line), file) != NULL)
    {
        char *start;
        char *end;
        int length;

        /* Remove newline */
        line[strcspn(line, "\n")] = '\0';

        start = line;

        /* =====================================================
           Customer ID
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        *end = '\0';

        customers[i].customerID = atoi(start);

        start = end + 1;


        /* =====================================================
           Full Name
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].fullName))
            length = sizeof(customers[i].fullName) - 1;

        strncpy(customers[i].fullName, start, length);
        customers[i].fullName[length] = '\0';

        start = end + 1;


        /* =====================================================
           Phone Number
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].phoneNumber))
            length = sizeof(customers[i].phoneNumber) - 1;

        strncpy(customers[i].phoneNumber, start, length);
        customers[i].phoneNumber[length] = '\0';

        start = end + 1;


        /* =====================================================
           Email
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].email))
            length = sizeof(customers[i].email) - 1;

        strncpy(customers[i].email, start, length);
        customers[i].email[length] = '\0';

        start = end + 1;


        /* =====================================================
           Address
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].address))
            length = sizeof(customers[i].address) - 1;

        strncpy(customers[i].address, start, length);
        customers[i].address[length] = '\0';

        start = end + 1;


        /* =====================================================
           National ID
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].nationalID))
            length = sizeof(customers[i].nationalID) - 1;

        strncpy(customers[i].nationalID, start, length);
        customers[i].nationalID[length] = '\0';

        start = end + 1;


        /* =====================================================
           Registration Date
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(customers[i].registrationDate))
            length = sizeof(customers[i].registrationDate) - 1;

        strncpy(customers[i].registrationDate, start, length);
        customers[i].registrationDate[length] = '\0';

        start = end + 1;


        /* =====================================================
           Status
           ===================================================== */
        end = strchr(start, '|');

        if (end == NULL)
            break;

        *end = '\0';

        customers[i].status = (u8)atoi(start);

        start = end + 1;


        /* =====================================================
           Notes
           ===================================================== */
        strncpy(customers[i].notes,
                start,
                sizeof(customers[i].notes) - 1);

        customers[i].notes[
            sizeof(customers[i].notes) - 1
        ] = '\0';


        /* Customer loaded successfully */
        i++;
    }

    customerCount = i;

    fclose(file);

    return 1;
}
int saveDepartments(void)
{
    FILE *file;
    int i;

    file = fopen("departments.txt", "w");

    if (file == NULL)
    {
        printf("Error: Could not open departments.txt for saving.\n");
        return 0;
    }

    for (i = 0; i < total_departments; i++)
    {
        fprintf(file,
                "%d|%s|%d|%s\n",
                department_list[i].departmentID,
                department_list[i].departmentName,
                department_list[i].departmentManagerID,
                department_list[i].description);
    }

    fclose(file);

    return 1;
}

int loadDepartments(void)
{
    FILE *file;
    char line[500];
    int i = 0;

    file = fopen("departments.txt", "r");

    if (file == NULL)
    {
        total_departments = 0;
        return 0;
    }

    total_departments = 0;

    while (i < MAX_DEPARTMENTS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        char *start;
        char *end;
        int length;

        /* Remove newline */
        line[strcspn(line, "\n")] = '\0';

        start = line;

        /* ================= Department ID ================= */

        end = strchr(start, '|');

        if (end == NULL)
            break;

        *end = '\0';

        department_list[i].departmentID = atoi(start);

        start = end + 1;

        /* ================= Department Name ================= */

        end = strchr(start, '|');

        if (end == NULL)
            break;

        length = end - start;

        if (length >= sizeof(department_list[i].departmentName))
            length = sizeof(department_list[i].departmentName) - 1;

        strncpy(department_list[i].departmentName,
                start,
                length);

        department_list[i].departmentName[length] = '\0';

        start = end + 1;

        /* ================= Manager ID ================= */

        end = strchr(start, '|');

        if (end == NULL)
            break;

        *end = '\0';

        department_list[i].departmentManagerID = atoi(start);

        start = end + 1;

        /* ================= Description ================= */

        strncpy(department_list[i].description,
                start,
                sizeof(department_list[i].description) - 1);

        department_list[i].description[
            sizeof(department_list[i].description) - 1
        ] = '\0';

        i++;
    }

    total_departments = i;

    fclose(file);

    return 1;
}
