/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:45:08 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/30 18:37:12 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//#include "paquito.h"

int	ft_strcmp(char *src, char *s)
{
	int	i;

	i = 0;
	while (src[i] && src[i] == s[i])
		i++;
	if (src[i] == '\0' && s[i] == '\0')
		return (1);
	return (0);
}

int	change_malloc_token(t_token *str, t_env *env, int measure)
{
	int	i;
	int	j;
	int	total;
	int	res;

	i = ft_strlen(str->content);
	j = ft_strlen(env->content);
	if (measure > j)
	{
		res = measure - j;
		total = i - res;
	}
	else if (measure < j)
	{
		res = j - measure;
		total = i + res;
	}
	else
		total = i;
	return (total);
}

void	delete_expanser(t_token *token, int start, int end)
{
	int		i;
	char	*str;

	i = ft_strlen(token->content);
	str = malloc(sizeof(char *) * (i - (end - start)) + 2);
	if (!str)
		return ;
	i = -1;
	while (++i < start)
		str[i] = token->content[i];
	while (token->content[end])
		str[i++] = token->content[end++];
	str[i] = '\0';
	free(token->content);
	token->content = str;
}

void	union_string(t_token *stack)
{
	t_token	*tmp;
	char	*tmp_content;

	tmp = stack->next;
	tmp_content = stack->content;
	stack->content = ft_strjoin(stack->content, stack->next->content);
	stack->next = tmp->next;
	free(tmp_content);
	free(tmp->content);
	free(tmp);
}

void	delete_quotes(t_token *token, char *str, int i, int j)
{
	char	tmp;

	while (token->content[i])
	{
		while (token->content[i] && !(token->content[i] == '\"'
				|| token->content[i] == '\''))
			str[j++] = token->content[i++];
		if (!token->content[i])
			break ;
		if (i == 0 || (token->content[i] == '\"'
				|| token->content[i] == '\''))
			tmp = token->content[i];
		else
			tmp = token->content[i - 1];
		i++;
		while (token->content[i] && token->content[i] != tmp)
			str[j++] = token->content[i++];
		tmp = 0;
		i++;
		if (!token->content[i])
			break ;
	}
	str[j] = '\0';
}
