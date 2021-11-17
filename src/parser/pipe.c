/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:22:52 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 20:31:42 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_pipe(void)
{
	ft_putstr_fd("Minishell: falha no pipe\n", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (0);
}

//find the pipe in the str, and verify if it inside of any quotes
static int	find_pipe(t_shell *shell, char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if (is_all_space2(str + i + 1, '|'))
				return (-2);
			if (shell->status_pipe->len > 0)
			{
				if (shell->status_pipe->lst_status[shell->status_pipe->pos++]
					== FALSE)
					continue ;
			}
			return (i);
		}
	}
	return (-1);
}

//will check if exist some valid pipe in the command;
//if yes, populate the string parse_cmd and refresh the command string;
int	check_pipe(t_shell *shell)
{
	int		pos;
	char	*aux;

	pos = find_pipe(shell, shell->command);
	if (pos == -2)
		return (error_newline());
	if (pos > 0)
	{
		shell->parse_cmd = ft_substr(shell->command, 0, pos);
		aux = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));
		if (shell->command)
			free(shell->command);
		shell->command = aux;
		return (1);
	}
	return (0);
}

//will execute the '|' 
//fd 0 READ STDIN
//fd 1 WRITE STDOUT
int	exec_pipe(t_shell *shell)
{
	int		fd[2];
	int		res;

	res = 0;
	while (shell->parse_cmd)
	{
		if (pipe(fd) >= 0)
		{
			res = treatment_redic(shell, 1, fd[1]);
			if (res == -1)
				return (1);
			if (res == 0)
				check_command(shell, fd[1]);
			reset_struct(shell);
			set_free_and_null(&shell->parse_cmd);
			dup2(fd[0], shell->fd_in);
			close(fd[0]);
			close(fd[1]);
		}
		else
			return (error_pipe());
		if (check_pipe(shell) == -1)
			return (1);
	}
	return (0);
}
