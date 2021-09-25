/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 22:31:53 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char** environ;

char	*get_command(void)
{
	char	cwd[2021];
	char	*prompt;
	char	*command;

	getcwd(cwd, 2021);
	prompt = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(prompt, "$\033[0m ");
	command = readline(prompt);
	//printf("%s\n", command);
	if (!ft_strcmp(command, "exit"))
		exit(0);
	free(prompt);
	add_history(command);
	return (command);
}

int	check_command(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		ft_echo(command);
	else if (!ft_strncmp(command, "pwd", 3))
		ft_pwd(command);
	else if (!ft_strncmp(command, "cd", 2))
		ft_cd(command);
	else if (!ft_strncmp(command, "env", 3))
		ft_env(command, environ);
	else
		not_found(command);
	return (0);
}

int	main(void)
{
	char	*command;

	while (1)
	{
		command = get_command();
		check_command(command);
		free(command);
	}
}
