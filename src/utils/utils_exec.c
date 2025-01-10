#include "../../inc/minishell.h"

int arr_size(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
        i++;
    return (i);
}