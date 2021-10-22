/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:11:12 by marcus            #+#    #+#             */
/*   Updated: 2021/10/21 22:48:02 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *key, void *value, int sig)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list) * 1);
	if (element == NULL)
		return (NULL);
	element->key = key;
	element->value = value;
	element->signal = sig;
	element->next = NULL;
	return (element);
}
