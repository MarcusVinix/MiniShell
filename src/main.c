/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/05 00:07:32 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char** environ;

void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	shell->command = readline(prompt);
	shell->split_cmd = ft_split(shell->command, ' ');
	//printf("%s\n", command);
	if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		free(prompt);
		free_all(shell);
		exit(0);
	}
	free(prompt);
	add_history(shell->command);
}

int	check_command(t_shell *shell)
{
	if (!ft_strncmp(shell->command, "echo", 4))
		ft_echo(shell);
	else if (!ft_strncmp(shell->command, "pwd", 3))
		ft_pwd(shell, shell->command);
	else if (ft_strncmp(shell->split_cmd[0], "cd", 2) == 0)
		ft_cd(shell);
	else if (!ft_strncmp(shell->command, "env", 3))
		ft_env(shell->command, shell);
	else if (!ft_strncmp(shell->command, "export", 6))
		ft_export(shell->command, shell);
	else if (ft_strncmp(shell->split_cmd[0], "unset", 5) == 0)
		ft_unset(shell, &shell->lst_env);
	else
		if (execve(shell->split_cmd[0], shell->split_cmd, (char *const *)shell->lst_env) == -1)
			not_found(shell->command);
	return (0);
}

void	start_struct(t_shell *shell)
{
	shell->command = NULL;
	shell->lst_env = create_bckup_env(environ);
}

int	main(void)
{
	t_shell	shell;

	start_struct(&shell);
	while (1)
	{
		get_command(&shell);
		check_command(&shell);
		free_list_string(shell.split_cmd);
	}
}
