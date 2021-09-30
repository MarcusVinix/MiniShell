/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:11:12 by marcus            #+#    #+#             */
/*   Updated: 2021/09/29 23:19:49 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *key, void *value)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list) * 1);
	if (element == NULL)
		return (NULL);
	element->key = key;
	element->value = value;
	element->next = NULL;
	return (element);
}
