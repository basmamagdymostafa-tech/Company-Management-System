#include <string.h>
#include <time.h>

#include "validation.h"
#include "employees.h"
#include "customers.h"
#include "departments.h"

/* ==================== Input Helpers ==================== */

void clearInputBuffer(void)
{
    s32 character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
        /* Discard remaining input. */
    }
}

s32 readString(const s8 *prompt, s8 *output, s32 size)
{
    s32 index;
    s32 hasCharacter;
    s32 inputComplete;

    printf("%s", prompt);

    if (fgets(output, size, stdin) == NULL)
    {
        return 0;
    }

    inputComplete = (strchr(output, '\n') != NULL);

    if (inputComplete)
    {
        output[strcspn(output, "\n")] = '\0';
    }
    else
    {
        clearInputBuffer();
        printf(COLOR_RED "Error: Input is too long.\n" COLOR_RESET);
        return 0;
    }

    if (output[0] == '\0')
    {
        printf(COLOR_RED "Error: This field cannot be empty.\n" COLOR_RESET);
        return 0;
    }

    hasCharacter = 0;

    for (index = 0; output[index] != '\0'; index++)
    {
        if (output[index] != ' ' && output[index] != '\t')
        {
            hasCharacter = 1;
            break;
        }
    }

    if (!hasCharacter)
    {
        printf(COLOR_RED
               "Error: This field cannot contain only spaces.\n"
               COLOR_RESET);
        return 0;
    }

    return 1;
}

s32 readOptionalString(const s8 *prompt, s8 *output, s32 size)
{
    s32 index;
    s32 hasCharacter;

    printf("%s", prompt);

    if (fgets(output, size, stdin) == NULL)
    {
        return 0;
    }

    if (strchr(output, '\n') == NULL)
    {
        clearInputBuffer();
        printf(COLOR_RED "Error: Input is too long.\n" COLOR_RESET);
        return 0;
    }

    output[strcspn(output, "\n")] = '\0';

    if (output[0] == '\0')
    {
        return 1;
    }

    hasCharacter = 0;

    for (index = 0; output[index] != '\0'; index++)
    {
        if (output[index] != ' ' && output[index] != '\t')
        {
            hasCharacter = 1;
            break;
        }
    }

    if (!hasCharacter)
    {
        printf(COLOR_RED
               "Error: This field cannot contain only spaces.\n"
               COLOR_RESET);
        return 0;
    }

    return 1;
}

s32 readInt(const s8 *prompt, s32 *number)
{
    s8 buffer[50];
    s32 index;
    s32 value;

    if (!readString(prompt, buffer, sizeof(buffer)))
    {
        return 0;
    }

    for (index = 0; buffer[index] != '\0'; index++)
    {
        if (buffer[index] < '0' || buffer[index] > '9')
        {
            printf(COLOR_RED "Error: Invalid numeric input.\n" COLOR_RESET);
            return 0;
        }
    }

    value = atoi(buffer);
    *number = value;

    return 1;
}

/* ==================== General Validators ==================== */

