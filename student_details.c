#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};

// Add student record
void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter marks of 3 subjects: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record added successfully!\n\n");
}

// Display all records
void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Total: %.2f\n",
               s.roll, s.name, s.total);
    }

    fclose(fp);
    printf("\n");
}

// Rank students (simple sorting)
void rankStudents() {
    struct Student s[100];
    int i = 0, j, n = 0;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records to rank!\n");
        return;
    }

    // Read all records
    while (fread(&s[n], sizeof(struct Student), 1, fp)) {
        n++;
    }
    fclose(fp);

    // Sort (descending order of total)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i].total < s[j].total) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < n; i++) {
        printf("Rank %d: %s (Total: %.2f)\n",
               i + 1, s[i].name, s[i].total);
    }
    printf("\n");
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("===== MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Rank Students\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankStudents(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
