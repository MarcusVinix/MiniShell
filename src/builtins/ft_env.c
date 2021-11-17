/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:40:09 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 19:56:11 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printlst(char *key, char *value, int fd, int sig)
{
	if (sig)
	{
		ft_putstr_fd(key, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(value, fd);
	}
}

//will decide which error will be print by the first string
//passed after command string 'env' 
//return the number of the error.
static int	verify_home(char *str)
{
	if (ft_strcmp(str, "/home") == 0)
	{
		invalid_permission_or_file("env", str, 1);
		return (126);
	}
	else
	{
		invalid_permission_or_file("env", str, 2);
		return (127);
	}
	return (0);
}

//print a list of environment
int	ft_env(t_shell *sh, int fd)
{
	if (sh->s_redic->redic > 2)
		fd = 1;
	if (ft_strlen_split(sh->split_cmd) != 1)
		return (verify_home(sh->split_cmd[1]));
	ft_lstiter(sh->lst_env, printlst, fd);
	return (0);
}
