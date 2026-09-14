# Company Management System
A **C programming final project** developed as part of the **Embedded Systems Diploma at Telecom Egypt**.

The project implements a console-based Company Management System for managing employees, customers, departments, and organizational reporting relationships.

It focuses on applying core C programming concepts such as **structures, arrays, functions, pointers, file handling, input validation, modular programming, and hierarchical data relationships**.

---

## 📌 Features

### 👤 Customer Management

* Add a new customer
* Automatically assign a unique Customer ID
* Delete customers
* View a specific customer by ID
* View all customers
* Update customer information
* Store customer information permanently using files

Customer information includes:

* Customer ID
* Full name
* Phone number
* Email
* Address
* National ID
* Registration date
* Status
* Notes

---

### 👨‍💼 Employee Management

* Add employees
* Automatically assign a unique Employee ID
* View a specific employee
* View all employees
* Assign employees to existing departments
* Assign managers to employees
* Maintain employee-manager relationships

Employee information includes details such as:

* Employee ID
* Full name
* Job title
* Department
* Manager
* Hiring date
* Contact information

---

### 🏢 Department Management

* Add departments
* Automatically assign Department IDs
* View a specific department
* View all departments
* Assign department managers
* View employees belonging to a department

Each department can contain:

* Department ID
* Department name
* Department manager
* Description

---

### 🌳 Employee Hierarchy

The system supports organizational reporting structures.

It can display:

**Direct Reports**

* Employees who directly report to a selected employee.

**Employee Hierarchy**

* The selected employee
* Direct reports
* Indirect reports at lower levels

Example:

```text
Department Manager
│
├── Employee A
│   └── Employee B
│       └── Employee C
│
└── Employee D
```

The system also checks for **circular reporting relationships** to prevent invalid management structures.

---

## ✅ Input Validation

A dedicated `validation.c` / `validation.h` module handles input validation throughout the system.

Validation includes:

* Required and optional string input
* Integer input
* Phone numbers
* Email addresses
* National IDs
* Dates
* Department IDs
* Manager IDs
* Employee-manager relationships
* Circular reporting relationships

Examples of validation rules:

* Egyptian-style phone numbers must contain **11 digits** and start with `01`.
* National IDs must contain **14 digits**.
* Email addresses must follow a basic valid format.
* Dates cannot be in the future.
* An employee cannot manage themselves.
* A manager must belong to the same department as the employee.
* Circular reporting relationships are rejected.

---

## 💾 Data Persistence

The system uses **text files** to save information so that data is not lost when the program closes.

The following files are used:

```text
employees.txt
customers.txt
departments.txt
next_ids.txt
```

When the program starts, existing data is loaded from these files.

When records are added or modified, the relevant information is saved back to the files.

The `next_ids.txt` file is used to preserve automatically generated IDs.

---

## 📂 Project Structure

```text
company_management_system/
│
├── main.c
│
├── config.c
├── config.h
│
├── employees.c
├── employees.h
│
├── customers.c
├── customers.h
│
├── departments.c
├── departments.h
│
├── hierarchy.c
├── hierarchy.h
│
├── storage.c
├── storage.h
│
├── validation.c
├── validation.h
│
└── README.md
```

### Module Responsibilities

| File              | Purpose                                            |
| ----------------- | -------------------------------------------------- |
| `main.c`          | Main program and menu system                       |
| `config.c/h`      | Common configuration, data types, screen utilities |
| `employees.c/h`   | Employee management                                |
| `customers.c/h`   | Customer management                                |
| `departments.c/h` | Department management                              |
| `hierarchy.c/h`   | Employee reporting hierarchy                       |
| `storage.c/h`     | Saving and loading data                            |
| `validation.c/h`  | Input and data validation                          |

---

## 🖥️ Main Menu

When the program runs, the user can choose from:

```text
1.  Add Customer
2.  Delete Customer
3.  View Customer
4.  View All Customers
5.  Update Customer

6.  Add Employee
7.  View Employee

8.  Add Department
9.  View Department
10. Assign Department Manager
11. View Department Employees

12. View Direct Reports
13. View Employee Hierarchy

0. Exit
```

---

## 🚀 Recommended Setup Sequence

Because employees must belong to an existing department, the recommended order is:

```text
1. Add a Department
        ↓
2. Add Employees
        ↓
3. Assign a Department Manager
        ↓
4. Define Employee-Manager Relationships
        ↓
5. View the Organizational Hierarchy
```

Customers can be managed independently.

---

## 🛠️ Technologies & Concepts Used

The project is written in:

**C Programming Language**

It demonstrates:

* Structures
* Arrays
* Functions
* Header files
* Modular programming
* Pointers
* Strings
* Input/output
* File handling
* Dynamic relationships between records
* Searching
* Data validation
* Error handling
* Hierarchical data structures
* Persistent storage
* Automatic ID generation

---

## 🎯 Project Objectives

The main objectives of this project are to:

* Build a complete console-based application using C.
* Practice modular programming.
* Separate functionality into reusable modules.
* Implement reliable user input validation.
* Work with structures and arrays to represent real-world entities.
* Implement persistent storage using files.
* Generate and maintain unique record IDs.
* Model relationships between employees, departments, and managers.
* Implement an organizational hierarchy.
* Prevent invalid and circular reporting relationships.

---
