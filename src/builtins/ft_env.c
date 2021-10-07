/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:40:09 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/07 20:37:40 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void printlst(char *key, char *value)
{
	printf("%s=%s\n", key, value);
}

int	ft_env(t_shell *sh)
{
	if (ft_strlen_split(sh->split_cmd) != 1)
	{
		printf("env: “%s”: No such file or directory\n", sh->split_cmd[1]);
		return (127);
	}
	ft_lstiter(sh->lst_env, printlst);
	return (0);
}
