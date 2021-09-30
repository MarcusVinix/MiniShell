/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:46:06 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/29 22:40:53 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_bckup_env(char **env)
{
	(void)env;
	t_list *list = NULL;

	return list;
}

char	*find_value(t_list **lst, char *key)
{
	while (*lst)
	{
		if (!ft_strcmp(*lst->key, key))
			return (*lst->value);
		*lst = *lst->next;
	}
	return (NULL);
}