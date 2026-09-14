#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"
#include "employees.h"
#include "customers.h"
#include "departments.h"

/* ==================== Employee Storage ==================== */

s32 saveEmployee(void)
{
    FILE *file;
    s32 index;

    file = fopen("employees.txt", "w");

    if (file == NULL)
    {
        printf(COLOR_RED
               "Error: Could not open employee file for saving.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        fprintf(file,
                "%d|%s|%s|%s|%d|%s|%d|%s|%s\n",
                employees[index].employeeID,
                employees[index].fullName,
                employees[index].phoneNumber,
                employees[index].email,
                employees[index].departmentID,
                employees[index].jobTitle,
                employees[index].managerID,
                employees[index].hiringDate,
                employees[index].employmentStatus);
    }

    fclose(file);
    saveNextIDs();

    return 1;
}

s32 loadEmployee(void)
{
    FILE *file;
    s32 index;
    s32 result;
    s32 loadedNextEmployeeID;
    s32 highestEmployeeID;

    file = fopen("employees.txt", "r");

    for (index = 0; index < MAX_EMPLOYEES; index++)
    {
        employees[index].employeeID = 0;
    }

    if (file == NULL)
    {
        return 0;
    }

    index = 0;

    while (index < MAX_EMPLOYEES)
    {
        result = fscanf(
                     file,
                     "%d|%99[^|]|%19[^|]|%99[^|]|%d|%99[^|]|%d|%19[^|]|%99[^\n]\n",
                     &employees[index].employeeID,
                     employees[index].fullName,
                     employees[index].phoneNumber,
                     employees[index].email,
                     &employees[index].departmentID,
                     employees[index].jobTitle,
                     &employees[index].managerID,
                     employees[index].hiringDate,
                     employees[index].employmentStatus);

        if (result != 9)
        {
            break;
        }

        index++;
    }

    fclose(file);

    loadedNextEmployeeID = nextEmployeeID;
    highestEmployeeID = 0;

    for (index = 0;
            index < MAX_EMPLOYEES && employees[index].employeeID != 0;
            index++)
    {
        if (employees[index].employeeID > highestEmployeeID)
        {
            highestEmployeeID = employees[index].employeeID;
        }
    }

    nextEmployeeID = highestEmployeeID + 1;

    if (loadedNextEmployeeID > nextEmployeeID)
    {
        nextEmployeeID = loadedNextEmployeeID;
    }

    return 1;
}

/* ==================== Customer Storage ==================== */

s32 saveCustomers(void)
{
    FILE *file;
    s32 index;

    file = fopen("customers.txt", "w");

    if (file == NULL)
    {
        printf(COLOR_RED
               "Error: Could not open customer file for saving.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0; index < customerCount; index++)
    {
        fprintf(file,
                "%d|%s|%s|%s|%s|%s|%s|%d|%s\n",
                customers[index].customerID,
                customers[index].fullName,
                customers[index].phoneNumber,
                customers[index].email,
                customers[index].address,
                customers[index].nationalID,
                customers[index].registrationDate,
                (s32)customers[index].status,
                customers[index].notes);
    }

    fclose(file);
    saveNextIDs();

    return 1;
}

s32 loadCustomers(void)
{
    FILE *file;
    s8 line[1000];
    s8 *start;
    s8 *end;
    s32 index;
    s32 length;
    s32 loadedNextCustomerID;
    s32 highestCustomerID;

    file = fopen("customers.txt", "r");

    customerCount = 0;

    if (file == NULL)
    {
        return 0;
    }

    index = 0;

    while (index < MAX_CUSTOMERS &&
            fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        start = line;

        /* Customer ID */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        *end = '\0';
        customers[index].customerID = atoi(start);
        start = end + 1;

        /* Full Name */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].fullName))
        {
            length = (s32)sizeof(customers[index].fullName) - 1;
        }

        strncpy(customers[index].fullName, start, length);
        customers[index].fullName[length] = '\0';
        start = end + 1;

        /* Phone Number */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].phoneNumber))
        {
            length = (s32)sizeof(customers[index].phoneNumber) - 1;
        }

        strncpy(customers[index].phoneNumber, start, length);
        customers[index].phoneNumber[length] = '\0';
        start = end + 1;

        /* Email */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].email))
        {
            length = (s32)sizeof(customers[index].email) - 1;
        }

        strncpy(customers[index].email, start, length);
        customers[index].email[length] = '\0';
        start = end + 1;

        /* Address */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].address))
        {
            length = (s32)sizeof(customers[index].address) - 1;
        }

        strncpy(customers[index].address, start, length);
        customers[index].address[length] = '\0';
        start = end + 1;

        /* National ID */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].nationalID))
        {
            length = (s32)sizeof(customers[index].nationalID) - 1;
        }

        strncpy(customers[index].nationalID, start, length);
        customers[index].nationalID[length] = '\0';
        start = end + 1;

        /* Registration Date */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(customers[index].registrationDate))
        {
            length = (s32)sizeof(customers[index].registrationDate) - 1;
        }

        strncpy(customers[index].registrationDate, start, length);
        customers[index].registrationDate[length] = '\0';
        start = end + 1;

        /* Status */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        *end = '\0';
        customers[index].status = (u8)atoi(start);
        start = end + 1;

        /* Notes */
        strncpy(customers[index].notes,
                start,
                sizeof(customers[index].notes) - 1);
        customers[index].notes[
            sizeof(customers[index].notes) - 1
        ] = '\0';

        index++;
    }

    customerCount = index;
    fclose(file);

    loadedNextCustomerID = nextCustomerID;
    highestCustomerID = 0;

    for (index = 0; index < customerCount; index++)
    {
        if (customers[index].customerID > highestCustomerID)
        {
            highestCustomerID = customers[index].customerID;
        }
    }

    nextCustomerID = highestCustomerID + 1;

    if (loadedNextCustomerID > nextCustomerID)
    {
        nextCustomerID = loadedNextCustomerID;
    }

    return 1;
}

