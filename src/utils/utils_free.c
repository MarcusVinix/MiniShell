/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:07:25 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/04 23:25:08 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{
	free(shell->command);
	ft_lstclear(&shell->lst_env, free);
	free_list_string(shell->split_cmd);
}

void free_list_string(char **str)
{
	int count;

	count = 0;
	while (str[count])
		free(str[count++]);
	free(str);
}
