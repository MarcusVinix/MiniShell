/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:40:09 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/05 20:41:03 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void printlst(char *key, char *value)
{
	printf("%s=%s\n", key, value);
}

void	ft_env(t_shell *sh)
{
	if (ft_strlen_split(sh->split_cmd) != 1 
			|| ft_strcmp(sh->split_cmd[0], "env"))
	{
		if (ft_strcmp(sh->split_cmd[0], "env"))
			printf("%s: command not found\n", sh->split_cmd[0]);
		else
			printf("%s: command not found\n", sh->split_cmd[1]);
		return ;
	}
	ft_lstiter(sh->lst_env, printlst);
	return;
}
