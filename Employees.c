#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Employees.h"
#include "departments.h"

struct employee employees[100] = {0};

/* ================= 1. SIMPLE INPUT HELPERS ================= */

// Clean leftover characters safely from stdin on overflow
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Reads a clean string, returns 0 if empty or error
int readString(const char *prompt, char *output, int size) {
    printf("%s", prompt);
    if (fgets(output, size, stdin) == NULL) {
        return 0;
    }
    output[strcspn(output, "\n")] = '\0'; // Remove Enter

    // 1. Check if user just hit Enter
    if (output[0] == '\0') {
        printf("Error: This field cannot be empty.\n");
        return 0;
    }

    // 2. Simple whitespace check: ensure at least one non-space character exists
    int hasChar = 0;
    for (int i = 0; output[i] != '\0'; i++) {
        if (output[i] != ' ' && output[i] != '\t') {
            hasChar = 1;
            break;
        }
    }
    if (!hasChar) {
        printf("Error: This field cannot contain only spaces.\n");
        return 0;
    }

    return 1;
}

// Reads an integer cleanly using readString + atoi
int readInt(const char *prompt, int *number) {
    char buffer[50];
    if (!readString(prompt, buffer, sizeof(buffer))) {
        return 0;
    }
    // Simple check: make sure every char is a digit
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf("Error: Invalid input!.\n");
            return 0;
        }
    }
    *number = atoi(buffer);
    return 1;
}

/* ================= 2. SIMPLE VALIDATORS ================= */

// Phone: must be digits only and reasonable length
int validatePhone(const char *phone) {
    // Check if the length is exactly 11 characters
    if (strlen(phone) != 11) {
        printf("Invalid phone! Must be exactly 11 digits.\n");
        return 0;
    }

    // Check if it starts with "01"
    if (phone[0] != '0' || phone[1] != '1') {
        printf("Invalid phone! Must start with 01.\n");
        return 0;
    }

    // Check that all characters are digits
    for (int i = 0; i<11; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            printf("Invalid phone number!.\n");
            return 0;
        }
    }

    return 1;
}
// Email: simple '@' and '.' check
int validateEmail(const char *email) {
    int atIndex = -1;
    int dotIndex = -1;
    int atCount = 0;

    for (int i = 0; email[i] != '\0'; i++) {
        // 1. No spaces allowed
        if (email[i] == ' ' || email[i] == '\t') {
            printf("Invalid email: Spaces are not allowed.\n");
            return 0;
        }

        // 2. Count and locate '@'
        if (email[i] == '@') {
            atIndex = i;
            atCount++;
        }

        // 3. Keep updating to find the LAST '.'
        if (email[i] == '.') {
            dotIndex = i;
        }
    }

    // Must have exactly ONE '@' (not first) and '.' must come after domain name
    if (atCount != 1 || atIndex <= 0 || dotIndex <= atIndex + 1) {
        printf("Invalid email format (example: user@mail.com)\n");
        return 0;
    }

    // Check extension characters & count length
    int extensionLen = 0;
    for (int i = dotIndex + 1; email[i] != '\0'; i++) {
        extensionLen++;
        if ((email[i] < 'a' || email[i] > 'z') &&
            (email[i] < 'A' || email[i] > 'Z')) {
            printf("Extension must contain letters only.\n");
            return 0;
        }
    }

    // Extension must be 2 to 6 characters (e.g., .co, .com, .online)
    if (extensionLen < 2) {
        printf("Invalid extension!\n");
        return 0;
    }

    return 1;
}

// ID uniqueness
int validateEmployeeID(int id, int targetIndex) {
    if (id <= 0) {
        printf("ID must be greater than 0.\n");
        return 0;
    }
    for (int i = 0; i < targetIndex; i++) {
        if (employees[i].employeeID == id) {
            printf("This ID already exists.\n");
            return 0;
        }
    }
    return 1;
}

// Department ID exists
int validateDepartmentID(int id) {
    for (int i = 0; department_list[i].departmentID != 0; i++) {
        if (department_list[i].departmentID == id) {
            return 1;
        }
    }
    printf("Department ID does not exist.\n");
    return 0;
}

// Manager ID exists (or 0 for top-level)
int validateManagerID(int managerID, int targetIndex, int empID) {
    if (managerID == 0) return 1;
    if (managerID == empID) {
        printf("Employee cannot manage themselves.\n");
        return 0;
    }
    for (int i = 0; i < targetIndex; i++) {
        if (employees[i].employeeID == managerID) {
            return 1;
        }
    }
    printf("Manager ID not found.\n");
    return 0;
}

// Circular reporting check
int checkCircular(int targetIndex, int empID, int managerID) {
    int cur = managerID;
    while (cur != 0) {
        for (int i = 0; i < targetIndex; i++) {
            if (employees[i].employeeID == cur) {
                if (employees[i].managerID == empID) {
                    printf("Error: Circular reporting detected.\n");
                    return 1;
                }
                cur = employees[i].managerID;
                break;
            }
        }
    }
    return 0;
}

// Simple validity checks: basic calendar limits + not in future
int validateDate(int day, int month, int year) {
    // 1. Basic sanity bounds
    if (year < 1960 || month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date values! Please check day/month/year.\n");
        return 0;
    }

    // 2. Simple month-day limit (Months with 30 days and February)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        printf("This month only has 30 days.\n");
        return 0;
    }
    if (month == 2 && day > 29) {
        printf("February cannot have more than 29 days.\n");
        return 0;
    }

    // 3. Get current date (automatically updates every day)
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    int curYear = today->tm_year + 1900;
    int curMonth = today->tm_mon + 1;
    int curDay = today->tm_mday;

    // 4. Future check
    if (year > curYear ||
       (year == curYear && month > curMonth) ||
       (year == curYear && month == curMonth && day > curDay)) {
        printf("Date cannot be in the future! (Today is %02d/%02d/%d)\n", curDay, curMonth, curYear);
        return 0;
    }

    return 1;
}

