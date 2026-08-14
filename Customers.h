#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#define MAX_CUSTOMERS 100
#include "Config.h"
struct Customer customers[MAX_CUSTOMERS];
int customerCount;
int findCustomerByID(int);
int validateNationalID(const char *);
void addCustomer(void);
void deleteCustomer(void);
void viewCustomer(void);
void viewAllCustomers(void);
void updateCustomer(void);

#endif // CUSTOMERS_H
