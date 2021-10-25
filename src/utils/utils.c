/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 01:40:53 by coder             #+#    #+#             */
/*   Updated: 2021/10/24 23:21:32 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_shell *shell)
{
	char	*str;
	int		quotes;
	
	str = ft_strdup(shell->split_cmd[1]);
	quotes = 0;
	if (!str)
		return (0);
	if (*str == '\'')
	{
		free(shell->split_cmd[1]);
		shell->split_cmd[1] = ft_strtrim(str, "\'");
		quotes = 1;
	}
	else if (*str == '\"')
	{
		free(shell->split_cmd[1]);
		shell->split_cmd[1] = ft_strtrim(str, "\"");
		quotes = 2;
	}
	free(str);
	return (quotes);
}

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