#include "main.h"

int validate_cla(int argc, char *argv[], file_list **f_head) // function to validate command line arguments
{

  if (argc == 1) // No file names provided
  {
    return FAILURE;
  }

  int i = 1;
  while (argv[i]) // check each file name
  {
    char *ext = strrchr(argv[i], '.');
    if (ext == NULL)
    {
      printf("ERROR : File extension not found\n");
      return FAILURE;
    }
    if (strcmp(ext, ".txt") == 0) // Check for .txt extension
    {
      FILE *fp;
      if (fp = fopen(argv[i], "r")) // Try to open the file
      {
        if (fseek(fp, 0, SEEK_END) == 0 && ftell(fp) > 0) // Check if file is not empty
        {
          if (insert_filename(f_head, argv[i]) == FAILURE) // Insert filename into linked list
          {
            fclose(fp);
            printf("INFO : Failed to insert duplicate filename : %s\n", argv[i]);
          }
        }
        else
        {
          fclose(fp);
          printf("ERROR : File is empty\n");
          return FAILURE;
        }
      }
      else
      {
        printf("ERROR : File not found\n");
        return FAILURE;
      }
    }
    else
    {
      printf("ERROR : File extension should be .txt\n");
      return FAILURE;
    }

    i++;
  }
  return SUCCESS;
}

int insert_filename(file_list **head, char *filename) // function to insert filename into linked list
{
  if (duplicate_check(head, filename) == FAILURE) // Check for duplicate filenames
  {
    printf("ERROR : Duplicate filename found\n");
    return FAILURE;
  }

  file_list *new = (file_list *)malloc(sizeof(file_list)); // Allocate memory for new node
  if (new == NULL)
  {
    printf("ERROR : Memory allocation failed\n");
    return FAILURE;
  }

  strcpy(new->filename, filename);
  new->link = NULL;

  if (*head == NULL) // If list is empty
  {
    *head = new;
    return SUCCESS;
  }

  file_list *temp = *head;

  while (temp->link != NULL) // Traverse to the end of the list
    temp = temp->link;

  temp->link = new;

  return SUCCESS;
}

int duplicate_check(file_list **head, char *filename) // function to check for duplicate filenames
{
  if (*head == NULL) // If list is empty
    return SUCCESS;

  file_list *temp = *head;
  while (temp != NULL) // Traverse the list
  {
    if (strcmp(temp->filename, filename) == 0)
      return FAILURE;

    temp = temp->link;
  }

  return SUCCESS;
}
