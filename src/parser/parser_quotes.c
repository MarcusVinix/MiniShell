/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:40:10 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/23 22:15:42 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Store into a list all redic and pipes
// Save the status depending the signal
// If signal is 0 the status is TRUE
// If signal is 1 the status is FALSE
static void	disable(t_shell *shell, int *pos, int signal)
{
	char		*cmd;
	t_status	*status;

	cmd = shell->command;
	status = shell->s_redic->status;
	if (cmd[*pos] == '<' || cmd[*pos] == '>')
	{
		if (signal == 0)
			status->lst_status[status->pos] = FALSE;
		else
			status->lst_status[status->pos] = TRUE;
		status->pos++;
		if (cmd[*pos + 1] == '<' || cmd[*pos + 1] == '>')
			*pos += 1;
	}
	if (cmd[*pos] == '|')
	{
		if (signal == 0)
			shell->status_pipe->lst_status[shell->status_pipe->pos] = FALSE;
		else
			shell->status_pipe->lst_status[shell->status_pipe->pos] = TRUE;
		shell->status_pipe->pos++;
	}
}

// Take the value of current environment variable
// Return the value
// Return empty if the variable don't exist
char	*aux_put_var(t_shell *shell, char *str_left, int *pos)
{
	char	*key;
	char	*value;

	key = ft_substr(shell->command, ft_strlen(str_left) + 1,
			*pos - (ft_strlen(str_left)));
	if (key[0] != '?')
		value = ft_strdup(find_value(&shell->lst_env, key));
	else
	{
		*pos += 1;
		value = ft_itoa(g_sh_status);
	}
	if (value == NULL)
		value = ft_strdup("");
	free(key);
	return (value);
}

// Check if the variable is valid and return 1 if isn't
// Call a function to take value of variable
// Change the string command puting the value of the variable in the right place
// Return 0 if is success
static int	put_variable(t_shell *shell, int *pos)
{
	char	*str_left;
	char	*str_middle;
	char	*str_right;
	char	*value;

	if (shell->command[*pos + 1] == ' ' || shell->command[*pos + 1] == '\0'
		|| shell->command[*pos + 1] == ':' || shell->command[*pos + 1] == '.'
		|| shell->command[*pos + 1] == '-')
		return (1);
	str_left = ft_substr(shell->command, 0, *pos);
	while (shell->command[*pos])
	{
		if (shell->command[*pos] == ' ' || shell->command[*pos] == '?'
			|| shell->command[*pos] == '\"' || shell->command[*pos] == '\'')
			break ;
		++*pos;
	}
	value = aux_put_var(shell, str_left, pos);
	str_middle = ft_strjoin(str_left, value);
	str_right = ft_substr(shell->command, *pos, ft_strlen(shell->command));
	set_free_and_null(&shell->command);
	shell->command = ft_strjoin(str_middle, str_right);
	*pos = ft_strlen(str_middle);
	free_four(str_left, str_middle, str_right, value);
	return (0);
}

// Check if is necessary change the string command
// If signal is 1 the current position is inside of any quote
// If the current position is a quote the return is 1
// Otherwise return 0
int	aux_quotes(t_shell *shell, char *quote, int *sig, int *pos)
{
	if (*sig == 1)
	{
		if (shell->command[*pos] == *quote)
		{
			*sig = 0;
			remove_quotes(shell, *pos);
			return (1);
		}
		disable(shell, pos, FALSE);
	}
	else
	{
		if (shell->command[*pos] == '\'' || shell->command[*pos] == '"')
		{
			*quote = shell->command[*pos];
			*sig = 1;
			remove_quotes(shell, *pos);
			return (1);
		}
		disable(shell, pos, TRUE);
	}
	return (0);
}

// Check if is necessary change the string command
// Change the command string when have some variable or quotes
int	trating_quotes(t_shell *shell)
{
	char	quote;
	int		pos;
	int		sig;

	pos = 0;
	sig = 0;
	quote = ' ';
	while (shell->command[pos])
	{
		if (aux_quotes(shell, &quote, &sig, &pos))
			continue ;
		if (quote != '\'' && shell->command[pos] == '$')
		{
			if (put_variable(shell, &pos) == 1)
				pos++;
			continue ;
		}
		pos++;
	}
	shell->s_redic->status->len = shell->s_redic->status->pos;
	shell->s_redic->status->pos = 0;
	shell->status_pipe->len = shell->status_pipe->pos;
	shell->status_pipe->pos = 0;
	return (0);
}
