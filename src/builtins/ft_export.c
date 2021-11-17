/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:01:03 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 20:06:50 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printlst(char *key, char *value, int fd, int sig)
{
	if (sig)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(value, fd);
		ft_putchar_fd('\n', fd);
	}
}

//split a string by 2, taking the first occurrence of char c
char	**ft_split_v2(char *str, char c)
{
	int		count;
	int		len;
	char	**rslt;

	count = 0;
	len = ft_strlen(str);
	while (str[count] != c && str[count] != 0)
		count++;
	if (len == count)
		rslt = (char **)ft_calloc((len + 1), sizeof(char *));
	else
		rslt = (char **)ft_calloc(len, sizeof(char *));
	rslt[0] = ft_substr(str, 0, count);
	if (count++ < len)
	{
		if (count == len)
			rslt[1] = ft_strdup(" ");
		else
			rslt[1] = ft_substr(str, count, len);
	}
	return (rslt);
}

//will check if the variable exist;
//if yes, just refresh the data;
//if no, create a new variable at the list 
static void	check_is_exist(t_list *lst, char *new_env, int sig, t_shell *sh)
{
	char	**key_val;

	key_val = ft_split_v2(new_env, '=');
	if (!change_value(&lst, key_val[0], key_val[1], sig))
	{
		if (key_val[1])
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(key_val[0]),
					ft_strdup(key_val[1]), sig));
			sh->len_env++;
		}
	}
	free_list_string(key_val);
}

//signal 1 = print error;
//signal 2 = just return the number of error
static int	verify_valid(char *str, int sig)
{
	if (str[0] == '-')
	{
		if (sig == 1)
			invalid_option(str);
		return (2);
	}
	else if (str[0] == '.' || ft_isdigit(str[0])
		|| str[0] == '?' || str[0] == '/')
	{
		if (sig == 1)
			invalid_identifier(str);
		return (1);
	}
	return (0);
}

//will put a new environment variable in the list.
//if sig is 1, means that the command string "export" was writed;
//if sig is 0, means that the user writed the new environment variable
//without the command string
int	ft_export(t_shell *sh, int fd, int sig)
{
	int	count;
	int	resp;

	resp = 0;
	count = sig;
	if (sh->s_redic->redic > 2)
		fd = 1;
	while (sh->split_cmd[count])
	{
		if (verify_valid(sh->split_cmd[count], 2))
		{
			if (!resp)
				resp = verify_valid(sh->split_cmd[count], 1);
		}
		else
			check_is_exist(sh->lst_env, sh->split_cmd[count], sig, sh);
		count++;
	}
	if (count == 1 && sig == 1)
		ft_lstiter(sh->lst_env, printlst, fd);
	return (resp);
}
