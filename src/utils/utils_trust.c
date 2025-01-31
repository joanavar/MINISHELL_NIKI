#include "../../inc/minishell.h"


t_trust *create_new_trust(void)
{
    t_trust *trust;

    trust = malloc(sizeof(t_trust) * 1);
    if (!trust)
        return (NULL);
    trust->arg = NULL;
    return (trust);
}
