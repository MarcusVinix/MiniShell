/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:46:06 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/15 14:39:55 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value(t_list **lst, char *key, char *new_value, int sig)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (new_value)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(new_value);
			}
			if (tmp->signal == 0)
				tmp->signal = sig;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	find_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_list	*create_bckup_env(char **env, t_shell *shell)
{
	int		i;
	int		pos;
	int		len;
	t_list	*list;

	list = NULL;
	i = 0;
	pos = 0;
	len = 0;
	while (env[i])
	{
		pos = find_pos(env[i]);
		len = ft_strlen(env[i]);
		ft_lstadd_back(&list, ft_lstnew(ft_substr(env[i], 0, pos),
				ft_substr(env[i], pos + 1, len - pos), 1));
		shell->len_env++;
		i++;
	}
	return (list);
}

char	*find_value(t_list **lst, char *key)
{
	t_list	*tmp;
	char	*resp;

	tmp = *lst;
	resp = ft_strtrim(key, " \'\"");
	while (tmp)
	{
		if (ft_strcmp(tmp->key, resp) == 0)
		{
			free(resp);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	free(resp);
	return (NULL);
}
