#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FAILURE 0
#define SUCCESS 1

typedef struct filename_node
{
    char filename[20];
    struct filename_node *link;
} file_list;

typedef struct sub_node
{
    int word_count;
    char filename[100];
    struct sub_node *sub_next;
} sub_list;

typedef struct main_node
{
    int file_count;
    char word[50];
    sub_list *sub_link;
    struct main_node *next;
} main_list;

// validate cla function
int validate_cla(int argc, char *argv[], file_list **head);
int insert_filename(file_list **head, char *filename);
int duplicate_check(file_list **head, char *filename);

// create database function
int create_database(main_list **hash_table, file_list *head);
// display database function
int display_database(main_list **hash_table);
// search database function
int search_database(main_list **hash_table);
// store database function
int store_database(main_list **hash_table, file_list *head);
// load database function
int load_database(main_list **hash_table, file_list **f_head);
// free database function
void free_database(main_list **hash_table);
// free file node function
void free_filenode(file_list **head);
// search file in linked list function
void search_file(char *filename, file_list ***head);

#endif
