/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 01:40:53 by coder             #+#    #+#             */
/*   Updated: 2021/11/24 17:16:37 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save all environment variables into a char **
// Return NULL if have some error
// Return a char ** with all the environment variable if is succes
char	**get_env_var(t_list **list_env, t_shell *shell)
{
	char	**env;
	t_list	*list;
	char	*tmp;
	int		i;

	env = malloc(sizeof(char *) * (shell->len_env + 1));
	if (!env)
		return (NULL);
	list = *list_env;
	i = 0;
	while (list)
	{
		tmp = ft_strjoin(list->key, "=");
		env[i++] = ft_strjoin(tmp, list->value);
		free(tmp);
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}

// Check if its everything number
int	all_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2);
		i++;
	}
	return (ft_atoi(str));
}
