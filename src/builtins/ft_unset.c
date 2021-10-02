/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:04:58 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/02 00:20:06 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *shell, t_list **lst)
{
	t_list	*tmp;
	char	*var;
	t_list	*next;
	int		check;

	check = 0;
	var = ft_strtrim(shell->command + 6, " ");
	tmp = *lst;
	if (find_value(&shell->lst_env, var))
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->next->key, var) == 0)
			{
				check = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (check)
		{
			next = tmp->next->next;
			ft_lstdelone(tmp->next, free);
			tmp->next =  next;
		}
	}
	free(var);
}
