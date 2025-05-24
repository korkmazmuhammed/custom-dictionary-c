#ifndef CUSTOM_DICT_H
#define CUSTOM_DICT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union
{
    int arr;
    float f_arr;
    char c_arr;
    double d_arr;
} Value;

typedef struct
{
    char *key;
    Value *value;
    char *dtype;
    int counter;
} Item;

typedef struct
{
    Item *myItem;
    int capacity; /*current capacity like a current index*/
    int dictSize; /*current  max size of dictionary*/
} CustomDict;

CustomDict *create_dict()
{
    CustomDict *dict;
    dict = (CustomDict *)malloc(sizeof(CustomDict));
    (*dict).capacity = 0;
    (*dict).dictSize = 17;
    dict->myItem = (Item *)calloc(sizeof(Item), (*dict).dictSize);
    if (dict)
        return dict;
    else
        return NULL;
}

Value *search_item(CustomDict *dict, char *key)
{
    int i;
    for (i = 0; i < (*dict).capacity; i++)
    {
        if (strcmp((*dict).myItem[i].key, key) == 0)
        {
            return (*dict).myItem[i].value;
        }
    }
    return NULL;
}

void delete_item(CustomDict *dict, char *key)
{
    int i;
    Item temp;
    for (i = 0; i < (*dict).capacity; i++)
    {
        if (strcmp((*dict).myItem[i].key, key) == 0)
        {
            memcpy(&temp, &(*dict).myItem[i], sizeof(Item));
            memcpy(&(*dict).myItem[i], &(*dict).myItem[(*dict).capacity - 1], sizeof(Item));
            memcpy(&(*dict).myItem[(*dict).capacity - 1], &temp, sizeof(Item));

            free((*dict).myItem[(*dict).capacity - 1].dtype);
            free((*dict).myItem[(*dict).capacity - 1].key);
            free((*dict).myItem[(*dict).capacity - 1].value);
            (*dict).capacity -= 1;
            dict->myItem = (Item *)realloc(dict->myItem, (*dict).capacity * sizeof(Item));
        }
    }
}

void set_value(CustomDict *dict, char *key, Value *value)
{
    int i, j;
    int counter;

    for (i = 0; i < (*dict).capacity; i++)
    {
        if (strcmp((*dict).myItem[i].key, key) == 0)
        {
            counter = (*dict).myItem[i].counter;
            if (strcmp((*dict).myItem[i].dtype, "int") == 0)
            {
                for (j = 0; j < counter; j++)
                    (*dict).myItem[i].value[j].arr = value[j].arr;
            }

            else if (strcmp((*dict).myItem[i].dtype, "char") == 0)
            {
                for (j = 0; j < counter; j++)
                    (*dict).myItem[i].value[j].c_arr = value[j].c_arr;
            }

            else if (strcmp((*dict).myItem[i].dtype, "float") == 0)
            {
                for (j = 0; j < counter; j++)
                    (*dict).myItem[i].value[j].f_arr = value[j].f_arr;
            }

            else /*it means a double data type*/
            {
                for (j = 0; j < counter; j++)
                    (*dict).myItem[i].value[j].d_arr = value[j].d_arr;
            }
        }
    }
}

void add_item(CustomDict *dict, char *dtype, char *key, Value *value)
{
    int i;
    int counter = (*dict).myItem[(*dict).capacity].counter;
    if (search_item(dict, key))
    {
        for (i = 0; i < (*dict).capacity; i++)
        {
            if (strcmp((*dict).myItem[i].key, key) == 0)
                (*dict).myItem[i].counter = counter;
        }
        set_value(dict, key, value);
        return;
    }

    (*dict).myItem[(*dict).capacity].value = (Value *)calloc(sizeof(Value), counter);
    (*dict).myItem[(*dict).capacity].key = (char *)calloc(sizeof(char), strlen(key));
    (*dict).myItem[(*dict).capacity].dtype = (char *)calloc(sizeof(char), strlen(dtype));

    strcpy((*dict).myItem[(*dict).capacity].dtype, dtype);

    strcpy((*dict).myItem[(*dict).capacity].key, key);
    if (strcmp((*dict).myItem[(*dict).capacity].dtype, "int") == 0)
        for (i = 0; i < counter; i++)
            (*dict).myItem[(*dict).capacity].value[i].arr = value[i].arr;
    else if (strcmp((*dict).myItem[(*dict).capacity].dtype, "char") == 0)
        for (i = 0; i < counter; i++)
            (*dict).myItem[(*dict).capacity].value[i].c_arr = value[i].c_arr;
    else if (strcmp((*dict).myItem[(*dict).capacity].dtype, "float") == 0)
        for (i = 0; i < counter; i++)
            (*dict).myItem[(*dict).capacity].value[i].f_arr = value[i].f_arr;
    else /*it means a double data type*/
        for (i = 0; i < counter; i++)
            (*dict).myItem[(*dict).capacity].value[i].d_arr = value[i].d_arr;
    (*dict).capacity += 1;
}

