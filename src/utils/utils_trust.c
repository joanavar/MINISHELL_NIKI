/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trust.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:34:17 by camurill          #+#    #+#             */
/*   Updated: 2025/02/01 16:57:53 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_trust	*create_new_trust(void)
{
	t_trust	*trust;

	trust = malloc(sizeof(t_trust));
	if (!trust)
		return (NULL);
	trust->arg = NULL;
	return (trust);
}
