


#include "string_operations.h"
#include <stdio.h>
#include <string.h>

void split_string(char* input_string, char* output_string, char start_char, char end_char) {
    char *start_ptr = strchr(input_string, start_char);
    char *end_ptr = strchr(input_string, end_char);

    // Ensure both start_char and end_char are found and are in the correct order
    if (start_ptr != NULL && end_ptr != NULL && start_ptr < end_ptr) {
        // Move start_ptr to the next character after start_char
        start_ptr++;

        // Calculate the length of the substring
        size_t length = end_ptr - start_ptr;

        // Copy the substring to output_string
        strncpy(output_string, start_ptr, length);

        // Null-terminate the output string
        output_string[length] = '\0';
    } else {
        // If the start_char or end_char are not found or in incorrect order, return an empty string
        output_string[0] = '\0';
    }
}
