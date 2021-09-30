/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:46:06 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/29 23:27:54 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!list)
			list = ft_lstnew(ft_substr(env[i], 0, pos),
				ft_substr(env[i], pos + 1, len - pos));
		list->next = ft_lstnew(ft_substr(env[i], 0, pos),
				ft_substr(env[i], pos + 1, len - pos));
		i++;
	}
	return (list);
}

char	*find_value(t_list **lst, char *key)
{
	while (*lst)
	{
		if (!ft_strcmp((*lst)->key, key))
			return ((*lst)->value);
		*lst = (*lst)->next;
	}
	return (NULL);
}
