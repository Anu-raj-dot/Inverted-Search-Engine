#include "main.h"

int search_database(main_list **hash_table) // function to search the database
{
    char search_word[50];
    printf("Enter the word to be searched: ");
    scanf("%[^\n]", search_word);

    printf("INFO : Searching through the database Started...\n");
    printf("\n");

    int index = 0;
    if (search_word[0] >= '0' && search_word[0] <= '9') // Check if the first character is a digit
    {
        index = 26;
    }
    else
    {
        index = tolower(search_word[0]) % 97; // Calculate index based on first character

        if (index > 25)
        {
            index = 27; // For non-alphabetic characters
        }
    }

    if (hash_table[index] == NULL) // If no main node exists at this index
    {
        printf("INFO : Word '%s' not found in the database.\n", search_word);
        printf("\n");
        return FAILURE;
    }

    main_list *current = hash_table[index]; // Pointer to traverse the list
    while (current != NULL)
    {
        if (strcmp(current->word, search_word) == 0) // If the word is found
        {
            printf("INFO : THE WORD '%s' is present in '%d' file\n", search_word, current->file_count);
            printf("\n");
            sub_list *sub_current = current->sub_link;
            while (sub_current) // Traverse the sub list to display filenames and word counts
            {
                printf("\tIn %s -> %d Times\n", sub_current->filename, sub_current->word_count);
                sub_current = sub_current->sub_next;
            }
            printf("\n");
            return SUCCESS;
        }
        current = current->next;
    }
    printf("INFO : Word '%s' not found in the database.\n", search_word);
    printf("\n");
    return FAILURE;
}