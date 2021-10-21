/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:04:58 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/21 18:15:56 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_env(t_shell *shell, t_list **lst)
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
	return (0);
}

int	ft_invalid_identifier(char *str)
{
	printf("minishell: unset: `%s': not a valid identifier\n", str);
	return (1);
}

int	check_unset(char *tmp, int quotes)
{
	int	j;

	if (!tmp && quotes == 2)
		return (ft_invalid_identifier(""));
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '-' || tmp[j] == '.' || ft_isdigit(tmp[0]) ||
			(tmp[0] == '$' && quotes == 1))
		{
			if (tmp[j] == '-' && j == 0)
				return (invalid_option(tmp));
			else
				return (ft_invalid_identifier(tmp));
		}
		j++;
	}
	return (0);
}

int	check_variables(t_shell *shell, int quotes)
{
	char	*tmp;
	char	*str;
	int		i;
	int		tmp_stat;
	int		stat;

	i = 1;
	tmp = NULL;
	str = NULL;
	tmp_stat = 0;
	stat = 0;
	while (shell->split_cmd[i])
	{
		tmp = ft_strdup(shell->split_cmd[i]);
		printf("tmp is %s\n", tmp);
		if (quotes == 2 || tmp[0] == '$')
		{
			str = find_value(&shell->lst_env, tmp + 1);
			if ((str || quotes == 2) && quotes != 1)
			{
				free(shell->split_cmd[i]);
				shell->split_cmd[i] = ft_strdup2(str);
			}
		}
		free(tmp);
		tmp_stat = check_unset(shell->split_cmd[i], quotes);
		if ((stat != 2 && i == 1) && tmp_stat != 0)
			stat = tmp_stat;
		i++;
	}
	return (stat);
}

int	ft_unset(t_shell *shell, t_list **lst, int fd)
{
	int		stat;
	int		quotes;

	if (fd > 2)
		return (0);
	stat = 0;
	quotes = check_quotes(shell);
	stat = check_variables(shell, quotes);
	if (stat == 0)
		stat = del_env(shell, lst);
	return (stat);
}
