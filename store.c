#include "main.h"

int store_database(main_list **hash_table, file_list *head) // function to store the database into a file
{
    char str[50];
    printf("Enter File Name [with .txt file] : "); // user input
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

    while (head) // check for duplicate file name among file names in linked list
    {
        if (strcmp(str, head->filename) == 0)
        {
            printf("ERROR : File name is already exist, Try another one\n");
            return FAILURE;
        }
        head = head->link;
    }

    FILE *fp;
    if ((fp = fopen(str, "w+")) == NULL) // create and open file in write mode
    {
        printf("ERROR : Failed to create and open the file\n");
        return FAILURE;
    }

    int count = 0;
    for (int i = 0; i < 28; i++) // run loop for each index of hash table
    {
        if (hash_table[i] == NULL) // if no node exists at this index
        {
            count++;
            continue;
        }

        main_list *main_current = hash_table[i];
        while (main_current) // traverse the linked list at this index
        {
            // write data to file in specified format [#index;word;file_count;filename1;word_count1;filename2;word_count2;...#]
            fprintf(fp, "#%d;%s;%d", i, main_current->word, main_current->file_count);

            sub_list *sub_current = main_current->sub_link;
            while (sub_current)
            {
                fprintf(fp, ";%s;%d;", sub_current->filename, sub_current->word_count);
                sub_current = sub_current->sub_next;
            }

            fputs("#\n", fp); // end of line storing single index of hash table
            main_current = main_current->next;
        }
    }
    if (count == 28) // if entire hash table is empty
    {
        printf("ERROR : Database is empty\n");
        fclose(fp);
        remove(str); // delete the created file
        return FAILURE;
    }

    fclose(fp); // close the file
    return SUCCESS;
}