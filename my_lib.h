#ifndef MY_LIB_H
#define MY_LIB_H

#define MAX_NAME_LEN 50
#define MAX_SPECIES_LEN 30
#define MAX_PATIENTS 100

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char species[MAX_SPECIES_LEN];
    int age;
} Patient;

void add_patient();
void list_patients();
void delete_patient();
void save_to_file();
void load_from_file();
#endif 
