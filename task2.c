#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char grade;
} Student;

// Function prototypes
void bubbleSort(Student arr[], int n, bool sortByName);
void selectionSort(Student arr[], int n, bool sortByName);
void insertionSort(Student arr[], int n, bool sortByName);
void printStudents(Student arr[], int n);
void displayMenu();

// Comparison functions
int compareByName(const Student *a, const Student *b) {
    return strcmp(a->name, b->name);
}

int compareByGrade(const Student *a, const Student *b) {
    return a->grade - b->grade;
}

void inputStudents(Student students[], int *count) {
    printf("Enter number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", count);
    getchar(); // Consume newline
    
    for (int i = 0; i < *count; i++) {
        printf("\nStudent %d:\n", i+1);
        printf("Name: ");
        fgets(students[i].name, MAX_NAME_LEN, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline
        
        printf("Grade (A-F): ");
        scanf(" %c", &students[i].grade);
        getchar(); // Consume newline
        
        // Validate grade
        students[i].grade = toupper(students[i].grade);
        while (students[i].grade < 'A' || students[i].grade > 'F') {
            printf("Invalid grade! Enter A-F: ");
            scanf(" %c", &students[i].grade);
            students[i].grade = toupper(students[i].grade);
            getchar();
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    
    inputStudents(students, &count);
    displayMenu(students, count);
    return 0;
}

void bubbleSort(Student arr[], int n, bool sortByName) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            int compareResult;
            if (sortByName) {
                compareResult = compareByName(&arr[j], &arr[j+1]);
            } else {
                compareResult = compareByGrade(&arr[j], &arr[j+1]);
            }
            
            if (compareResult > 0) {
                // Swap
                Student temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(Student arr[], int n, bool sortByName) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            int compareResult;
            if (sortByName) {
                compareResult = compareByName(&arr[j], &arr[min_idx]);
            } else {
                compareResult = compareByGrade(&arr[j], &arr[min_idx]);
            }
            
            if (compareResult < 0) {
                min_idx = j;
            }
        }
        // Swap
        Student temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(Student arr[], int n, bool sortByName) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            int compareResult;
            if (sortByName) {
                compareResult = compareByName(&arr[j], &key);
            } else {
                compareResult = compareByGrade(&arr[j], &key);
            }
            
            if (compareResult > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void printStudents(Student arr[], int n) {
    printf("\nStudent Records:\n");
    printf("----------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s %c\n", arr[i].name, arr[i].grade);
    }
    printf("\n");
}

void displayMenu(Student students[], int count) {
    int choice;
    bool sortByName;
    Student copy[MAX_STUDENTS];
    
    do {
        printf("\nStudent Record Sorting System\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            printf("\nSort by:\n");
            printf("1. Name\n");
            printf("2. Grade\n");
            printf("Enter your choice: ");
            int sortChoice;
            scanf("%d", &sortChoice);
            sortByName = (sortChoice == 1);

            // Make a copy of original array for sorting
            memcpy(copy, students, sizeof(Student) * count);

            switch(choice) {
                case 1:
                    bubbleSort(copy, count, sortByName);
                    printf("\nSorted using Bubble Sort:\n");
                    break;
                case 2:
                    selectionSort(copy, count, sortByName);
                    printf("\nSorted using Selection Sort:\n");
                    break;
                case 3:
                    insertionSort(copy, count, sortByName);
                    printf("\nSorted using Insertion Sort:\n");
                    break;
            }
            printStudents(copy, count);
        } else if (choice != 4) {
            printf("Invalid choice!\n");
        }
    } while (choice != 4);
}
