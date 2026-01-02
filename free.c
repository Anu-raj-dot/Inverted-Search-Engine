#include "main.h"

void free_database(main_list **hash_table) // function to free the hash table and its linked lists
{
    for (int i = 0; i < 28; i++)
    {
        if (hash_table[i] == NULL) // If no node exists at this index
        {
            continue;
        }

        main_list *current_main = hash_table[i];
        main_list *temp = NULL;

        while (current_main) // Traverse the main linked list
        {
            sub_list *sub = current_main->sub_link;
            sub_list *temp1 = NULL;

            while (sub) // Traverse the sub linked list
            {
                temp1 = sub;
                sub = sub->sub_next;
                free(temp1); // Free sub node
            }

            temp = current_main;
            current_main = current_main->next;
            free(temp); // Free main node
        }

        hash_table[i] = NULL; // Set index to NULL after freeing
    }
}

void free_filenode(file_list **head) // function to free the linked list of file names
{
    file_list *current = *head;
    file_list *temp = NULL;

    while (current)
    {
        temp = current;
        current = current->link;
        free(temp); // Free file node
    }
    *head = NULL;
}

void search_file(char *filename, file_list ***head) // function to search and remove a file name from node
{
    file_list *current = **head;
    file_list *temp = NULL;

    if (head == NULL)
        return;

    while (current)
    {

        if (strcmp(current->filename, filename) == 0)
        {
            if (**head == current)
            {
                **head = current->link;
                free(current);
            }
            else
            {
                temp->link = current->link;
                free(current);
            }
            return;
        }

        temp = current;
        current = current->link;
    }
}