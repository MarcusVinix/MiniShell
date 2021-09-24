/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/24 19:03:22 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list_string(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	free(str);
}

void ft_echo(char *command)
{
	char **str;
	int count;

	count = 1;
	str = ft_split(command, ' ');
	while (str[count])
	{
		printf("%s ", str[count]);
		count++;
	}
	free_list_string(str);
	printf("\n");
}