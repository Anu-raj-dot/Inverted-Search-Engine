#include "main.h"

int create_database(main_list **hash_table, file_list *f_head)
{
    if (f_head == NULL)
    {
        printf("ERROR : NO file exists to create database\n");
        return FAILURE;
    }

    while (f_head)
    {
        char *name = f_head->filename;
        FILE *fp;

        if ((fp = fopen(name, "r")) == NULL) // Open file in read mode
        {
            printf("ERROR : Unable to open file %s\n", name);
            return FAILURE;
        }

        char word[50];
        while (fscanf(fp, " %s", word) != EOF)
        {
            // Process each word (e.g., insert into hash table)
            int index = 0;
            if (word[0] >= '0' && word[0] <= '9') // Check if the first character is a digit
            {
                index = 26;
            }
            else
            {
                index = tolower(word[0]) % 97; // Calculate index based on first character

                if (index > 25)
                {
                    index = 27; // For non-alphabetic characters
                }
            }

            if (hash_table[index] == NULL) // if no main node exists at this index
            {
                main_list *main_node = (main_list *)malloc(sizeof(main_list)); // Create new main node
                if (main_node == NULL)
                {
                    printf("ERROR : Memory allocation failed\n");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(main_node->word, word);
                main_node->file_count = 1; // Initialize file count
                main_node->sub_link = NULL;
                main_node->next = NULL;
                hash_table[index] = main_node; // Insert at hash table

                sub_list *sub_node = (sub_list *)malloc(sizeof(sub_list)); // Create new sub node
                if (sub_node == NULL)
                {
                    printf("ERROR : Memory allocation failed\n");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(sub_node->filename, name);
                sub_node->word_count = 1; // Initialize word count
                sub_node->sub_next = NULL;
                main_node->sub_link = sub_node;
            }
            else
            {
                main_list *current = hash_table[index]; // Traverse to find if the word already exists
                main_list *prev = NULL;
                int found = 0;

                while (current != NULL) // Check if the word already exists
                {
                    if (strcmp(current->word, word) == 0)
                    {
                        found = 1;

                        sub_list *sub_current = current->sub_link;
                        sub_list *sub_prev = NULL;
                        int sub_found = 0;

                        while (sub_current != NULL) // Check if the filename already exists
                        {
                            if (strcmp(sub_current->filename, name) == 0)
                            {
                                sub_current->word_count++; // Increment word count
                                sub_found = 1;
                                break;
                            }
                            sub_prev = sub_current; // Keep track of previous sub node
                            sub_current = sub_current->sub_next;
                        }

                        if (!sub_found) // If filename not found, create a new sub node
                        {
                            current->file_count++;                                    // Increment file count
                            sub_list *new_sub = (sub_list *)malloc(sizeof(sub_list)); // Create new sub node
                            if (new_sub == NULL)
                            {
                                printf("ERROR : Memory allocation failed\n");
                                fclose(fp);
                                return FAILURE;
                            }
                            strcpy(new_sub->filename, name);
                            new_sub->word_count = 1;
                            new_sub->sub_next = NULL;
                            sub_prev->sub_next = new_sub; // Link new sub node
                        }
                        break;
                    }
                    prev = current;
                    current = current->next;
                }

                if (!found) // If word not found, create a new main node
                {
                    main_list *main_node = (main_list *)malloc(sizeof(main_list)); // Create new main node
                    if (main_node == NULL)
                    {
                        printf("ERROR : Memory allocation failed\n");
                        fclose(fp);
                        return FAILURE;
                    }
                    strcpy(main_node->word, word);
                    main_node->file_count = 1; // Initialize file count
                    main_node->sub_link = NULL;
                    main_node->next = NULL;
                    prev->next = main_node;

                    sub_list *sub_node = (sub_list *)malloc(sizeof(sub_list));
                    if (sub_node == NULL)
                    {
                        printf("ERROR : Memory allocation failed\n");
                        fclose(fp);
                        return FAILURE;
                    }
                    strcpy(sub_node->filename, name);
                    sub_node->word_count = 1; // Initialize word count
                    sub_node->sub_next = NULL;
                    main_node->sub_link = sub_node;
                }
            }
        }
        fclose(fp); // Close the file after processing
        f_head = f_head->link;
    }

    return SUCCESS;
}
