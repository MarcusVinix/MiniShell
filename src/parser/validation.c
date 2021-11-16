/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:35:04 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/15 19:35:31 by mavinici         ###   ########.fr       */
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
