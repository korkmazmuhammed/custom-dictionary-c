#include <stdio.h>
#include <stdlib.h>
#include "customDict.h"

int main()
{
    CustomDict *dict = NULL;
    dict = create_dict();
    if (!dict)
    {
        printf("ERROR CREATING DICTIONARY\n");
        return -1;
    }
    char *filename = "data.csv";
    if (!read_csv(dict, filename))
        printf("FILE NOT OPENED ERROR !!!\n");
    sort_dict(dict);
    print_dict(dict);
    free_dict(dict);
    return 0;
}