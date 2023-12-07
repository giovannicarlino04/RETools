#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reversing.h"


#define MIN_STRING_LENGTH 4

char *strdup(const char *source) {
    if (source == NULL) {
        return NULL;
    }

    size_t length = strlen(source) + 1; // +1 for null terminator
    char *new_string = (char *)malloc(length);

    if (new_string != NULL) {
        memcpy(new_string, source, length);
    }

    return new_string;
}

char **extract_strings_from_file(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, file_size, file) != file_size) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        fclose(file);
        return NULL;
    }
    fclose(file);
    buffer[file_size] = '\0';

    char **strings = NULL;
    size_t strings_count = 0;

    for (size_t i = 0; i < file_size; ++i) {
        size_t j = i;
        while (j < file_size && isprint(buffer[j])) {
            ++j;
        }

        if (j - i >= MIN_STRING_LENGTH) {
            strings = (char **)realloc(strings, (strings_count + 1) * sizeof(char *));
            if (strings == NULL) {
                fprintf(stderr, "Memory reallocation error\n");
                free(buffer);
                return NULL;
            }
            buffer[j] = '\0';  // Null-terminate the string
            strings[strings_count++] = strdup(buffer + i);
            i = j; // Move to the end of the string
        }
    }

    strings = (char **)realloc(strings, (strings_count + 1) * sizeof(char *));
    strings[strings_count] = NULL;  // Mark end of strings with NULL

    free(buffer);
    return strings;
}