/* ================= 3. ADD EMPLOYEE ================= */

void addEmployee(void) {
    int targetIndex = -1;
    printf("\n");
    printf("========================================\n");
    printf("              ADD EMPLOYEE\n");
    printf("========================================\n");
    for (int i = 0; i < 100; i++) {
        if (employees[i].employeeID == 0) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("Employee list is full!\n");
        return;
    }

    // 1. Employee ID
    do {
        while (!readInt("Id: ", &employees[targetIndex].employeeID));
    } while (!validateEmployeeID(employees[targetIndex].employeeID, targetIndex));

    // 2. Full Name
    while (!readString("Full name: ", employees[targetIndex].fullName, sizeof(employees[targetIndex].fullName)));

    // 3. Phone Number
    do {
        while (!readString("Phone Number: ", employees[targetIndex].phoneNumber, sizeof(employees[targetIndex].phoneNumber)));
    } while (!validatePhone(employees[targetIndex].phoneNumber));

    // 4. Email
    do {
        while (!readString("Email: ", employees[targetIndex].email, sizeof(employees[targetIndex].email)));
    } while (!validateEmail(employees[targetIndex].email));

    // 5. Department ID
    int deptID;
    do {
        while (!readInt("Department ID: ", &deptID));
    } while (!validateDepartmentID(deptID));
    employees[targetIndex].departmentID = deptID;

    // 6. Job Title
    while (!readString("Job title: ", employees[targetIndex].jobTitle, sizeof(employees[targetIndex].jobTitle)));

    // 7. Manager ID
    int mgrID;
    do {
        while (!readInt("Manager ID (0 for top manager): ", &mgrID));
    } while (!validateManagerID(mgrID, targetIndex, employees[targetIndex].employeeID) ||
             checkCircular(targetIndex, employees[targetIndex].employeeID, mgrID));
    employees[targetIndex].managerID = mgrID;

    // 8. Hiring Date
    int hiringDay, hiringMonth, hiringYear;
    do {
        printf("\n--- Hiring Date ---\n");
        while (!readInt("Enter Day (1-31): ", &hiringDay));
        while (!readInt("Enter Month (1-12): ", &hiringMonth));
        while (!readInt("Enter Year (e.g. 2024): ", &hiringYear));
    } while (!validateDate(hiringDay, hiringMonth, hiringYear));
    // Formats it cleanly as "DD/MM/YYYY" into the struct string
    sprintf(employees[targetIndex].hiringDate, "%02d/%02d/%04d", hiringDay, hiringMonth, hiringYear);

    // 9. Employment Status
    while (!readString("Employment status (e.g. full-time, part-time,...etc): ", employees[targetIndex].employmentStatus, sizeof(employees[targetIndex].employmentStatus)));


    saveEmployee();
    printf("\n\033[32mEmployee added successfully!\033[0m\n\n");

}


/* ================= 4. VIEW EMPLOYEE ================= */

void viewEmployee(void)
{
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

    int viewOption = 0;
    int findEmp = 0;
    int startIndex = 0;
    int endIndex = 0;

    printf("\n");
    printf("============================================================\n");
    printf("                  EMPLOYEE VIEW OPTIONS\n");
    printf("============================================================\n");
    printf("  1. View Specific Employee (by ID)                          \n");
    printf("  2. View All Employees                                      \n");
    printf("============================================================\n\n");

    do
    {
        if (readInt("Enter your choice (1-2): ", &viewOption))
        {
            if (viewOption == 1 || viewOption == 2)
            {
                break;
            }
        }

        printf("Invalid choice! Please enter 1 or 2.\n");
    } while (1);

    switch (viewOption)
    {
        case 1:

            while (1)
            {
                if (!readInt("Employee ID you are searching for: ",
                             &findEmp))
                {
                    continue;
                }

                if (findEmp <= 0)
                {
                    printf("Invalid Employee ID! ID must be greater than 0.\n");
                    continue;
                }

                break;
            }

            int foundIndex = -1;

            for (int i = 0;
                 i < 100 && employees[i].employeeID != 0;
                 i++)
            {
                if (employees[i].employeeID == findEmp)
                {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex == -1)
            {
                printf("\nEmployee ID %d not found.\n", findEmp);
                return;
            }

            startIndex = foundIndex;
            endIndex = foundIndex + 1;

            break;

        case 2:
            startIndex = 0;
            endIndex = 100;
            break;

        default:
            return;
    }

    for (int i = startIndex;
         i < endIndex && employees[i].employeeID != 0;
         i++)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                    EMPLOYEE %d INFORMATION\n" , i+1 );
        printf("============================================================\n");
        printf("  Employee ID        : %-34d  \n", employees[i].employeeID);
        printf("  Full Name          : %-34s  \n", employees[i].fullName);
        printf("  Phone Number       : %-34s  \n", employees[i].phoneNumber);
        printf("  Email              : %-34s  \n", employees[i].email);
        printf("  Department ID      : %-34d  \n", employees[i].departmentID);
        printf("  Job Title          : %-34s  \n", employees[i].jobTitle);
        printf("  Employment Status  : %-34s  \n", employees[i].employmentStatus);
        printf("  Hiring Date        : %-34s  \n", employees[i].hiringDate);

        if (employees[i].managerID == 0)
        {
            printf("  Manager ID         : %-34s  \n", "None");
        }
        else
        {
            printf("  Manager ID         : %-34d  \n", employees[i].managerID);
        }

        printf("============================================================\n");
    }
}







