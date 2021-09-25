/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 22:55:38 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char** environ;

void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;

	getcwd(cwd, 2021);
	prompt = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(prompt, "$\033[0m ");
	shell->command = readline(prompt);
	//printf("%s\n", command);
	if (!ft_strcmp(shell->command, "exit"))
		exit(0);
	free(prompt);
	add_history(shell->command);
}

int	check_command(t_shell *shell)
{
	if (!ft_strncmp(shell->command, "echo", 4))
		ft_echo(shell->command);
	else if (!ft_strncmp(shell->command, "pwd", 3))
		ft_pwd(shell->command);
	else if (!ft_strncmp(shell->command, "cd", 2))
		ft_cd(shell);
	else if (!ft_strncmp(shell->command, "env", 3))
		ft_env(shell->command, environ);
	else
		not_found(shell->command);
	return (0);
}

int	main(void)
{
	t_shell	shell;

	shell.command = NULL;
	while (1)
	{
		get_command(&shell);
		check_command(&shell);
		free(shell.command);
	}
}
