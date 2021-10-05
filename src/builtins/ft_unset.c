/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:04:58 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/04 23:08:14 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *shell, t_list **lst)
{
	t_list	*tmp;
	t_list	*next;
	int		i;

	tmp = *lst;
	i = 1;
	while (shell->split_cmd[i])
	{
		if (find_value(&shell->lst_env, shell->split_cmd[i]))
		{
			while (tmp)
			{
				if (ft_strcmp(tmp->next->key, shell->split_cmd[i]) == 0)
				{
					next = tmp->next->next;
					ft_lstdelone(tmp->next, free);
					tmp->next =  next;
					break ;
				}
				tmp = tmp->next;
			}
		}
		i++;
	}
}
