/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:08:20 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 16:22:51 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_home(t_cmd *cmd)
{
	t_env	*home;

	home = cmd->shell->env;
	while (home)
	{
		if (!strncmp(home->value, "HOME", 5))
			return (home->content);
		home = home->next;
	}
	return ("HOME not set");
}

void	get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	get_cd(t_cmd *cmd)
{
	char	*home;

	if (!cmd->arr_cmd[1])
	{
		home = strdup(find_home(cmd));
		if (chdir(home) != 0)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putendl_fd(home, 2);
		}
		free(home);
	}
	else if ((cmd->arr_cmd[1]) && !(cmd->arr_cmd[2]))
	{
		if (chdir(cmd->arr_cmd[1]) != 0)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(cmd->arr_cmd[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
	}
	else
		ft_putendl_fd("bash: cd: too many arguments", 2);
	return ;
}
