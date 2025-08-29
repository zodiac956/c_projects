#include <stdio.h>
#include <stdlib.h>

struct student {
    char name[50];
    char surname[50];
    int number;
    float gpa;
};

struct student* students = NULL;
int studentCount = 0;

// Function declarations
void sAdd();
void sSearch();
void sUpdate();
void sDelete();
void sDisplay();
void sSaveToFile();
void sLoadFromFile();
void pressEnterToContinue();

int main() {
    sLoadFromFile();  // Load saved students

    int option;
    while (1) {
        printf("\n====== Student Management System ======\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Display All Students\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: sAdd(); break;
            case 2: sSearch(); break;
            case 3: sUpdate(); break;
            case 4: sDelete(); break;
            case 5: sDisplay(); break;
            case 6:
                sSaveToFile();
                free(students);
                printf("Exiting... Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void sAdd() {
    students = realloc(students, (studentCount + 1) * sizeof(struct student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter student's name: ");
    scanf("%s", students[studentCount].name);

    printf("Enter student's surname: ");
    scanf("%s", students[studentCount].surname);

    printf("Enter student's number: ");
    scanf("%d", &students[studentCount].number);

    printf("Enter student's GPA: ");
    scanf("%f", &students[studentCount].gpa);

    studentCount++;
    printf("Student added successfully.\n");
    pressEnterToContinue();
}

void sSearch() {
    int searchNumber, foundIndex = -1;

    printf("Enter student number to search: ");
    scanf("%d", &searchNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].number == searchNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\nStudent not found!\n");
        pressEnterToContinue();
        return;
    }

    printf("\n--- Student Found ---\n");
    printf("Name    : %s\n", students[foundIndex].name);
    printf("Surname : %s\n", students[foundIndex].surname);
    printf("Number  : %d\n", students[foundIndex].number);
    printf("GPA     : %.2f\n", students[foundIndex].gpa);
    pressEnterToContinue();
}

void sUpdate() {
    int searchNumber, foundIndex = -1;

    printf("Enter student number to update: ");
    scanf("%d", &searchNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].number == searchNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\nStudent not found!\n");
        pressEnterToContinue();
        return;
    }

    int choice;
    printf("\nWhat would you like to update?\n");
    printf("1. Name\n2. Surname\n3. Number\n4. GPA\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf("%s", students[foundIndex].name);
            break;
        case 2:
            printf("Enter new surname: ");
            scanf("%s", students[foundIndex].surname);
            break;
        case 3:
            printf("Enter new number: ");
            scanf("%d", &students[foundIndex].number);
            break;
        case 4:
            printf("Enter new GPA: ");
            scanf("%f", &students[foundIndex].gpa);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    printf("Student updated successfully.\n");
    pressEnterToContinue();
}

void sDelete() {
    int searchNumber, foundIndex = -1;

    printf("Enter student number to delete: ");
    scanf("%d", &searchNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].number == searchNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\nStudent not found!\n");
        pressEnterToContinue();
        return;
    }

    // Shift elements to the left
    for (int i = foundIndex; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    students = realloc(students, studentCount * sizeof(struct student));

    printf("Student deleted successfully.\n");
    pressEnterToContinue();
}

void sDisplay() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        pressEnterToContinue();
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("\nStudent #%d\n", i + 1);
        printf("Name    : %s %s\n", students[i].name, students[i].surname);
        printf("Number  : %d\n", students[i].number);
        printf("GPA     : %.2f\n", students[i].gpa);
    }
    pressEnterToContinue();
}

void sSaveToFile() {
    FILE* fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Error saving to file.\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct student), studentCount, fp);
    fclose(fp);
    printf("Data saved successfully.\n");
}

void sLoadFromFile() {
    FILE* fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        return; // no saved data
    }

    fread(&studentCount, sizeof(int), 1, fp);
    students = malloc(studentCount * sizeof(struct student));
    fread(students, sizeof(struct student), studentCount, fp);
    fclose(fp);
}

void pressEnterToContinue() {
    printf("\nPress Enter to return to the menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}
