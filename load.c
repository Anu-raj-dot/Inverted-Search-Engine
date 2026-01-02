#include "main.h"

int load_database(main_list **hash_table, file_list **f_head) // function to load the database from a file
{
    while (1) // user permission for erasing existing database
    {
        printf("CAUTION : Loading new database will erase the current database. Do you want to continue? (Y/N): ");
        char choice;
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ;
        if (choice == 'y' || choice == 'Y')
        {
            break;
        }
        else if (choice == 'n' || choice == 'N')
        {
            return FAILURE;
        }
        else
        {
            printf("ERROR : Invalid choice. Please enter Y or N.\n");
        }
    }

    char str[50];
    printf("Enter File Name [with .txt file] : ");
    scanf(" %s", str);
    while (getchar() != '\n')
        ;

    char *ext;
    if (ext = strstr(str, ".txt")) // validation for .txt extension
    {
        if (strcmp(ext, ".txt") != 0)
        {
            printf("ERROR : File name is invalid\n");
            return FAILURE;
        }
    }
    else
    {
        printf("ERROR : .txt is missing in file name.\n");
        return FAILURE;
    }

    free_database(hash_table); // Free existing database before loading new one

    FILE *fp;
    if ((fp = fopen(str, "r")) == NULL) // open file in read mode
    {
        printf("ERROR : Failed to open the file\n");
        return FAILURE;
    }

    char line[3000];
    int flag = 0;
    while (fgets(line, 3000, fp)) // read each line from the file
    {
        if (line[0] != '#') // validate for starting character '#'
        {
            continue;
        }

        line[strcspn(line, "\n")] = '\0'; // Remove newline character from the line

        char *data = strtok(line, ";"); // split the line using ';' as delimiter

        if (data == NULL || data[0] != '#') // validate for starting character '#'
        {
            continue;
        }

        int index = atoi(++data);                 // get index by converting string to integer
        char *word = strtok(NULL, ";");           // get the word
        int file_count = atoi(strtok(NULL, ";")); // get the file count

        main_list *main_node = (main_list *)malloc(sizeof(main_list)); // create new main node
        main_node->file_count = file_count;
        strcpy(main_node->word, word);
        main_node->next = NULL;
        main_node->sub_link = NULL;

        if (hash_table[index] == NULL) // if no node exists at this index
        {
            hash_table[index] = main_node; // insert main node at hash table

            for (int i = 0; i < file_count; i++) // loop to create sub nodes for each file
            {
                char *file_name = strtok(NULL, ";");      // get the file name
                int word_count = atoi(strtok(NULL, ";")); // get the word count

                sub_list *sub_node = (sub_list *)malloc(sizeof(sub_list)); // create new sub node
                strcpy(sub_node->filename, file_name);

                search_file(file_name, &f_head); // function call to check if file exists in the linked list of file names

                sub_node->word_count = word_count;
                sub_node->sub_next = NULL;

                sub_list *temp1 = main_node->sub_link; // pointer to traverse sub linked list

                if (temp1 == NULL) // if sub linked list is empty
                {
                    main_node->sub_link = sub_node;
                }
                else
                {
                    while (temp1->sub_next) // traverse to the end of sub linked list
                    {
                        temp1 = temp1->sub_next;
                    }
                    temp1->sub_next = sub_node; // link new sub node at the end
                }
            }
        }
        else
        {
            main_list *current_main = hash_table[index]; // pointer to traverse main linked list
            while (current_main->next)
            {
                current_main = current_main->next;
            }
            current_main->next = main_node; // link new main node at the end

            for (int i = 0; i < file_count; i++) // loop to create sub nodes for each file
            {
                char *file_name = strtok(NULL, ";"); // get the file name
                int word_count = atoi(strtok(NULL, ";"));

                sub_list *sub_node = (sub_list *)malloc(sizeof(sub_list)); // create new sub node
                strcpy(sub_node->filename, file_name);

                search_file(file_name, &f_head);

                sub_node->word_count = word_count;
                sub_node->sub_next = NULL;

                sub_list *temp1 = main_node->sub_link; // pointer to traverse sub linked list

                if (temp1 == NULL) // if sub linked list is empty
                {
                    main_node->sub_link = sub_node;
                }
                else
                {
                    while (temp1->sub_next) // traverse to the end of sub linked list
                    {
                        temp1 = temp1->sub_next;
                    }
                    temp1->sub_next = sub_node; // link new sub node at the end
                }
            }
        }
    }

    fclose(fp); // close the file
    return SUCCESS;
}