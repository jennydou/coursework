#include <stdio.h>
#include <stdlib.h>
#include "my_lib.h"

void menu() {
    printf("\n===== Veterinary Clinic Database =====\n");
    printf("1. Add patient\n");
    printf("2. Show all patients\n");
    printf("3. Delete patient\n");
    printf("4. Update patient info\n");
    printf("5. Save to file\n");
    printf("6. Load from file\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    load_from_file();

    char choice_str[10];
    int choice = -1;

    while (choice != 0) {
        menu();
        fgets(choice_str, sizeof(choice_str), stdin);
        choice = atoi(choice_str);

        switch (choice) {
            case 1: add_patient(); break;
            case 2: list_patients(); break;
            case 3: delete_patient(); break;
            case 4: update_patient(); break;
            case 5: save_to_file(); break;
            case 6: load_from_file(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
