/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 11:51:04 by marcus            #+#    #+#             */
/*   Updated: 2021/09/30 20:28:05 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(char *, char*))
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		f(lst->key, lst->value);
		lst = lst->next;
	}
}
