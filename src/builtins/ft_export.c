/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:03 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/26 16:27:25 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_v2(char *str, char c)
{
	int count;
	int len;
	char **rslt;

	count = 0;
	len = ft_strlen(str);
	while (str[count] != c && str[count] != 0)
		count++;
	if (len == count)
		rslt = (char **)ft_calloc((len + 1), sizeof(char *));
	else
		rslt = (char **)ft_calloc(len, sizeof(char *));
	rslt[0] = ft_substr(str, 0, count);
	if (count < len)
		rslt[1] = ft_substr(str, ++count, len);
	return (rslt);
}

static void	check_is_exist(char **env, char *new_env)
{
	char **key_val;
	char **exist_k_v;
	int count;
	int signal;

	count = 0;
	signal = 0;
	key_val = ft_split_v2(new_env, '=');
	while (env[count])
	{
		exist_k_v = ft_split_v2(env[count], '=');
		if(!ft_strcmp(exist_k_v[0], key_val[0]))
		{
			env[count] = ft_strdup(new_env);
			signal = 1;
		}
		count++;
	}
	if (signal)
		env[count] = ft_strdup(new_env);
	free_list_string(key_val);
}

void ft_export(char *command, char** env)
{
	char **str;
	int count;
	
	str = ft_split(command, ' ');
	if (ft_strcmp(str[0], "export"))
	{
		free_list_string(str);
		return;
	}
	count = 1;
	while (str[count])
	{
		check_is_exist(env, str[1]);
		count++;
	}
	free_list_string(str);
}