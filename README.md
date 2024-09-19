
# Student Database Management System (C Program)

The Student Database Management System is a command-line C program that allows users to efficiently manage student records. The system supports adding, updating, searching, deleting, and viewing student information. Each student has a unique 6-digit Student ID, and their records are stored persistently in a file that can be accessed across multiple executions of the program.

The program stores student data in both a binary format (students.dat) and a CSV format (student_database.csv) for compatibility with spreadsheet software like Excel. Additionally, this system features a waiver calculation system that automatically calculates scholarship rates based on a student's GPA and gender, according to predefined rules.

This project is designed for educational institutions, allowing them to easily manage and track student records.


## Features

- Add Student Record:

    - Collects student information such as name, date of birth, gender, parent's names,      address, birth certificate number, GPAs, and course name.

    -   Automatically generates a unique 6-digit Student ID.

    - Validates GPA entries to ensure they are no more than 5.00.

    - Calculates a waiver percentage based on the student's GPA and gender.

    - Stores data in a binary file (students.dat) and a CSV file (student_database.     csv)     for  easy export to Excel.

- View All Student Records:

    - Displays all student records in a structured format, including details like Student ID, name, address, GPA, and waiver percentage.

- Search Student by ID:

    - Allows searching for a specific student using their unique Student ID.
- Update Student Record:

    - Enables updating existing student records using the Student ID.
- Delete Student Record:

    - Permanently removes a student record using the Student ID.
- Waiver Calculation:

    - Automatically calculates waiver percentages based on GPA and gender, following predefined rules.



## Project Features Included

- Unique Student ID Generation: A 6-digit unique Student ID is automatically generated for each new student to ensure no duplicates.
- CSV Export: Records are stored in both a binary file for system use and a CSV file for easy analysis in Excel.
- GPA Validation: Ensures GPA entries for HSC and SSC do not exceed 5.00.
- Waiver Calculation System: The program automatically calculates waiver percentages based on gender and GPA, simplifying scholarship tracking.
- Error Handling: The system ensures valid input for critical fields like GPA and Student ID and offers easy navigation through the menu.
- Persistent Storage: Records are stored in files, allowing access to data across multiple program executions.
## Installation

- Prerequisites
```
C compiler (e.g., GCC)
Compatible with Linux macOS, and Windows
```
    
## Deployment

Clone the project

```bash
  git clone https://github.com/yourusername/student-database-management-system.git
```

Go to the project directory

```bash
  cd student-database-management-system
```

Compile the Program:

```bash
  gcc -o student_db student_db.c
```

Run the Program:

```bash
  ./student_db
```


## Usage Instructions

- After running the program, you will be presented with a menu where you can:
  - Add new student records.
  - View all student records.
  - Search for a student by their Student ID.
  - Update existing student records.
  - Delete a student record by ID.
The program automatically saves data in two formats:

  - Binary Format: students.dat for internal storage.
  - CSV Format: student_database.csv for compatibility with Excel.
## Scholarship Waiver Rules

- GPA and Gender-Based Waiver:
    - GPA 5.00 (Both HSC & SSC): 100% scholarship.
    - GPA 5.00 (HSC) and 4.80 – 4.99 (SSC): 60% for Male, 75% for Female.
    - GPA 4.80 – 4.99: 50% for Male, 65% for Female.
    - GPA 4.50 – 4.79: 25% for Male, 40% for Female.
    - GPA 4.00 – 4.49: 15% for Male, 30% for Female.
    - GPA 3.50 – 3.99: 10% for Male, 25% for Female.
## Future Enhancements

- Add sorting and filtering options for student records based on GPA, course, or waiver percentage.
- Implement an admin login system for added security.
- Add a graphical user interface (GUI) for better user interaction.
## Authors

- [@RedwanHaasaan](https://github.com/RedwanHaasaan)

## 🚀 About Me
Cybersecurity expert and penetration tester.
Currently studying Computer Science and Engineering (CSE) at Northern University of Bangladesh.