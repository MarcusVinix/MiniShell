/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:40:09 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/22 18:48:53 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void printlst(char *key, char *value, int fd, int sig)
{
	if (sig)
	{
		ft_putstr_fd(key, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(value, fd);
	}
}
	

static int verify_$(t_shell *sh)
{
	int count;
	char *val;

	count = 1;
	while (sh->split_cmd[count])
	{
		if (sh->split_cmd[count][0] == '$')
		{
			val = find_value(&sh->lst_env, ++sh->split_cmd[count]);
			--sh->split_cmd[count];
			if (!ft_strcmp(val, " ") || !val)
			{
				count++;
				continue;
			}
			else if (val)
				printf("env: “%s”: No such file or directory\n", val);
		}
		else
			printf("env: “%s”: No such file or directory\n", sh->split_cmd[count]);
		return (127);
	}	
	return (0);
}

int	ft_env(t_shell *sh, int fd)
{
	if (sh->redic > 2)
		fd = 1;
	if (ft_strlen_split(sh->split_cmd) != 1)
	{
		//printf("env: “%s”: No such file or directory\n", sh->split_cmd[1]);
		if (verify_$(sh))
			return (127);
	}
	ft_lstiter(sh->lst_env, printlst, fd);
	return (0);
}
