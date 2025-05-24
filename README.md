
# Custom Dictionary Implementation in C

This project implements a flexible dictionary (associative array) data structure in C that supports multiple value types (int, float, double, char) under string keys. Bulk import from CSV, sorting, searching, updating, and memory-safe deletion are all supported. Developed as part of GTU CSE102 Assignment 12.

Author: Muhammed Korkmaz
Student ID: 220104004043
University: Gebze Technical University

## Overview

This program allows you to store, retrieve, update, delete, and print multiple key-value pairs. Each key can be associated with a list of values of any supported type (int, float, double, or char). The program can bulk-load entries from a CSV file, sort all entries by key, and print the dictionary contents in an organized format. All data is dynamically allocated and freed for memory safety.

## Usage

1. Prepare a CSV input file named data.csv in the following format:
int,key1,1,2,3
float,key2,1.1,2.2,3.3
char,key3,a,b,c
double,key4,1.11,2.22
- The first column is the value type (int, float, double, or char)
- The second column is the key name (string, unique)
- The rest are the values for that key, comma-separated

2. Compile the program:
gcc 220104004043.c -o custom_dict

3. Run the program:
./custom_dict
The program will read data.csv, sort entries by key, and print all key-value pairs.

## Example Output

ITEM NO   KEY    VALUES

ITEM--> [1] key1:  (1) (2) (3)
ITEM--> [2] key2:  (1.1) (2.2) (3.3)
ITEM--> [3] key3:  (a) (b) (c)
ITEM--> [4] key4:  (1.11) (2.22)

## Core Functions

- create_dict() - Initializes a new dictionary
- add_item(dict, dtype, key, value) - Adds or updates a key-value entry
- set_value(dict, key, value) - Updates an existing key’s values
- search_item(dict, key) - Retrieves the values for a given key
- delete_item(dict, key) - Removes a key and all its values
- read_csv(dict, filename) - Loads data from a CSV file
- sort_dict(dict) - Sorts items by key (lexicographically)
- print_dict(dict) - Prints all items in a readable format
- free_dict(dict) - Releases all dynamically allocated memory

## Files

220104004043.c: Main program
customDict.h: Structs and function definitions
data.csv: Input data
220104004043.pdf: Project report

## Memory Management

All items, values, keys, and arrays are dynamically allocated and safely freed with free_dict(dict) at the end of the program.

## Contact

For details, see the full report or the code comments.
Author: Muhammed Korkmaz, GTU, 220104004043
