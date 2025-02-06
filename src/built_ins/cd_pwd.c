/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:08:20 by camurill          #+#    #+#             */
/*   Updated: 2025/02/06 16:42:11 by camurill         ###   ########.fr       */
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

static void	update_pwd(t_shell *shell)
{
	char	cwd[1024];
	t_env	*env;
	char	*old_pwd;

	env = shell->env;
	old_pwd = NULL;
	while (env)
	{
		if (!ft_strncmp(env->value, "PWD", 4))
		{
			old_pwd = ft_strdup(env->content);
			break ;
		}
		env = env->next;
	}
	env = shell->env;
	res_pwd(cwd, env, old_pwd, shell);
}

static void	res_get_cd(t_cmd *cmd)
{
	char	*home;

	home = ft_strdup(find_home(cmd));
	if (chdir(home) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putendl_fd(home, 2);
	}
	else
		update_pwd(cmd->shell);
	free(home);
}

void	get_cd(t_cmd *cmd)
{
	if (!cmd->arr_cmd[1])
		res_get_cd(cmd);
	else if ((cmd->arr_cmd[1]) && !(cmd->arr_cmd[2]))
	{
		if (chdir(cmd->arr_cmd[1]) != 0)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(cmd->arr_cmd[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			cmd->shell->exit_status = 1;
		}
		else
			update_pwd(cmd->shell);
	}
	else
		ft_putendl_fd("bash: cd: too many arguments", 2);
}
