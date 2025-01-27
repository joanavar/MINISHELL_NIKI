/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannavarrogomez <joannavarrogomez@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:11:34 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/22 18:22:55 by joannavarro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env   *choose_env(t_shell *shell)
{
    t_env *env;

    env = ft_calloc(sizeof(t_env), 1);
    shell->env = env;
    shell->env->value = ft_strdup("SHLVL");
    shell->env->content = ft_strdup("1");
    shell->env->next = NULL;
    shell->env->prev = NULL;
    return (shell->env);
}
