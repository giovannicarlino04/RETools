#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reversing.h"

#define MAX_INPUT_LENGTH 100

void save_strings_to_file(const char *executable_path, const char *output_file) {
    char **strings = extract_strings_from_file(executable_path);
    if (strings == NULL) {
        printf("Error extracting strings from file.\n");
        return;
    }

    FILE *file = fopen(output_file, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; strings[i] != NULL; ++i) {
        fprintf(file, "%s\n", strings[i]);
    }

    fclose(file);
    printf("Extracted strings from file '%s' have been saved to '%s'.\n", executable_path, output_file);
}

int main() {
    int choice;
    char executable_path[MAX_INPUT_LENGTH];
    const char *output_file = "extracted_strings.txt";
    printf("Welcome to RETools, by Giovanni Carlino.\n");

    do {
        printf("Menu:\n");
        printf("1. Extract strings from file\n");
        printf("0. Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting program.\n");
                break;
            case 1:
                printf("Enter the path of the executable file: \n");
                scanf("%s", executable_path);
                save_strings_to_file(executable_path, output_file);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
