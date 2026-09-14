# Company Management System

A **C programming final project** developed as part of the **Embedded Systems Diploma at Telecom Egypt (WE)**.

The project implements a console-based Company Management System for managing employees, customers, departments, and organizational reporting relationships — built with core C: structures, arrays, functions, pointers, file handling, input validation, modular programming, and hierarchical data relationships.

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

### 👨‍💼 Employee Management

* Add employees
* Automatically assign a unique Employee ID
* View a specific employee
* Assign employees to existing departments
* Assign managers to employees
* Maintain employee-manager relationships

Employee information includes:

* Employee ID
* Full name
* Phone number & email
* Department ID
* Job title
* Manager ID
* Hiring date
* Employment status

### 🏢 Department Management

* Add departments
* Automatically assign Department IDs
* View a specific department
* Assign department managers
* View employees belonging to a department

Each department contains:

* Department ID
* Department name
* Department manager
* Description

### 🌳 Employee Hierarchy

The system supports organizational reporting structures. It can display:

**Direct Reports** — employees who report directly to a selected employee.

**Employee Hierarchy** — the selected employee plus all direct *and* indirect reports below them, printed as an indented tree.

```text
Department Manager
│
├── Employee A
│   └── Employee B
│       └── Employee C
│
└── Employee D
```

The system also checks for **circular reporting relationships** to prevent invalid management structures (an employee never ends up managing themselves, directly or indirectly).

---

## ✅ Input Validation

A dedicated `validation.c` / `validation.h` module handles input validation throughout the system, including required/optional string input, integer input, and field-specific rules:

* **Phone number** — exactly 11 digits, must start with `01` (Egyptian-style: `01x xxxx xxxx`)
* **National ID** — exactly 14 numeric digits
* **Email** — exactly one `@`, a `.` after it, and a 2–6 letter extension (e.g. `user@mail.com`), no spaces
* **Date** — must be a real calendar date and cannot be in the future
* **Department ID** — must reference an existing department
* **Manager ID** — must reference an existing employee, must belong to the **same department** as the employee being assigned, and an employee cannot be their own manager
* **Circular reporting** — rejected if assigning a manager would create a loop anywhere up the chain

---

## 💾 Data Persistence

The system uses **text files** so data isn't lost when the program closes:

```text
employees.txt
customers.txt
departments.txt
next_ids.txt
```

Existing data is loaded from these files on startup, and saved back automatically on exit (menu option `0`). `next_ids.txt` preserves the next auto-generated ID for each entity across runs.

---

## 📂 Project Structure

```text
company_management_system/
│
├── main.c
│
├── config.c / config.h
├── employees.c / employees.h
├── customers.c / customers.h
├── departments.c / departments.h
├── hierarchy.c / hierarchy.h
├── storage.c / storage.h
├── validation.c / validation.h
│
├── employees.txt
├── customers.txt
├── departments.txt
├── next_ids.txt
│
└── README.md
```

### Module Responsibilities

| File               | Purpose                                            |
|--------------------|-----------------------------------------------------|
| `main.c`           | Main program and menu system                       |
| `config.c/h`       | Shared types, struct definitions, limits, console utilities |
| `employees.c/h`    | Employee management                                |
| `customers.c/h`    | Customer management                                |
| `departments.c/h`  | Department management                              |
| `hierarchy.c/h`    | Employee reporting hierarchy                       |
| `storage.c/h`      | Saving and loading data                            |
| `validation.c/h`   | Input reading and data validation                  |

### Capacity Limits

Defined in `config.h` (adjustable at compile time):

* `MAX_EMPLOYEES` = 100
* `MAX_CUSTOMERS` = 100
* `MAX_DEPARTMENTS` = 50

---

## 🖥️ Main Menu

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

0. Exit (saves and quits)
```

---

## 🚀 Recommended Setup Sequence

Because employees must belong to an existing department, and a manager must share the employee's department, the recommended order is:

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

Customers can be managed independently at any point.

---

## 🛠️ Technologies & Concepts Used

**Language:** C

**Concepts demonstrated:**

* Structures & arrays
* Functions, header files & modular programming
* Pointers & strings
* File I/O and persistent storage
* Automatic/unique ID generation
* Searching and record relationships (employee ↔ department ↔ manager)
* Input and data validation
* Error handling
* Hierarchical / recursive data structures (organizational tree)

---

## 🎯 Project Objectives

* Build a complete console-based application in C.
* Practice modular programming by separating functionality into reusable modules.
* Implement reliable, defensive user input validation.
* Use structures and arrays to represent real-world entities (employees, customers, departments).
* Implement persistent storage using files.
* Generate and maintain unique, file-backed record IDs.
* Model relationships between employees, departments, and managers.
* Implement and traverse an organizational hierarchy.
* Prevent invalid and circular reporting relationships.

---
