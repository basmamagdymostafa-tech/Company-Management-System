#ifndef STORAGE_H
#define STORAGE_H

#include "config.h"

s32 saveEmployee(void);
s32 loadEmployee(void);

s32 saveCustomers(void);
s32 loadCustomers(void);

s32 saveDepartments(void);
s32 loadDepartments(void);

s32 saveNextIDs(void);
s32 loadNextIDs(void);

#endif /* STORAGE_H */
