/*
Author: Redwan Hasan
Email: redwanhasan.workspace@gmail.com
Project Name: Student Database Management System
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_COURSE_LENGTH 50
#define MAX_CERT_NO_LENGTH 20
#define DATE_LENGTH 11

// Structure to store student information
struct Student {
    int student_id;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char dob[DATE_LENGTH];
    char gender;   // 'M' for Male, 'F' for Female
    char father_name[MAX_NAME_LENGTH];
    char mother_name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char birth_cert_no[MAX_CERT_NO_LENGTH];
    float hsc_gpa;
    float ssc_gpa;
    int hsc_year;
    int ssc_year;
    char course_name[MAX_COURSE_LENGTH];
    float scholarship_rate; // Waiver rate based on GPA and gender
};

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void backToMenu();
int generateUniqueID();
void calculateWaiver(struct Student *s);
int validateGPA(float gpa);
void exportToCSV(struct Student s);
void promptForGPA(float *gpa, const char *exam_name);

// Global file pointer for binary file operations
FILE *fp;

// Main menu
void menu() {
    int choice;
    while (1) {
        printf("\n========== Student Database Management System ==========\n");
        printf("1. Add Student Record\n");
        printf("2. View All Student Records\n");
        printf("3. Search Student Record by Student ID\n");
        printf("4. Update Student Record by Student ID\n");
        printf("5. Delete Student Record by Student ID\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0); break;
            default: printf("Invalid choice, please try again.\n");
        }
    }
}

// Function to generate a unique 6-digit Student ID
int generateUniqueID() {
    int id;
    struct Student s;

    srand(time(0));  // Initialize random seed
    FILE *temp_fp = fopen("students.dat", "rb");
    
    // Continuously generate until a unique ID is found
    do {
        id = rand() % 900000 + 100000; // Generate 6-digit number
        if (temp_fp != NULL) {
            int found = 0;
            while (fread(&s, sizeof(s), 1, temp_fp)) {
                if (s.student_id == id) {
                    found = 1;
                    break;
                }
            }
            if (!found) break;
        } else {
            break; // File doesn't exist, ID is unique
        }
    } while (1);

    fclose(temp_fp);
    return id;
}

// Function to calculate waiver based on GPA and gender
void calculateWaiver(struct Student *s) {
    if (s->hsc_gpa >= 5.00 && s->ssc_gpa >= 5.00) {
        s->scholarship_rate = 100.0;
    } else if (s->hsc_gpa >= 5.00 && s->ssc_gpa >= 4.80) {
        s->scholarship_rate = (s->gender == 'F') ? 75.0 : 60.0;
    } else if (s->hsc_gpa >= 4.80 && s->ssc_gpa >= 4.50) {
        s->scholarship_rate = (s->gender == 'F') ? 65.0 : 50.0;
    } else if (s->hsc_gpa >= 4.50 && s->ssc_gpa >= 4.00) {
        s->scholarship_rate = (s->gender == 'F') ? 40.0 : 25.0;
    } else if (s->hsc_gpa >= 4.00 && s->ssc_gpa >= 3.50) {
        s->scholarship_rate = (s->gender == 'F') ? 30.0 : 15.0;
    } else if (s->hsc_gpa >= 3.50 && s->ssc_gpa >= 3.00) {
        s->scholarship_rate = (s->gender == 'F') ? 25.0 : 10.0;
    } else {
        s->scholarship_rate = 0.0;
    }
}

// Function to export data to CSV
void exportToCSV(struct Student s) {
    FILE *csv_fp = fopen("student_database.csv", "a");  // Append mode
    if (csv_fp == NULL) {
        printf("Error opening CSV file!\n");
        return;
    }

    // Write header if CSV is empty
    if (ftell(csv_fp) == 0) {
        fprintf(csv_fp, "Student ID,Name,Date of Birth,Gender,Father's Name,Mother's Name,Address,Birth Certificate No,HSC GPA,HSC Year,SSC GPA,SSC Year,Course Name,Scholarship Rate\n");
    }

    // Write the student data in CSV format
    fprintf(csv_fp, "%d,%s %s,%s,%c,%s,%s,%s,%s,%.2f,%d,%.2f,%d,%s,%.2f%%\n",
            s.student_id, s.first_name, s.last_name, s.dob, s.gender, s.father_name, s.mother_name,
            s.address, s.birth_cert_no, s.hsc_gpa, s.hsc_year, s.ssc_gpa, s.ssc_year, s.course_name, s.scholarship_rate);

    fclose(csv_fp);  // Close the CSV file
}

// Function to validate GPA
int validateGPA(float gpa) {
    return gpa <= 5.0;
}

// Prompt for GPA and validate
void promptForGPA(float *gpa, const char *exam_name) {
    do {
        printf("Enter %s GPA: ", exam_name);
        scanf("%f", gpa);
        if (!validateGPA(*gpa)) {
            printf("Error: GPA cannot be more than 5.0. Please re-enter.\n");
        }
    } while (!validateGPA(*gpa));
}

// Function to add a student record
void addStudent() {
    struct Student s;
    fp = fopen("students.dat", "ab");  // Append mode for binary file
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    s.student_id = generateUniqueID();  // Generate unique student ID
    printf("\nGenerated Student ID: %d\n", s.student_id);

    printf("Enter First Name: ");
    getchar();  // To consume the newline character left by scanf
    fgets(s.first_name, MAX_NAME_LENGTH, stdin);
    s.first_name[strcspn(s.first_name, "\n")] = '\0';  // Remove trailing newline

    printf("Enter Last Name: ");
    fgets(s.last_name, MAX_NAME_LENGTH, stdin);
    s.last_name[strcspn(s.last_name, "\n")] = '\0';

    printf("Enter Date of Birth (dd/mm/yyyy): ");
    fgets(s.dob, DATE_LENGTH, stdin);
    s.dob[strcspn(s.dob, "\n")] = '\0';

    printf("Enter Gender (M/F): ");
    scanf(" %c", &s.gender);

    printf("Enter Father's Name: ");
    getchar();  // To consume newline
    fgets(s.father_name, MAX_NAME_LENGTH, stdin);
    s.father_name[strcspn(s.father_name, "\n")] = '\0';

    printf("Enter Mother's Name: ");
    fgets(s.mother_name, MAX_NAME_LENGTH, stdin);
    s.mother_name[strcspn(s.mother_name, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(s.address, MAX_ADDRESS_LENGTH, stdin);
    s.address[strcspn(s.address, "\n")] = '\0';

    printf("Enter Birth Certificate Number: ");
    fgets(s.birth_cert_no, MAX_CERT_NO_LENGTH, stdin);
    s.birth_cert_no[strcspn(s.birth_cert_no, "\n")] = '\0';

    promptForGPA(&s.hsc_gpa, "HSC");
    printf("Enter HSC Passing Year: ");
    scanf("%d", &s.hsc_year);

    promptForGPA(&s.ssc_gpa, "SSC");
    printf("Enter SSC Passing Year: ");
    scanf("%d", &s.ssc_year);

    printf("Enter Course Name: ");
    getchar();  // Consume newline
    fgets(s.course_name, MAX_COURSE_LENGTH, stdin);
    s.course_name[strcspn(s.course_name, "\n")] = '\0';

    // Calculate waiver based on GPA and gender
    calculateWaiver(&s);

    // Write student record to binary file
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    // Export the student record to the CSV file
    exportToCSV(s);

    printf("Student record added successfully!\n");
    printf("Scholarship Rate: %.2f%%\n", s.scholarship_rate);
    backToMenu();
}

// Function to view all student records
void viewStudents() {
    struct Student s;
    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n========== All Student Records ==========\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nStudent ID: %d\nName: %s %s\nDate of Birth: %s\nGender: %c\nFather's Name: %s\nMother's Name: %s\nAddress: %s\nBirth Certificate No: %s\nHSC GPA: %.2f\nHSC Passing Year: %d\nSSC GPA: %.2f\nSSC Passing Year: %d\nCourse Name: %s\nScholarship Rate: %.2f%%\n",
               s.student_id, s.first_name, s.last_name, s.dob, s.gender, s.father_name, s.mother_name,
               s.address, s.birth_cert_no, s.hsc_gpa, s.hsc_year, s.ssc_gpa, s.ssc_year, s.course_name, s.scholarship_rate);
    }
    fclose(fp);
    backToMenu();
}

// Function to search a student by Student ID
void searchStudent() {
    struct Student s;
    int student_id, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &student_id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.student_id == student_id) {
            printf("\nStudent Found:\n");
            printf("Student ID: %d\nName: %s %s\nDate of Birth: %s\nGender: %c\nFather's Name: %s\nMother's Name: %s\nAddress: %s\nBirth Certificate No: %s\nHSC GPA: %.2f\nHSC Passing Year: %d\nSSC GPA: %.2f\nSSC Passing Year: %d\nCourse Name: %s\nScholarship Rate: %.2f%%\n",
                   s.student_id, s.first_name, s.last_name, s.dob, s.gender, s.father_name, s.mother_name,
                   s.address, s.birth_cert_no, s.hsc_gpa, s.hsc_year, s.ssc_gpa, s.ssc_year, s.course_name, s.scholarship_rate);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No student found with Student ID %d\n", student_id);
    }
    backToMenu();
}

// Function to update a student record
void updateStudent() {
    struct Student s;
    int student_id, found = 0;
    FILE *temp_fp;

    fp = fopen("students.dat", "rb");
    temp_fp = fopen("temp.dat", "wb");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Student ID to update: ");
    scanf("%d", &student_id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.student_id == student_id) {
            found = 1;

            printf("\nUpdating Record for Student ID: %d\n", s.student_id);
            printf("Enter New First Name (or press Enter to keep current): ");
            getchar();  // To consume the newline character left by scanf
            fgets(s.first_name, MAX_NAME_LENGTH, stdin);
            s.first_name[strcspn(s.first_name, "\n")] = '\0';  // Remove trailing newline
            if (strlen(s.first_name) == 0) {
                printf("First Name remains: %s\n", s.first_name);
            }

            printf("Enter New Last Name (or press Enter to keep current): ");
            fgets(s.last_name, MAX_NAME_LENGTH, stdin);
            s.last_name[strcspn(s.last_name, "\n")] = '\0';
            if (strlen(s.last_name) == 0) {
                printf("Last Name remains: %s\n", s.last_name);
            }

            printf("Enter New Date of Birth (dd/mm/yyyy) (or press Enter to keep current): ");
            fgets(s.dob, DATE_LENGTH, stdin);
            s.dob[strcspn(s.dob, "\n")] = '\0';
            if (strlen(s.dob) == 0) {
                printf("Date of Birth remains: %s\n", s.dob);
            }

            printf("Enter New Gender (M/F) (or press Enter to keep current): ");
            scanf(" %c", &s.gender);

            printf("Enter New Father's Name (or press Enter to keep current): ");
            getchar();  // To consume newline
            fgets(s.father_name, MAX_NAME_LENGTH, stdin);
            s.father_name[strcspn(s.father_name, "\n")] = '\0';
            if (strlen(s.father_name) == 0) {
                printf("Father's Name remains: %s\n", s.father_name);
            }

            printf("Enter New Mother's Name (or press Enter to keep current): ");
            fgets(s.mother_name, MAX_NAME_LENGTH, stdin);
            s.mother_name[strcspn(s.mother_name, "\n")] = '\0';
            if (strlen(s.mother_name) == 0) {
                printf("Mother's Name remains: %s\n", s.mother_name);
            }

            printf("Enter New Address (or press Enter to keep current): ");
            fgets(s.address, MAX_ADDRESS_LENGTH, stdin);
            s.address[strcspn(s.address, "\n")] = '\0';
            if (strlen(s.address) == 0) {
                printf("Address remains: %s\n", s.address);
            }

            printf("Enter New Birth Certificate Number (or press Enter to keep current): ");
            fgets(s.birth_cert_no, MAX_CERT_NO_LENGTH, stdin);
            s.birth_cert_no[strcspn(s.birth_cert_no, "\n")] = '\0';
            if (strlen(s.birth_cert_no) == 0) {
                printf("Birth Certificate Number remains: %s\n", s.birth_cert_no);
            }

            promptForGPA(&s.hsc_gpa, "HSC");
            printf("Enter New HSC Passing Year (or enter 0 to keep current): ");
            scanf("%d", &s.hsc_year);
            if (s.hsc_year == 0) {
                printf("HSC Passing Year remains: %d\n", s.hsc_year);
            }

            promptForGPA(&s.ssc_gpa, "SSC");
            printf("Enter New SSC Passing Year (or enter 0 to keep current): ");
            scanf("%d", &s.ssc_year);
            if (s.ssc_year == 0) {
                printf("SSC Passing Year remains: %d\n", s.ssc_year);
            }

            printf("Enter New Course Name (or press Enter to keep current): ");
            getchar();  // Consume newline
            fgets(s.course_name, MAX_COURSE_LENGTH, stdin);
            s.course_name[strcspn(s.course_name, "\n")] = '\0';
            if (strlen(s.course_name) == 0) {
                printf("Course Name remains: %s\n", s.course_name);
            }

            // Calculate waiver based on GPA and gender
            calculateWaiver(&s);
        }

        // Write to temporary file
        fwrite(&s, sizeof(s), 1, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Student record updated successfully!\n");
    } else {
        printf("No student found with Student ID %d\n", student_id);
    }
    backToMenu();
}

// Function to delete a student record
void deleteStudent() {
    struct Student s;
    int student_id, found = 0;
    FILE *temp;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &student_id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.student_id == student_id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Student record deleted successfully!\n");
    } else {
        printf("No student found with Student ID %d\n", student_id);
    }
    backToMenu();
}

// Function to go back to the main menu
void backToMenu() {
    printf("\nPress any key to go back to the main menu...\n");
    getchar();  // To consume the newline character left by scanf
    getchar();  // Wait for user input
    menu();  // Go back to main menu
}

int main() {
    menu();  // Start the program by displaying the menu
    return 0;
}