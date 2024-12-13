/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:43:52 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:22 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_value(char *value)
{
	char	*aux;
	size_t	i;
	size_t	j;

	i = 0;
	if (!value)
		return (NULL);
	while(value[i] != '=')
		i++;
	aux =  malloc(sizeof(char) * (i + 1));
	if (!aux)
		return (NULL);//error_message("Malloc", CLOSE); //ToDO clear lst
	j = i + 1;
	i = 0;
	while (--j > 0)
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

	i = 0;
	k = 0;
	if (!content)
		return (NULL);
	j = ft_strlen(content);
	while (content[i] != '=')
		i++;
	aux =  malloc(sizeof(char) * (j - i + 2));
	if (!aux)
		return (NULL);//error_message("Malloc", CLOSE); //ToDO clear lst
	i++;
	while (content[i])
		aux[k++] = content[i++];
	aux[k] = '\0';
	return (aux);
}

t_env	*lstnew(char *content)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(*list));
	if (!list)
		return (NULL);//error_message("Malloc", CLOSE); //ToDO clear lst;
	list->value = get_value(content);
	list->content = get_content(content);
	list->next = NULL;
	return (list);
}

t_env	*get_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	size_t	i;

	i = -1;
	head = NULL;
	while (env[++i])
	{
		new_node = lstnew(env[i]);
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
	}
	if (current)
		current->next = NULL;
	return (head);
}
