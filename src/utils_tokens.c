#include "../inc/minishell.h"

int count_quotes_utils(t_token *token, int i, int count, char tmp)
{
    while (token->content[i])
	{
		while (token->content[i])
		{
			if (token->content[i] == '\"' || token->content[i] == '\'')
			{
				tmp = token->content[i];
				i++;
				break ;
			}
			i++;
			count++;
		}
		while (token->content[i])
		{
			if (token->content[i] == tmp)
			{
				i++;
				break ;
			}
			i++;
			count++;
		}
	}
	return (count);
}