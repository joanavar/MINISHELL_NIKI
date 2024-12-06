/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:45:08 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:01:26 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

int ft_strcmp(const char *src, char *s)
{
	int i;

	i = 0;
	while (src[i] == s[i])
		i++;
	if (src[i] == '\0' && s[i] == '\0')
		return (0);
	return (1);
}


