/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/30 20:25:46 by jestevam         ###   ########.fr       */
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
	//printf("%s\n", command);
	if (!ft_strcmp(shell->command, "exit"))
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
		ft_echo(shell->command);
	else if (!ft_strncmp(shell->command, "pwd", 3))
		ft_pwd(shell, shell->command);
	else if (!ft_strncmp(shell->command, "cd", 2))
		ft_cd(shell);
	else if (!ft_strncmp(shell->command, "env", 3))
		ft_env(shell->command, shell);
	else if (!ft_strncmp(shell->command, "export", 6))
		ft_export(shell->command, environ);
	else
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
	}
}
