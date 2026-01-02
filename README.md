# Inverted Search Engine

A simple **inverted index-based search engine** implemented in C.  
This project builds an inverted index from multiple text files, tracking all words and the files they appear in along with their frequencies.

---

## Features

- **Create Database**: Reads multiple input `.txt` files and builds an index of all words.
- **Display Database**: Shows all indexed words with the list of files and word counts.
- **Search Database**: Lets the user search for a word and find its occurrence details.
- **Store Database**: Saves the index to a file in a custom format for later retrieval.
- **Update Database**: Loads the database from a saved file, replacing the current in-memory index.
- **Clear Database**: Frees all allocated memory and resets the index.
- **Memory Management**: Properly frees all allocated memory on exit.

---

## Data Structures

- **file_list**: Linked list of input filenames.
- **main_list**: Linked list per hash table slot, each node stores a unique word.
- **sub_list**: For each word, a linked list of files containing the word and word counts.

The hash table has 28 slots indexed as:  
- `0-25`: words starting with `a-z`  
- `26`: words starting with numbers `0-9`  
- `27`: words starting with other characters (punctuation/symbols)

---

## Getting Started

### Prerequisites

- GCC compiler (for compiling C code)
- `.txt` files for testing

### Compilation

```
gcc main.c create.c display.c search.c store.c load.c validate.c free.c -o inverted
```

### Running

```
./inverted file1.txt file2.txt ... fileN.txt
```

---

## Usage

When running, the program shows this menu:

```
OPERATIONS
(1) Create database
(2) Display database
(3) Search database
(4) Save database
(5) Update database
(6) Clear database
(7) Exit
Enter your choice:
```

- Choose an option by entering the corresponding number.
- Follow on-screen prompts for inputs (e.g., word to search, filename to save/load).

---

## Example

Input files:  
- `hello.txt`:  
  ```
  HI MY NAME IS ANURAJ
  ```
- `welcome.txt`:  
  ```
  HI WELCOME TO MY VILLA HOUSE NAME IS BOGANVILLA, my place IS !kerala and MY NAME IS ANURAJ.
  ```

After creating the database and displaying it, you might see:

| INDEX | THE_WORD | FILE_COUNT | FILE_NAME -> WORD_COUNT           |
|-------|----------|------------|----------------------------------|
| 7     | HI       | 2          | hello.txt -> 1   welcome.txt -> 1 |
| 12    | MY       | 2          | hello.txt -> 1   welcome.txt -> 2 |
| 13    | NAME     | 2          | hello.txt -> 1   welcome.txt -> 2 |
| 0     | ANURAJ   | 2          | hello.txt -> 1   welcome.txt -> 1 |

Searching the word "NAME" displays:

```
INFO : THE WORD 'NAME' is present in 2 files

    In hello.txt -> 1 Times
    In welcome.txt -> 2 Times
```

---

## Error Handling

- Only accepts `.txt` files.
- Input files must not be empty.
- Duplicate or invalid filenames are rejected.
- Memory allocation failures are handled gracefully.
- Prevents saving an empty database.

---

## Project Structure

```
.
├── main.c
├── main.h
├── create.c
├── display.c
├── search.c
├── store.c
├── load.c
├── validate.c
├── free.c
└── README.md
```

---

## Future Improvements

- Make search case-insensitive.
- Ignore common stopwords like "the", "a", "is".
- Support for additional file formats.
- Add wildcard or fuzzy search capabilities (e.g., `hel*`).

---

## DEMO

<img width="1920" height="1080" alt="inverted_0" src="https://github.com/user-attachments/assets/0013897b-225b-49bb-8eda-314ce722f0b2" />
<img width="1920" height="1080" alt="inverted_1" src="https://github.com/user-attachments/assets/e7720ace-a3be-495a-9d6a-8bb822d1d85e" />
<img width="1920" height="1080" alt="inverted_2" src="https://github.com/user-attachments/assets/e435b66a-2b77-4111-9f49-409443b6b684" />
<img width="1920" height="1080" alt="inverted_3" src="https://github.com/user-attachments/assets/cc7a2d3d-9de6-4b6d-9696-26cf5a0381f9" />
<img width="1920" height="1080" alt="inverted_4" src="https://github.com/user-attachments/assets/e45b4655-67d3-4dd5-a9ea-800e8fcc8a57" />

