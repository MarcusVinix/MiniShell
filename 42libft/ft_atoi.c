/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:02:00 by mavinici          #+#    #+#             */
/*   Updated: 2021/05/18 20:02:00 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	errors(void)
{
	ft_putendl_fd("Error", 1);
	exit(0);
}

static int	ft_ignore(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	number;

	sign = 1;
	number = 0;
	while (ft_ignore(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nptr) == 1)
		number = number * 10 + (*nptr++ - '0');
	if ((number * sign) > INT_MAX || (number * sign) < INT_MIN)
		errors();
	return (number * sign);
}
