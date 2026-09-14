#ifndef VALIDATION_H
#define VALIDATION_H

#include "config.h"

/* ==================== Input Helpers ==================== */

void clearInputBuffer(void);
s32 readString(const s8 *prompt, s8 *output, s32 size);
s32 readOptionalString(const s8 *prompt, s8 *output, s32 size);
s32 readInt(const s8 *prompt, s32 *number);

/* ==================== General Validators ==================== */

s32 validatePhone(const s8 *phone);
s32 validateEmail(const s8 *email);
s32 validateNationalID(const s8 *nationalID);
s32 validateDate(s32 day, s32 month, s32 year);

/* ==================== Employee Validators ==================== */

s32 validateDepartmentID(s32 departmentID);
s32 validateManagerID(s32 managerID,
                      s32 targetIndex,
                      s32 employeeID,
                      s32 departmentID);
s32 checkCircular(s32 targetIndex, s32 employeeID, s32 managerID);

#endif /* VALIDATION_H */
