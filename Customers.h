#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "config.h"

extern struct Customer customers[MAX_CUSTOMERS];
extern s32 customerCount;
extern s32 nextCustomerID;

s32 findCustomerByID(s32 customerID);
void addCustomer(void);
void deleteCustomer(void);
void viewCustomer(void);
void viewAllCustomers(void);
void updateCustomer(void);

#endif /* CUSTOMERS_H */
