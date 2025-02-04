#include "../../inc/minishell.h"

int res_travel(t_token *tmp, t_env *env, t_shell *shell)
{
    int i;

    i = 0;
	while (tmp->content[i])
	{
		if (!tmp->content[i + 1] && tmp->content[i] == '$')
			return (0);
		else if (tmp->content[i] == '$' && tmp->content[i + 1] == '?')
		{
			expand_exit_status(tmp, i, shell);
			continue ;
		}
		else if (tmp->content[i] == '$')
		{
		    expander(tmp, i, env, shell);
			if (!tmp->content[i++])
				break ;
			continue ;
		}
		i++;
		if (!tmp->content)
			break ;
	}
    return (1);
}