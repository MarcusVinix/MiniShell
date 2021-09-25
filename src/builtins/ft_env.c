/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:40:09 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/24 22:20:32 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_list_string(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
}

void	ft_env(char *command, char **envi)
{
	char **str;
	int count;

	count = 0;
	str = ft_split(command, ' ');
	while (str[count])
		count++;
	if (count != 1 || ft_strcmp(str[0], "env"))
	{
		if (ft_strcmp(str[0], "env"))
			printf("%s: command not found\n", str[0]);
		else
			printf("%s: command not found\n", str[1]);
		return ;
	}
	while (*envi)
	{
		printf("%s\n", *envi);
		envi++;
	}
	free_list_string(str);
	return;
}