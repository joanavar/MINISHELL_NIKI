/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trust.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:34:17 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 18:36:37 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_trust	*create_new_trust(void)
{
	t_trust	*trust;

	trust = malloc(sizeof(t_trust) * 1);
	if (trust)
		return (NULL);
	trust->arg = NULL;
	return (trust);
}
