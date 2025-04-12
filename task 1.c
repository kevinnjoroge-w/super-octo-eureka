#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_GRADE_LEN 3

// Global array to store student grades
char grades[MAX_STUDENTS][MAX_GRADE_LEN];
int count = 0;

// Function prototypes
void addGrade();
void deleteGrade();
void searchGrade();
void calculateAverage();
void findMinMax();
void displayAll();
void displayMenu();

int main() {
    displayMenu();
    return 0;
}

void addGrade() {
    if (count >= MAX_STUDENTS) {
        printf("Error: Maximum number of students reached!\n");
        return;
    }

    printf("Enter student grade (A-F with optional +/-): ");
    scanf("%s", grades[count]);
    
    // Validate grade format
    if (strlen(grades[count]) > MAX_GRADE_LEN || 
        !isalpha(grades[count][0]) ||
        (strlen(grades[count]) > 1 && !strchr("+-", grades[count][1])) ||
        (strlen(grades[count]) > 2 && grades[count][1] != '\0')) {
        printf("Invalid grade format! Use A-F with optional +/-\n");
        return;
    }

    // Convert to uppercase
    grades[count][0] = toupper(grades[count][0]);
    count++;
    printf("Grade added successfully!\n");
}

void deleteGrade() {
    if (count == 0) {
        printf("No grades to delete!\n");
        return;
    }

    char search[MAX_GRADE_LEN];
    printf("Enter grade to delete: ");
    scanf("%s", search);
    search[0] = toupper(search[0]);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(grades[i], search) == 0) {
            // Shift remaining elements
            for (int j = i; j < count - 1; j++) {
                strcpy(grades[j], grades[j+1]);
            }
            count--;
            found = 1;
            printf("Grade deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Grade not found!\n");
    }
}

void searchGrade() {
    if (count == 0) {
        printf("No grades to search!\n");
        return;
    }

    char search[MAX_GRADE_LEN];
    printf("Enter grade to search: ");
    scanf("%s", search);
    search[0] = toupper(search[0]);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(grades[i], search) == 0) {
            printf("Grade found at position %d\n", i+1);
            found = 1;
        }
    }

    if (!found) {
        printf("Grade not found!\n");
    }
}

void calculateAverage() {
    if (count == 0) {
        printf("No grades to calculate average!\n");
        return;
    }

    float sum = 0;
    for (int i = 0; i < count; i++) {
        switch(grades[i][0]) {
            case 'A': sum += 4; break;
            case 'B': sum += 3; break;
            case 'C': sum += 2; break;
            case 'D': sum += 1; break;
            case 'F': sum += 0; break;
        }
    }

    printf("Average grade: %.2f\n", sum / count);
}

void findMinMax() {
    if (count == 0) {
        printf("No grades to analyze!\n");
        return;
    }

    char min[MAX_GRADE_LEN], max[MAX_GRADE_LEN];
    strcpy(min, grades[0]);
    strcpy(max, grades[0]);

    for (int i = 1; i < count; i++) {
        if (strcmp(grades[i], min) < 0) {
            strcpy(min, grades[i]);
        }
        if (strcmp(grades[i], max) > 0) {
            strcpy(max, grades[i]);
        }
    }

    printf("Highest grade: %s\n", max);
    printf("Lowest grade: %s\n", min);
}

void displayAll() {
    if (count == 0) {
        printf("No grades to display!\n");
        return;
    }

    printf("Current grades:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i+1, grades[i]);
    }
}

void displayMenu() {
    int choice;
    do {
        printf("\nStudent Grade Management System\n");
        printf("1. Add a grade\n");
        printf("2. Delete a grade\n");
        printf("3. Search for a grade\n");
        printf("4. Calculate average grade\n");
        printf("5. Find highest and lowest grades\n");
        printf("6. Display all grades\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addGrade(); break;
            case 2: deleteGrade(); break;
            case 3: searchGrade(); break;
            case 4: calculateAverage(); break;
            case 5: findMinMax(); break;
            case 6: displayAll(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}
