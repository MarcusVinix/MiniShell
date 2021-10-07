/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:03 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/06 22:02:04 by jestevam         ###   ########.fr       */
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

static void	check_is_exist(t_list *lst, char *new_env)
{
	char **key_val;

	key_val = ft_split_v2(new_env, '=');
	if (!change_value(&lst, key_val[0], key_val[1]))
	{
		if (key_val[1])
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(key_val[0]), 
					ft_strdup(key_val[1])));
	}
	free_list_string(key_val);
}

//signal 1 = print error;
//signal 2 = just return the number of error
static int verify_valid(char *str, int signal)
{
	if (str[0] == '-')
	{
		if (signal == 1)
			invalid_option(str[0]);
		return (2);
	}
	else if (str[0] == '.' || ft_isdigit(str[0]) || str[0] == '?')
	{
		if (signal == 1)
			invalid_identifier(str);
		return (1);
	}
	return (0);
}

int	ft_export(t_shell *sh)
{
	int count;
	int	resp;
	
	resp = 0;
	count = 1;
	while (sh->split_cmd[count])
	{
		if (verify_valid(sh->split_cmd[count], 1))
		{
			if (!resp)
				resp = verify_valid(sh->split_cmd[count], 2);
		}
		else
			check_is_exist(sh->lst_env, sh->split_cmd[count]);
		count++;
	}
	if (count == 1)
		ft_lstiter(sh->lst_env, printlst);
	return (resp);
}