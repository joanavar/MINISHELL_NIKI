/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:35:51 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:57 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_doubles(char *str, char ltr)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == ltr)
			counter++;
		i++;
	}
	if (counter % 2 == 0)
		return (0);
	return (counter % 2);
}

int	check_specials(char *str, char ltr)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ltr)
			return (1);
		i++;
	}
	return (0);
}

int	parssing(t_shell **shell)
{
	if (check_doubles((*shell)->prompt, 34))
		return (-1);
	if (check_doubles((*shell)->prompt, 39))
		return (-1);
	return (0);
}
