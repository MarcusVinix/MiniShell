/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:03 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/06 21:14:05 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void printlst(char *key, char *value)
{
	printf("declare -x %s=%s\n", key, value);
}

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
	if (count++ < len)
	{
		if (count == len)
			rslt[1] = ft_strdup(" ");
		else
			rslt[1] = ft_substr(str, count, len);	
	}
		
	return (rslt);
}

static int	check_is_exist(t_list *lst, char *new_env)
{
	char **key_val;

	key_val = ft_split_v2(new_env, '=');
	if (key_val[0][0] == '.' || ft_isdigit(key_val[0][0]) || key_val[0][0] == '?')
	{
		printf("bash: export: `%s': not a valid identifier\n", new_env);
		free_list_string(key_val);
		return (-1);
	}
	if (!change_value(&lst, key_val[0], key_val[1]))
	{
		if (key_val[1])
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(key_val[0]), 
					ft_strdup(key_val[1])));
	}
	free_list_string(key_val);
	return (0);
}

void ft_export(t_shell *sh)
{
	int count;
	
	count = 1;
	while (sh->split_cmd[count])
		check_is_exist(sh->lst_env, sh->split_cmd[count++]);
	if (count == 1)
		ft_lstiter(sh->lst_env, printlst);
}