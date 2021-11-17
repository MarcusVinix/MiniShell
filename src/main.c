/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:40:48 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 20:33:05 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints the path that usually exist at the line of the shell
//save what the user write in a variable "command"
//save in the history the command saved in the variable
void	get_command(t_shell *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	if (shell->command)
		free(shell->command);
	shell->command = readline(prompt);
	free(prompt);
	if (shell->command == NULL)
		exit_shell(shell);
	add_history(shell->command);
	shell->s_redic->redic = -1;
}

int	exec_all_commands(t_shell *shell, int res, int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	get_command(shell);
	if (is_all_space(shell->command))
		return (1);
	if (trating_quotes(shell))
		return (1);
	res = check_pipe(shell);
	if (res == -1)
		return (1);
	if (res)
		if (exec_pipe(shell))
			return (1);
	if (treatment_redic(shell, 0, 1) == -1)
		return (1);
	if (shell->command)
	{
		reset_struct(shell);
		check_command(shell, 1);
	}
	shell->status_pipe->len = 0;
	shell->status_pipe->pos = 0;
	reset_struct(shell);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell				shell;
	struct sigaction	act_quit;
	int					in;
	int					out;
	int					res;

	res = 0;
	in = dup(0);
	out = dup(1);
	g_sh_status = 0;
	if (argc != 1 || argv[1])
		return (0);
	start_struct(&shell, env);
	while (1)
	{
		config_sigaction(&shell.act, sigint_handle, SIGINT);
		config_sigaction(&act_quit, SIG_IGN, SIGQUIT);
		if (exec_all_commands(&shell, res, in, out))
			continue ;
	}
	return (g_sh_status);
}
