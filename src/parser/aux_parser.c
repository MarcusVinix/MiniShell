/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:35:04 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/23 21:52:57 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verify the position of redic
// Also check if is valid with is_all_space2
// Return 0 if after redic is just space or another redic
// Return 1 if a valid redic is find
int	valid_redic(char *cmd, int pos)
{
	if (!cmd)
		return (0);
	if (cmd[pos] == '<')
	{
		if (cmd[pos + 1] == '<')
			pos++;
		if (is_all_space2(cmd + pos + 1, '<'))
			return (0);
	}
	else if (cmd[pos] == '>')
	{
		if (cmd[pos + 1] == '>')
			pos++;
		if (is_all_space2(cmd + pos + 1, '>'))
			return (0);
	}
	return (1);
}

// Split the string in two side left and right
// After join the two sides removing the current quote
void	remove_quotes(t_shell *shell, int pos)
{
	char	*str_left;
	char	*str_right;

	str_left = ft_substr(shell->command, 0, pos);
	str_right = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));
	set_free_and_null(&shell->command);
	shell->command = ft_strjoin(str_left, str_right);
	free(str_left);
	free(str_right);
}

// Store the current delimiter
void	store_delimiter(t_shell *shell)
{
	char	*tmp;

	if (!shell->s_redic->file)
		return ;
	if (!shell->s_redic->delimiter)
		shell->s_redic->delimiter = ft_strdup(shell->s_redic->file);
	else
	{
		tmp = ft_strjoin(shell->s_redic->delimiter, " ");
		set_free_and_null(&shell->s_redic->delimiter);
		shell->s_redic->delimiter = ft_strjoin(tmp, shell->s_redic->file);
		free(tmp);
	}
}

// Call function check_redic
// if some error happen Free parse_cmd string and return -1
// Call function exec_redic and return -1 if some error happen
//signal 1 = into pipe
//signal 0 = without pipe
// return 0 if don't have any redic
// return 1 if is success
int	treatment_redic(t_shell *shell, int signal, int fd)
{
	if (check_redic(shell, signal))
	{
		if (signal == 1)
			shell->s_redic->out = fd;
		if (shell->s_redic->parse == NULL)
		{
			reset_struct(shell);
			set_free_and_null(&shell->parse_cmd);
			return (-1);
		}
		if (exec_redic(shell))
		{
			set_free_and_null(&shell->parse_cmd);
			reset_struct(shell);
			return (-1);
		}
		if (signal == 0)
		{
			set_free_and_null(&shell->s_redic->parse);
			set_free_and_null(&shell->command);
		}
		return (1);
	}
	return (0);
}
