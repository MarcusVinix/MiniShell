/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 18:33:16 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_command(void)
{
	char	cwd[2021];
	char	*prompt;
	char	*command;

	getcwd(cwd, 2021);
	prompt = ft_strjoin(cwd, "$ ");
	command = readline(prompt);
	//printf("%s\n", command);
	if (!ft_strcmp(command, "exit"))
	{
		exit(0);
	}
	free(prompt);
	return (command);
}

int	check_command(char *command)
{
	if (!ft_strncmp(command, "echo", 4))
		ft_echo(command);
	else if (!ft_strncmp(command, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(command, "cd", 2))
		printf("CDCDHEHHE\n");
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
