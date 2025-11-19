#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_lib.h"

static Patient patients[MAX_PATIENTS];
static int patient_count = 0;

void add_patient() {
    if (patient_count >= MAX_PATIENTS) {
        printf("Error: patient limit reached.\n");
        return;
    }

    Patient p;
    p.id = patient_count + 1;

    printf("Enter animal name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter animal species: ");
    fgets(p.species, sizeof(p.species), stdin);
    p.species[strcspn(p.species, "\n")] = '\0';

    printf("Enter animal age: ");
    char age_str[10];
    fgets(age_str, sizeof(age_str), stdin);
    p.age = atoi(age_str);

    patients[patient_count++] = p;
    printf("Patient added successfully!\n");
}

void list_patients() {
    if (patient_count == 0) {
        printf("The database is empty.\n");
        return;
    }

    printf("\nList of patients:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < patient_count; i++) {
        printf("ID: %d | Name: %s | Species: %s | Age: %d\n",
               patients[i].id, patients[i].name, patients[i].species, patients[i].age);
    }
    printf("----------------------------------------\n");
}

void delete_patient() {
    if (patient_count == 0) {
        printf("No patients to delete.\n");
        return;
    }

    printf("Enter patient ID to delete: ");
    char id_str[10];
    fgets(id_str, sizeof(id_str), stdin);
    int id = atoi(id_str);

    int found = 0;
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == id) {
            found = 1;
            for (int j = i; j < patient_count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patient_count--;
            printf("Patient with ID %d deleted.\n", id);
            break;
        }
    }

    if (!found)
        printf("No patient found with that ID.\n");
}

void update_patient() {
    if (patient_count == 0) {
        printf("No patients to update.\n");
        return;
    }

    printf("Enter patient ID to update: ");
    char id_str[10];
    fgets(id_str, sizeof(id_str), stdin);
    int id = atoi(id_str);

    int found = 0;
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("Enter new name: ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("Enter new species: ");
            fgets(patients[i].species, sizeof(patients[i].species), stdin);
            patients[i].species[strcspn(patients[i].species, "\n")] = '\0';

            printf("Enter new age: ");
            char age_str[10];
            fgets(age_str, sizeof(age_str), stdin);
            patients[i].age = atoi(age_str);

            printf("Patient information updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("No patient found with that ID.\n");
}

void save_to_file() {
    FILE *f = fopen("patients.txt", "w");
    if (!f) {
        printf("Error: could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < patient_count; i++) {
        fprintf(f, "%d;%s;%s;%d\n",
                patients[i].id,
                patients[i].name,
                patients[i].species,
                patients[i].age);
    }

    fclose(f);
    printf("Data saved to file patients.txt\n");
}

void load_from_file() {
    FILE *f = fopen("patients.txt", "r");
    if (!f) {
        printf("No database file found, starting with an empty list.\n");
        return;
    }

    patient_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ";");
        if (!token) continue;

        Patient p;
        p.id = atoi(token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(p.name, token, MAX_NAME_LEN);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(p.species, token, MAX_SPECIES_LEN);

        token = strtok(NULL, ";");
        if (!token) continue;
        p.age = atoi(token);

        patients[patient_count++] = p;
        if (patient_count >= MAX_PATIENTS)
            break;
    }

    fclose(f);
    printf("Loaded %d patients from file.\n", patient_count);
}