s32 validatePhone(const s8 *phone)
{
    s32 index;

    if (strlen(phone) != 11)
    {
        printf(COLOR_RED
               "Invalid phone! Must be exactly 11 digits.\n"
               COLOR_RESET);
        return 0;
    }

    if (phone[0] != '0' || phone[1] != '1')
    {
        printf(COLOR_RED
               "Invalid phone! allowed format: 01x xxxx xxxx.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0; index < 11; index++)
    {
        if (phone[index] < '0' || phone[index] > '9')
        {
            printf(COLOR_RED
                   "Invalid phone number ! Digits only.\n"
                   COLOR_RESET);
            return 0;
        }
    }

    return 1;
}

s32 validateEmail(const s8 *email)
{
    s32 index;
    s32 atIndex = -1;
    s32 dotIndex = -1;
    s32 atCount = 0;
    s32 extensionLength;

    for (index = 0; email[index] != '\0'; index++)
    {
        if (email[index] == ' ' || email[index] == '\t')
        {
            printf(COLOR_RED
                   "Invalid email: Spaces are not allowed.\n"
                   COLOR_RESET);
            return 0;
        }

        if (email[index] == '@')
        {
            atIndex = index;
            atCount++;
        }

        if (email[index] == '.')
        {
            dotIndex = index;
        }
    }

    if (atCount != 1 || atIndex <= 0 || dotIndex <= atIndex + 1)
    {
        printf(COLOR_RED
               "Invalid email format (example: user@mail.com).\n"
               COLOR_RESET);
        return 0;
    }

    extensionLength = 0;

    for (index = dotIndex + 1; email[index] != '\0'; index++)
    {
        extensionLength++;

        if ((email[index] < 'a' || email[index] > 'z') &&
                (email[index] < 'A' || email[index] > 'Z'))
        {
            printf(COLOR_RED
                   "Email extension must contain letters only.\n"
                   COLOR_RESET);
            return 0;
        }
    }

    if (extensionLength < 2 || extensionLength > 6)
    {
        printf(COLOR_RED
               "Email extension must contain 2 to 6 letters.\n"
               COLOR_RESET);
        return 0;
    }

    return 1;
}

s32 validateNationalID(const s8 *nationalID)
{
    s32 index;

    if (strlen(nationalID) != 14)
    {
        printf(COLOR_RED
               "National ID must contain exactly 14 digits.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0; nationalID[index] != '\0'; index++)
    {
        if (nationalID[index] < '0' || nationalID[index] > '9')
        {
            printf(COLOR_RED
                   "National ID must contain numbers only.\n"
                   COLOR_RESET);
            return 0;
        }
    }

    return 1;
}

s32 validateDate(s32 day, s32 month, s32 year)
{
    time_t currentTime;
    struct tm *today;
    s32 currentYear;
    s32 currentMonth;
    s32 currentDay;
    s32 daysInMonth;
    s32 isLeapYear;

    if (year < 1960 || month < 1 || month > 12 || day < 1)
    {
        printf(COLOR_RED
               "Invalid date values! Please check day/month/year.\n"
               COLOR_RESET);
        return 0;
    }

    isLeapYear = ((year % 400 == 0) ||
                  (year % 4 == 0 && year % 100 != 0));

    if (month == 2)
    {
        daysInMonth = isLeapYear ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        daysInMonth = 30;
    }
    else
    {
        daysInMonth = 31;
    }

    if (day > daysInMonth)
    {
        printf(COLOR_RED
               "Invalid day for the selected month.\n"
               COLOR_RESET);
        return 0;
    }

    currentTime = time(NULL);
    today = localtime(&currentTime);

    if (today == NULL)
    {
        return 0;
    }

    currentYear = today->tm_year + 1900;
    currentMonth = today->tm_mon + 1;
    currentDay = today->tm_mday;

    if (year > currentYear ||
            (year == currentYear && month > currentMonth) ||
            (year == currentYear &&
             month == currentMonth &&
             day > currentDay))
    {
        printf(COLOR_RED
               "Date cannot be in the future! "
               "(Today is %02d/%02d/%d)\n"
               COLOR_RESET,
               currentDay,
               currentMonth,
               currentYear);
        return 0;
    }

    return 1;
}

/* ==================== Employee Validators ==================== */

s32 validateDepartmentID(s32 departmentID)
{
    s32 index;

    for (index = 0;
            index < MAX_DEPARTMENTS &&
            department_list[index].departmentID != 0;
            index++)
    {
        if (department_list[index].departmentID == departmentID)
        {
            return 1;
        }
    }

    printf(COLOR_RED "Department ID does not exist.\n" COLOR_RESET);
    return 0;
}

s32 validateManagerID(s32 managerID,
                      s32 targetIndex,
                      s32 employeeID,
                      s32 departmentID)
{
    s32 index;

    if (managerID == 0)
    {
        return 1;
    }

    if (managerID == employeeID)
    {
        printf(COLOR_RED
               "Employee cannot manage themselves.\n"
               COLOR_RESET);
        return 0;
    }

    for (index = 0; index < targetIndex; index++)
    {
        if (employees[index].employeeID == managerID)
        {
            if (employees[index].departmentID != departmentID)
            {
                printf(COLOR_RED
                       "Invalid Manager ID! The manager must belong "
                       "to the same department.\n"
                       COLOR_RESET);
                return 0;
            }

            return 1;
        }
    }

    printf(COLOR_RED "Manager ID not found.\n" COLOR_RESET);
    return 0;
}

s32 checkCircular(s32 targetIndex, s32 employeeID, s32 managerID)
{
    s32 currentManager;
    s32 index;
    s32 foundManager;

    currentManager = managerID;

    while (currentManager != 0)
    {
        foundManager = 0;

        for (index = 0; index < targetIndex; index++)
        {
            if (employees[index].employeeID == currentManager)
            {
                foundManager = 1;

                if (employees[index].managerID == employeeID)
                {
                    printf(COLOR_RED
                           "Error: Circular reporting detected.\n"
                           COLOR_RESET);
                    return 1;
                }

                currentManager = employees[index].managerID;
                break;
            }
        }

        if (!foundManager)
        {
            break;
        }
    }

    return 0;
}
