/**************************************************************************************************************************************************************
       NAME    : ANURAJ R
       ROLL NO : 25005_010
       BATCH   : 25005B
       PROJECT : INVERTED SEARCH ENGINE
 ***************************************************************************************************************************************************************/
#include "main.h"

int main(int argc, char *argv[])
{
    file_list *head = NULL;

    if (validate_cla(argc, argv, &head) == FAILURE)
    {
        printf("INFO : ./a.out <filename.txt> <filename.txt> ...\n");
        return 0;
    }

    main_list *hash_table[28] = {NULL};
    int flag = 0, load = 0;

    while (1)
    {
        printf("\n");
        printf("\t\t\tOPERATIONS\n(1) Create database\n(2) Display database\n(3) Search database\n(4) Save database\n(5) Update database\n(6) Clear database\n(7) Exit\nEnter your choice :");
        int choice = 0;
        scanf(" %d", &choice);
        printf("\n");
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
        {
            printf("INFO : Creating Database Started...\n");

            if (flag == 1)
            {
                free_database(hash_table);
                if(load == 1 && head != 0)
                {
                    validate_cla(argc, argv, &head);
                    load = 0;
                }
                else
                    load = 0;
            }

            if (create_database(hash_table, head) == SUCCESS)
            {
                printf("INFO : Database created successfully.\n");
                flag = 1;
            }
            else
            {
                printf("ERROR : Failed to create database.\n");
            }
        }
        break;

        case 2:
        {
            printf("INFO : Database Display Started...\n");
            if (display_database(hash_table) == SUCCESS)
            {
                printf("INFO : Database displayed successfully.\n");
            }
            else
            {
                printf("ERROR : Failed to display database.\n");
            }
        }
        break;

        case 3:
        {
            search_database(hash_table);
        }
        break;

        case 4:
        {
            printf("INFO :Processing to store Database in file...\n");
            if (store_database(hash_table, head) == SUCCESS)
            {
                printf("INFO : Database stored successfully.\n");
            }
            else
            {
                printf("INFO :Failed to store database.\n");
            }
        }
        break;

        case 5:
        {
            printf("INFO : Processing to load Database from file...\n");
            if (load_database(hash_table, &head) == SUCCESS)
            {
                flag = 0, load = 1;
                printf("INFO : Database loaded successfully.\n");
            }
            else
            {
                printf("INFO : Failed to load database.\n");
            }
        }
        break;

        case 6:
        {
            printf("INFO : Clearing the database...\n");
            free_filenode(&head);
            free_database(hash_table);
            validate_cla(argc, argv, &head);
            printf("INFO : Database cleared successfully.\n");
        }
        break;

        case 7:
        {
            printf("INFO : Exiting the program...\n");
            free_database(hash_table);
            free_filenode(&head);
            return 0;
        }
        break;

        default:
        {
            printf("ERROR : Invalid choice. Enter a valid option\n");
        }
        }
    }
}