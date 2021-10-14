/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 01:40:53 by coder             #+#    #+#             */
/*   Updated: 2021/10/14 04:27:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_shell *shell)
{
	char	*str;
	int		quotes;
	
	str = ft_strdup(shell->split_cmd[1]);
	quotes = 0;
	if (!str)
		return (0);
	if (*str == '\'')
	{
		free(shell->split_cmd[1]);
		shell->split_cmd[1] = ft_strtrim(str, "\'");
		quotes = 1;
	}
	else if (*str == '\"')
	{
		free(shell->split_cmd[1]);
		shell->split_cmd[1] = ft_strtrim(str, "\"");
		quotes = 2;
	}
	free(str);
	return (quotes);
}
