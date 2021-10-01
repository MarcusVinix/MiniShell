/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:03 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/30 21:56:47 by jestevam         ###   ########.fr       */
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
	t_list *aux;

	aux = lst;
	key_val = ft_split_v2(new_env, '=');
	while (aux)
	{
		if(!ft_strcmp(key_val[0], aux->key))
		{
			if (key_val[1])
			{
				free(aux->value);
				aux->value = ft_strdup(key_val[1]);
			}
			break;
		}
		aux = aux->next;
	}
	if (!aux)
	{
		if (key_val[1])
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(key_val[0]), 
					ft_strdup(key_val[1])));
	}
	free_list_string(key_val);
}

void ft_export(char *command, t_shell *sh)
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
		check_is_exist(sh->lst_env, str[count++]);
	if (count == 1)
		ft_lstiter(sh->lst_env, printlst);
	free_list_string(str);
}