int read_csv(CustomDict *dict, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 0;
    char *arr = (char *)calloc(sizeof(char), 6);   /*variable that catches a data type*/
    char *arr2 = (char *)calloc(sizeof(char), 12); /*variable that catches a key*/
    char comma;
    Value my_value[10];
    int counter = 0;

    while (fscanf(fp, "%s", arr) != EOF)
    {
        fscanf(fp, "%s", arr2);
        arr[strlen(arr) - 1] = '\0';
        arr2[strlen(arr2) - 1] = '\0';
        if (strcmp(arr, "int") == 0)
        {
            while (fscanf(fp, "%c ", &comma) != EOF && comma != '\n')
            {
                fscanf(fp, "%d", &my_value[counter++].arr);
            }
        }

        else if (strcmp(arr, "char") == 0)
        {
            while (fscanf(fp, "%c ", &comma) != EOF && comma != '\n')
            {
                fscanf(fp, "%c", &my_value[counter++].c_arr);
            }
        }
        else if (strcmp(arr, "double") == 0)
        {
            while (fscanf(fp, "%c ", &comma) != EOF && comma != '\n')
            {
                fscanf(fp, "%lf", &my_value[counter++].d_arr);
            }
        }
        else /*it is a float type data*/
        {
            while (fscanf(fp, "%c ", &comma) != EOF && comma != '\n')
            {
                fscanf(fp, "%f", &my_value[counter++].f_arr);
            }
        }
        (*dict).myItem[(*dict).capacity].counter = counter;
        add_item(dict, arr, arr2, my_value); /*arr2 is key and arr is data type*/
        counter = 0;
    }
    return 1;
}

void sort_dict(CustomDict *dict)
{
    Item temp;
    int i, j;
    for (i = 0; i < (*dict).capacity; i++)
    {
        for (j = i + 1; j < (*dict).capacity; j++)
        {
            if (strcmp((*dict).myItem[i].key, (*dict).myItem[j].key) > 0)
            {
                memcpy(&temp, &(*dict).myItem[j], sizeof(Item));
                memcpy(&(*dict).myItem[j], &(*dict).myItem[i], sizeof(Item));
                memcpy(&(*dict).myItem[i], &temp, sizeof(Item));
            }
        }
    }
}

void print_dict(CustomDict *dict)
{
    int i, j;
    printf("\nITEM NO\t KEY\t VALUES\n\n");

    for (i = 0; i < (*dict).capacity; i++)
    {
        printf("ITEM--> [%d] %s:  ", i + 1, (*dict).myItem[i].key);
        for (j = 0; j < (*dict).myItem[i].counter; j++)
        {
            if (strcmp((*dict).myItem[i].dtype, "int") == 0)
            {
                printf("(%d) ", (*dict).myItem[i].value[j].arr);
            }
            else if (strcmp((*dict).myItem[i].dtype, "char") == 0)
            {
                printf("(%c) ", (*dict).myItem[i].value[j].c_arr);
            }
            else if (strcmp((*dict).myItem[i].dtype, "float") == 0)
            {
                printf("(%.1f) ", (*dict).myItem[i].value[j].f_arr);
            }
            else
            /* it means a double data type */
            {
                printf("(%.1lf) ", (*dict).myItem[i].value[j].d_arr);
            }
        }
        printf("\n");
    }
}

void free_dict(CustomDict *dict)
{
    int i;
    for (i = 0; i < (*dict).capacity; i++)
    {
        free((*dict).myItem[i].dtype);
        free((*dict).myItem[i].key);
        free((*dict).myItem[i].value);
    }
    free((*dict).myItem);
    free(dict);
}
#endif