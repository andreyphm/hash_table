#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "font.h"
#include "input_proc.h"

void check_cmd(FILE** const input_file, FILE** const output_file, 
               hash_func_num_t* hash_func_num, ULL* hash_table_capacity,
               int argc, const char* const argv[])
{
    if (argc == CORRECT_ARGC)
    {
        *input_file = fopen(argv[1], "r");
        *output_file = fopen(argv[2], "w");

        if (!*input_file)
        {
            printf(MAKE_BOLD_RED("Can't open input file. Default input file will be used: " DEFAULT_INPUT_FILE ".\n"));
            *input_file = fopen(DEFAULT_INPUT_FILE, "r");
        }

        if (!*output_file)
        {
            printf(MAKE_BOLD_RED("Can't open output file. Default output file will be used: " DEFAULT_OUTPUT_FILE ".\n"));
            *output_file = fopen(DEFAULT_OUTPUT_FILE, "w");
        }
        
        *hash_func_num = (hash_func_num_t)(atoi(argv[3]));
        *hash_table_capacity = (ULL)atoi(argv[4]);
    }
    else
    {
        bad_cmd_message(argv);
        *input_file = fopen(DEFAULT_INPUT_FILE, "r");
        *output_file = fopen(DEFAULT_OUTPUT_FILE, "w");
    }
}

void bad_cmd_message(const char* const* argv)
{
    printf(MAKE_BOLD("You haven't entered files and hash func number or you entered them incorrectly.\n"
                     "Default files will be used: " 
                     DEFAULT_INPUT_FILE " for input and " 
                     DEFAULT_OUTPUT_FILE " for output.\n"
                     "Default hash func and capacity will be used.\n"
                     "If you want to select your files, hash func and capacity, please, "
                     "use: %s input_file output_file hash_func_number hash_table_capacity.\n\n"), argv[0]);
}

char* read_file_to_buffer(FILE* const file)
{
    assert(file);

    struct stat file_struct = {};
    fstat(fileno(file), &file_struct);
    size_t file_size = (size_t)file_struct.st_size;

    char* buffer = (char*) calloc(file_size + 1, sizeof(*buffer));
    file_size = fread(buffer, sizeof(*buffer), file_size, file);
    buffer[file_size] = '\0';

    return buffer;
}

char** words_addresses_to_array(char* buffer, size_t* number_of_words)
{
    assert(buffer);
    assert(number_of_words);

    char* start_of_buffer = buffer;

    count_words(buffer, number_of_words);

    char** array_of_pointers = (char**) calloc(*number_of_words + 1, sizeof(char*));
    assert(array_of_pointers);

    post_pointers(array_of_pointers, start_of_buffer, buffer);
    assert(*array_of_pointers);

    return array_of_pointers;
}

void count_words(char* buffer, size_t* number_of_words)
{
    assert(buffer);
    assert(number_of_words);

    char* word_pointer = 0;

    while ((word_pointer = strchr(buffer, '\n')) != nullptr)
    {
        *number_of_words += 1;
        buffer = word_pointer + 1;
    }
}

void post_pointers(char** array_of_pointers, char* start_of_buffer, char* buffer)
{
    assert(array_of_pointers);
    assert(start_of_buffer);
    assert(buffer);

    char* word_pointer = 0;
    buffer = start_of_buffer;
    array_of_pointers[0] = start_of_buffer;

    for (int i = 1; (word_pointer = strchr(buffer, '\n')) != nullptr; i++)
    {
        *word_pointer = '\0';
        array_of_pointers[i] = word_pointer + 1;
        buffer = word_pointer + 1;
    }
}
