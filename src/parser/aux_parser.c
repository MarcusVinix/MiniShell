/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:35:04 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/16 20:55:55 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redic(char *cmd, int pos)
{
	int	i;

	i = 0;
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
