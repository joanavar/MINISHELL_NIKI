/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:46 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/05 13:03:48 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//#include "paquito.h"

static int	close_expansor(t_token *token, int i)
{
	if (token->content[i] >= 'a' && token->content[i] <= 'z')
		return (1);
	else if (token->content[i] >= 'A' && token->content[i] <= 'Z')
		return (1);
	else if (token->content[i] == '_')
		return (1);
	else if (token->content[i] >= '0' && token->content[i] <= '9')
		return (1);
	return (0);
}

static int	correct_expansor(t_token *token, int i)
{
	if (token->content[i] >= 'a' && token->content[i] <= 'z')
		return (1);
	else if (token->content[i] >= 'A' && token->content[i] <= 'Z')
		return (1);
	else if (token->content[i] == '_')
		return (1);
	return (0);
}

static void	exchange_expanser(t_token *token, t_env *env, int start, int end)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = -1;
	len = change_malloc_token(token, env, start - end);
	str = malloc(sizeof(char) * len + 1);
	while (++i < start)
		str[i] = token->content[i];
	while (env->content[++j])
		str[i++] = env->content[j];
	while (token->content[end])
		str[i++] = token->content[end++];
	str[i] = '\0';
	free(token->content);
	token->content = str;
}

void	expander(t_token *token, int i, t_env *env, t_shell *shell)
{
	char	*str;
	int		j;
	t_env	*tmp;

	(void)shell;
	if (token->content[++i] == '$')
		return ;
	j = i;
	if (correct_expansor(token, i))
	{
		while (close_expansor(token, i))
			i++;
		str = ft_substr(token->content, j, i - j);
		if (!str)
			return ;
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(str, tmp->value))
				return (free(str), exchange_expanser(token, tmp, j - 1, i));
			tmp = tmp->next;
		}
		free(str);
		delete_expanser(token, j - 1, i);
	}
}

void	expandir(t_token **stack, t_env *env, t_shell *shell)
{
	t_token	*tmp;

	tmp = *stack;
	travel_expansor(tmp, env, shell);
}
