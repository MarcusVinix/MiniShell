/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:46:06 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/30 19:52:08 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value(t_list **lst, char *key, char *new_value)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return (1) ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	find_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_list	*create_bckup_env(char **env)
{
	int		i;
	int		pos;
	int		len;
	t_list	*list;

	list = NULL;
	i = 0;
	pos = 0;
	len = 0;
	while (env[i])
	{
		pos = find_pos(env[i]);
		len = ft_strlen(env[i]);
		ft_lstadd_back(&list, ft_lstnew(ft_substr(env[i], 0, pos),
			ft_substr(env[i], pos + 1, len - pos)));
		i++;
	}
	return (list);
}

char	*find_value(t_list **lst, char *key)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
