/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:43:52 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 16:48:51 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_value(char *value)
{
	char	*aux;
	size_t	i;
	size_t	j;

	i = 0;
	if (!value)
		return (NULL);
	while (value[i] && value[i] != '=')
		i++;
	if (!value[i])  // Si no hay '=', retornar NULL
		return (NULL);
	aux = malloc(sizeof(char) * (i + 1));
	if (!aux)
		return (NULL);
	j = i;
	i = 0;
	while (i < j)
	{
		aux[i] = value[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

static char	*get_content(char *content)
{
	char	*aux;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!content)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (!content[i])
		return (NULL);
	j = ft_strlen(content);
	aux = malloc(sizeof(char) * (j - i + 1));
	if (!aux)
		return (NULL);
	k = 0;
	i++;
	while (content[i])
		aux[k++] = content[i++];
	aux[k] = '\0';
	return (aux);
}

t_env	*lstnew(char *content)
{
	t_env	*list;

	if (!content)
		return (NULL);
	list = (t_env *)malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->value = get_value(content);
	if (!list->value)
	{
		free(list);
		return (NULL);
	}
	list->content = get_content(content);
	if (!list->content)
	{
		free(list->value);
		free(list);
		return (NULL);
	}
	list->next = NULL;
	list->prev = NULL; 
	return (list);
}

t_env	*get_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	size_t	i;

	if (!env)
		return (NULL);
	i = -1;
	head = NULL;
	current = NULL;
	while (env[++i])
	{
		new_node = lstnew(env[i]);
		if (!new_node)
		{
			if (head)
				free_env(head);  // Liberar toda la lista si falla
			return (NULL);
		}
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			new_node->prev = current;
			current = new_node;
		}
	}
	return (head);
}

/*int main(int ac, char **ag, char **env)
{
	t_env	*env_lst = get_env(env);
	int		i = 0;

	while (env_lst)
	{
		printf("%s=%s\n", env_lst->value, env_lst->content);
		env_lst = env_lst->next;
	}
	//printf("%s=%s\n",
		get_value("hola=/run/user/101047/vscode-git-8d84d82def.sock"),
		get_content("hola=/run/user/101047/vscode-git-8d84d82def.sock"));
	return (0);
}*/