/* ==================== Department Storage ==================== */

s32 saveDepartments(void)
{
    FILE *file;
    s32 index;

    file = fopen("departments.txt", "w");

    if (file == NULL)
    {
        printf(COLOR_RED
               "Error: Could not open departments file for saving.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0; index < total_departments; index++)
    {
        fprintf(file,
                "%d|%s|%d|%s\n",
                department_list[index].departmentID,
                department_list[index].departmentName,
                department_list[index].departmentManagerID,
                department_list[index].description);
    }

    fclose(file);
    saveNextIDs();

    return 1;
}

s32 loadDepartments(void)
{
    FILE *file;
    s8 line[500];
    s8 *start;
    s8 *end;
    s32 index;
    s32 length;
    s32 loadedNextDepartmentID;
    s32 highestDepartmentID;

    file = fopen("departments.txt", "r");

    total_departments = 0;

    if (file == NULL)
    {
        return 0;
    }

    index = 0;

    while (index < MAX_DEPARTMENTS &&
            fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        start = line;

        /* Department ID */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        *end = '\0';
        department_list[index].departmentID = atoi(start);
        start = end + 1;

        /* Department Name */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        length = (s32)(end - start);

        if (length >= (s32)sizeof(department_list[index].departmentName))
        {
            length = (s32)sizeof(department_list[index].departmentName) - 1;
        }

        strncpy(department_list[index].departmentName, start, length);
        department_list[index].departmentName[length] = '\0';
        start = end + 1;

        /* Department Manager ID */
        end = strchr(start, '|');
        if (end == NULL)
        {
            break;
        }

        *end = '\0';
        department_list[index].departmentManagerID = atoi(start);
        start = end + 1;

        /* Description */
        strncpy(department_list[index].description,
                start,
                sizeof(department_list[index].description) - 1);
        department_list[index].description[
            sizeof(department_list[index].description) - 1
        ] = '\0';

        index++;
    }

    total_departments = index;
    fclose(file);

    loadedNextDepartmentID = nextDepartmentID;
    highestDepartmentID = 0;

    for (index = 0; index < total_departments; index++)
    {
        if (department_list[index].departmentID > highestDepartmentID)
        {
            highestDepartmentID = department_list[index].departmentID;
        }
    }

    nextDepartmentID = highestDepartmentID + 1;

    if (loadedNextDepartmentID > nextDepartmentID)
    {
        nextDepartmentID = loadedNextDepartmentID;
    }

    return 1;
}

/* ==================== Automatic ID Storage ==================== */

s32 saveNextIDs(void)
{
    FILE *file;

    file = fopen("next_ids.txt", "w");

    if (file == NULL)
    {
        printf(COLOR_RED
               "Error: Could not save next ID values.\n"
               COLOR_RESET);
        return 0;
    }

    fprintf(file,
            "%d|%d|%d\n",
            nextCustomerID,
            nextEmployeeID,
            nextDepartmentID);

    fclose(file);

    return 1;
}

s32 loadNextIDs(void)
{
    FILE *file;
    s32 customerID;
    s32 employeeID;
    s32 departmentID;

    file = fopen("next_ids.txt", "r");

    if (file == NULL)
    {
        nextCustomerID = 1;
        nextEmployeeID = 1;
        nextDepartmentID = 1;
        return 0;
    }

    if (fscanf(file,
               "%d|%d|%d",
               &customerID,
               &employeeID,
               &departmentID) == 3)
    {
        nextCustomerID = customerID;
        nextEmployeeID = employeeID;
        nextDepartmentID = departmentID;
    }

    fclose(file);

    return 1;
}
