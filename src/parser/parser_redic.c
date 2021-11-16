/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:07:54 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/15 21:14:36 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	find_redic(t_shell *shell)
{
	int		i;
	char	*aux;
	int		ret;

	if (!shell->s_redic->cmd)
		return (-1);
	aux = shell->s_redic->cmd;
	i = 0;
	ret = -1;
	while (aux[i])
	{
		ret = aux_find_redic(shell, aux, i);
		if (ret != -1)
		{
			if (shell->s_redic->status->len > 0)
			{
				if (shell->s_redic->status->lst_status
					[shell->s_redic->status->pos++] == FALSE)
				{
					i++;
					continue ;
				}
			}
			return (ret);
		}
		i++;
	}
	return (-1);
}

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

int	parser_redic(t_shell *shell, int pos)
{
	char	*aux;

	shell->s_redic->parse = ft_substr(shell->s_redic->cmd, 0, pos);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
	if (!valid_redic(shell->s_redic->cmd, pos))
	{
		free(shell->s_redic->parse);
		shell->s_redic->parse = NULL;
		return (error_newline());
	}
	shell->s_redic->file = find_file(shell, &pos);
	aux = ft_substr(shell->s_redic->cmd, pos + 1,
			ft_strlen(shell->s_redic->cmd));
	if (shell->s_redic->cmd)
	{
		free(shell->s_redic->cmd);
		shell->s_redic->cmd = NULL;
	}
	shell->s_redic->cmd = aux;
	return (1);
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
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
