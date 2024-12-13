/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:08:20 by camurill          #+#    #+#             */
/*   Updated: 2024/12/13 18:01:19 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}
//ToDo
void	get_cd(t_shell *shell)
{
	if (shell->eco_token->next == NULL)
	{
		error_message("Need a relative or absolute path\n", NO_CLOSE);
		return ;
	}
	else if (shell->eco_token->next->next->content)
	{
		if (chdir(shell->eco_token->next->next->content) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else
	{
		error_message("Too many arguments\n", NO_CLOSE);
		return ;
	}
}
