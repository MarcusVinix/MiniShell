/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 11:51:04 by marcus            #+#    #+#             */
/*   Updated: 2021/10/20 17:37:12 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(char *, char*, int fd), int fd)
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		f(lst->key, lst->value, fd);
		lst = lst->next;
	}
}
