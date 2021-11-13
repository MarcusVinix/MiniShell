/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:04:58 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/24 13:14:47 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_shell *shell, t_list **lst)
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
					tmp->next = next;
					shell->len_env--;
					break ;
				}
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int	check_unset(char *tmp)
{
	int	j;

	if (!tmp)
		return (ft_invalid_identifier_unset(""));
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '-' || tmp[j] == '.' || ft_isdigit(tmp[0]) || tmp[0]
			== '$' || tmp[j] == '=')
		{
			if (tmp[j] == '-' && j == 0)
				return (invalid_option(tmp));
			else
				return (ft_invalid_identifier_unset(tmp));
		}
		j++;
	}
	return (0);
}

static void	aux_check(t_shell *shell, char *tmp, int i)
{
	char	*str;

	str = find_value(&shell->lst_env, tmp + 1);
	if (str)
	{
		free(shell->split_cmd[i]);
		shell->split_cmd[i] = ft_strdup2(str);
	}
}

int	check_variables(t_shell *shell)
{
	char	*tmp;
	int		i;
	int		tmp_stat;
	int		stat;

	i = 1;
	tmp = NULL;
	tmp_stat = 0;
	stat = 0;
	while (shell->split_cmd[i])
	{
		tmp = ft_strdup(shell->split_cmd[i]);
		if (tmp[0] == '$')
			aux_check(shell, tmp, i);
		free(tmp);
		tmp_stat = check_unset(shell->split_cmd[i]);
		if ((stat != 2 && i == 1) && tmp_stat != 0)
			stat = tmp_stat;
		i++;
	}
	return (stat);
}

int	ft_unset(t_shell *shell, t_list **lst, int fd)
{
	int		stat;

	if (fd > 2)
		return (0);
	stat = 0;
	stat = check_variables(shell);
	if (stat == 0)
		del_env(shell, lst);
	return (stat);
}
