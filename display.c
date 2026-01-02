#include "main.h"

int display_database(main_list **hash_table) // function to display the database
{
    int index = 0;
    int flag = 1;

    for (int i = 0; i < 28; i++) // Traverse the hash table
    {
        if (hash_table[i] == NULL) // Skip empty indices
        {
            index++;
            continue;
        }

        main_list *current = hash_table[i]; // Pointer to traverse the linked list at this index

        if (flag) // Print header only once
        {
            printf("\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-10s %-15s %-15s %-12s \n", "INDEX", "THE_WORD", "FILE_COUNT", "FILE_NAME -> WORD_COUNT");
            flag = 0;
        }

        while (current) // Traverse the linked list
        {
            printf("%-10d %-15s %-15d ", i, current->word, current->file_count);
            sub_list *sub_current = current->sub_link;
            while (sub_current)
            {
                printf("%-10s -> %-10d ", sub_current->filename, sub_current->word_count);
                sub_current = sub_current->sub_next;
            }
            current = current->next;
            printf("\n");
        }
    }

    if (index == 28) // If entire hash table is empty
    {
        printf("INFO : Hash table is empty.\n");
        return FAILURE;
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
    return SUCCESS;
}