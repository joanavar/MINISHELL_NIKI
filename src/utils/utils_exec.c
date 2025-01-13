#include "../../inc/minishell.h"

int arr_size(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        printf("contenido array :%s\n", array[i]);
        i++;
    }
    return (i);
}