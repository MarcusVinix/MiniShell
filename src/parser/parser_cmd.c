/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:40:00 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 22:43:23 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// will only split one of these strings.
// The order is hierarchical
static void	create_split_cmd(t_shell *shell)
{
	if (shell->s_redic->parse)
		shell->split_cmd = ft_split(shell->s_redic->parse, ' ');
	else if (shell->s_redic->cmd)
		shell->split_cmd = ft_split(shell->s_redic->cmd, ' ');
	else if (shell->parse_cmd)
		shell->split_cmd = ft_split(shell->parse_cmd, ' ');
	else
		shell->split_cmd = ft_split(shell->command, ' ');
}

int	aux_check_command(t_shell *shell, int fd)
{
	if (shell->split_cmd[1])
		g_sh_status = ft_atoi(shell->split_cmd[1]);
	free_list_string(shell->split_cmd);
	if (fd > 2)
		return (1);
	exit_shell(shell);
	return (0);
}

//will execute the command which command word was written
//saves the result of command in the variable "g_sh_status"
int	check_command(t_shell *shell, int fd)
{
	create_split_cmd(shell);
	config_sigaction(&shell->act, sigint_handle_cmd, SIGINT);
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell, fd);
	else if (find_index(shell->split_cmd[0], '=') > 0)
		ft_export(shell, fd, 0);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		g_sh_status = ft_pwd(fd, shell);
	else if (ft_strcmp(shell->split_cmd[0], "cd") == 0)
		g_sh_status = ft_cd(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "env") == 0)
		g_sh_status = ft_env(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "export") == 0)
		g_sh_status = ft_export(shell, fd, 1);
	else if (ft_strcmp(shell->split_cmd[0], "unset") == 0)
		g_sh_status = ft_unset(shell, &shell->lst_env, fd);
	else if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		if (aux_check_command(shell, fd))
			return (0);
	}
	else
		g_sh_status = ft_exec(shell, fd);
	free_list_string(shell->split_cmd);
	return (0);
}
