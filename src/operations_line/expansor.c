/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:46 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 11:43:42 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//#include "paquito.h"

static int	is_valid_char(char c, int include_numbers)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	if (include_numbers && c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	close_expansor(t_token *token, int i)
{
	return (is_valid_char(token->content[i], 1));
}

static int	correct_expansor(t_token *token, int i)
{
	return (is_valid_char(token->content[i], 0));
}

static void	copy_env_content(char *str, t_env *env, int *i)
{
	int	j;

	j = -1;
	while (env->content[++j])
		str[(*i)++] = env->content[j];
}

static void	copy_content(char *str, t_token *token, t_env *env, int *idx)
{
	int	i;

	i = -1;
	while (++i < idx[0])
		str[i] = token->content[i];
	copy_env_content(str, env, &i);
	while (token->content[idx[1]])
		str[i++] = token->content[idx[1]++];
	str[i] = '\0';
}

static void	exchange_expanser(t_token *token, t_env *env, int start, int end)
{
	char	*str;
	int		len;
	int		idx[2];

	if (!token || !env || !token->content || !env->content)
		return ;
	len = change_malloc_token(token, env, start - end);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return ;
	idx[0] = start;
	idx[1] = end;
	copy_content(str, token, env, idx);
	free(token->content);
	token->content = str;
}

static void	handle_env_var(t_token *token, t_env *env, int *i, int j)
{
	char	*str;
	t_env	*tmp;

	str = ft_substr(token->content, j, *i - j);
	if (!str)
		return ;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->value))
		{
			free(str);
			exchange_expanser(token, tmp, j - 1, *i);
			return ;
		}
		tmp = tmp->next;
	}
	free(str);
	delete_expanser(token, j - 1, *i);
}

static void	process_dollar(t_token *token, int *i, t_env *env)
{
	if (token->content[*i] == '$')
	{
		if (!(token->content[*i + 1] == '\0' || 
			(token->content[*i + 1] == '$' && token->content[*i + 2] == '\0')))
			expander(token, *i, env);
	}
}

static void	process_token(t_token *token, t_env *env)
{
	int	i;

	i = 0;
	while (token->content[i])
	{
		process_dollar(token, &i, env);
		i++;
	}
}

static void	process_expansions(t_token *token, t_env *env)
{
	while (token)
	{
		token = expansor_res(token);
		if (!token)
			return ;
		if ((token->type == 1 || token->type == 3))
			process_token(token, env);
		token = token->next;
	}
}

void	expander(t_token *token, int i, t_env *env)
{
	int	j;

	if (!token || !env || !token->content)
		return ;
	if (token->content[++i] == '$' || token->content[i] == '\0')
		return ;
	if (token->content[i] == '?')
	{
		exchange_expanser(token, env, i - 1, i + 1);
		return ;
	}
	j = i;
	if (correct_expansor(token, i))
	{
		while (close_expansor(token, i))
			i++;
		handle_env_var(token, env, &i, j);
	}
}

void	expandir(t_token **stack, t_env *env)
{
	t_token	*tmp;

	tmp = *stack;
	process_expansions(tmp, env);
}
