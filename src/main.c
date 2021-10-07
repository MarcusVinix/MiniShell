/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:44:20 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/08 01:10:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status;

void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;
	int		ret;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	if (shell->command)
		free(shell->command);
	shell->command = readline(prompt);
	shell->split_cmd = ft_split(shell->command, ' ');
	//printf("%s\n", command);
	ret = 0;
	if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		if (shell->split_cmd[1])
			ret = ft_atoi(shell->split_cmd[1]);
		free(prompt);
		free_all(shell);
		exit(status);
	}
	free(prompt);
	add_history(shell->command);
}

int	check_command(t_shell *shell)
{
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		ft_pwd(shell, shell->command);
	else if (ft_strcmp(shell->split_cmd[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(shell->split_cmd[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->split_cmd[0], "export") == 0)
		status = ft_export(shell);
	else if (ft_strcmp(shell->split_cmd[0], "unset") == 0)
		ft_unset(shell, &shell->lst_env);
	else
		status = ft_exec(shell);
	return (0);
}

void	start_struct(t_shell *shell, char **env)
{
	shell->command = NULL;
	shell->lst_env = create_bckup_env(env);
}

void	sig_handle(int sig)
{
	(void)sig;
	printf("APERTOU HEHE\n");
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	status = 0;
	if (argc != 1 || argv[1])
		return (0);
	start_struct(&shell, env);
	while (1)
	{
		get_command(&shell);
		check_command(&shell);
		free_list_string(shell.split_cmd);
	}
	return (status);
}
