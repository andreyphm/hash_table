#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#define DEFAULT_INPUT_FILE  "input.txt"
#define DEFAULT_OUTPUT_FILE "output.txt"
#define CORRECT_ARGC 3

char* read_file_to_buffer(FILE* const file);
void check_files(FILE** const input_file, FILE** const output_file, int argc, const char* const argv[]);
void bad_argc_message(const char* const* argv);

char** words_addresses_to_array(char* buffer, size_t* number_of_strings);
void count_words(char* buffer, size_t* number_of_strings);
void post_pointers(char** array_of_pointers, char* start_of_buffer, char* buffer);

#endif // INPUT_H
