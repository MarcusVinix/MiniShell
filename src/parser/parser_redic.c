/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:07:54 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/23 22:28:02 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check and save wich redic is and return the position
// Return -1 if the current position isn't a redic
int	aux_find_redic(t_shell *shell, char *aux, int i)
{
	if (aux[i] == '>')
	{
		if (aux[i + 1] == '>')
			shell->s_redic->redic = 2;
		else
			shell->s_redic->redic = 1;
		return (i);
	}
	else if (aux[i] == '<')
	{
		if (aux[i + 1] == '<')
			shell->s_redic->redic = 4;
		else
			shell->s_redic->redic = 3;
		return (i);
	}
	return (-1);
}

// Check if have any redic
// Return -1 the there no one redic in the command
// Return the position of the current valid redic
static int	find_redic(t_shell *shell)
{
	int		i;
	char	*aux;
	int		ret;

	if (!shell->s_redic->cmd)
		return (-1);
	aux = shell->s_redic->cmd;
	i = -1;
	ret = -1;
	while (aux[++i])
	{
		ret = aux_find_redic(shell, aux, i);
		if (ret != -1)
		{
			if (shell->s_redic->status->len > 0)
			{
				if (shell->s_redic->status->lst_status
					[shell->s_redic->status->pos++] == FALSE)
					continue ;
			}
			return (ret);
		}
	}
	return (-1);
}

// Find and store file name of the current redic
// Return NUll if don't have any file name
// Return the file name if is success
char	*find_file(t_shell *shell, int *pos)
{
	char	**aux;
	char	*file;
	char	*tmp;

	if (shell->s_redic->redic == 1 || shell->s_redic->redic == 3)
		tmp = ft_substr(shell->s_redic->cmd, *pos + 1,
				ft_strlen(shell->s_redic->cmd));
	else
		tmp = ft_substr(shell->s_redic->cmd, *pos + 2,
				ft_strlen(shell->s_redic->cmd));
	if (ft_strcmp(tmp, "") == 0 || is_all_space(tmp))
	{
		free(tmp);
		return (NULL);
	}
	aux = ft_split(tmp, ' ');
	file = ft_strdup(aux[0]);
	*pos = ft_strlen(file);
	if (shell->s_redic->cmd)
		free(shell->s_redic->cmd);
	shell->s_redic->cmd = ft_split_rev(aux);
	free_list_string(aux);
	free(tmp);
	return (file);
}

// Split the string command using the parament pos
// The parament pos is the position of the current redic
// Return 2 if there is no file name
// Return 1 is success
int	parser_redic(t_shell *shell, int pos)
{
	char	*aux;

	shell->s_redic->parse = ft_substr(shell->s_redic->cmd, 0, pos);
	if (shell->s_redic->file)
		set_free_and_null(&shell->s_redic->file);
	if (!valid_redic(shell->s_redic->cmd, pos))
	{
		set_free_and_null(&shell->s_redic->parse);
		return (error_newline());
	}
	shell->s_redic->file = find_file(shell, &pos);
	aux = ft_substr(shell->s_redic->cmd, pos + 1,
			ft_strlen(shell->s_redic->cmd));
	if (shell->s_redic->cmd)
		set_free_and_null(&shell->s_redic->cmd);
	shell->s_redic->cmd = aux;
	return (1);
}

//signal 1 = into pipe
//signal 0 = without pipe
// Find the position of the redic and parser the string
// Return 1 if parse of string is success
// Return 0 if isn't a redic
int	check_redic(t_shell *shell, int signal)
{
	int	pos;

	if (signal == 1)
		shell->s_redic->cmd = ft_strdup(shell->parse_cmd);
	else if (signal == 0)
		shell->s_redic->cmd = ft_strdup(shell->command);
	pos = find_redic(shell);
	if (pos >= 0)
		return (parser_redic(shell, pos));
	return (0);
}
