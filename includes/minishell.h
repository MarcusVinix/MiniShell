/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:39:45 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/24 21:53:27 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# define NO_FILE "No such file or directory"
# define NO_OLDPWD "OLDPWD not set"
# define TRUE 1
# define FALSE 0

extern int	g_sh_status;

typedef struct s_status
{
	int		lst_status[100];
	int		pos;
	int		len;
}			t_status;
typedef struct s_redic
{
	int			in;
	int			out;
	int			redic;
	char		*file;
	char		*delimiter;
	char		*parse;
	char		*cmd;
	t_status	*status;
}			t_redic;

typedef struct s_shell
{
	int					in;
	char				*command;
	char				**split_cmd;
	char				*parse_cmd;
	int					fd_in;
	int					fd_out;
	int					len_env;
	int					ret;
	t_list				*lst_env;
	t_status			*status_pipe;
	t_redic				*s_redic;
	struct sigaction	act;
}			t_shell;

//builtins
int		ft_pwd(int fd, t_shell *shell);
void	ft_echo(t_shell *sh, int fd);
int		ft_env(t_shell *sh, int fd);
int		ft_cd(t_shell *shell, int fd);
int		ft_export(t_shell *sh, int fd, int sig);
int		ft_unset(t_shell *shell, t_list **lst, int fd);

//errors
int		not_found(char *command);
int		error_cd(char *message);
int		error_no_file(char *path);
int		invalid_option(char *s);
void	invalid_identifier(char *str);
int		no_file(char *file, t_shell *shell);
int		error_newline(void);
int		ft_invalid_identifier_unset(char *str);
int		error_heredoc(char **str, int *i);
int		invalid_permission_or_file(char *comm, char *str, int signal);

//free
void	free_all(t_shell *shell);
void	free_list_string(char **str);
void	exit_shell(t_shell *shell);
void	set_free_and_null(char **str);
void	free_four(char *var1, char *var2, char *var3, char *var4);

//utils
t_list	*create_bckup_env(char **env, t_shell *shell);
char	*find_value(t_list **lst, char *key);
int		change_value(t_list **lst, char *key, char *new_value, int sig);
void	get_command(t_shell *shell);
void	start_struct(t_shell *shell, char **env);
void	reset_struct(t_shell *shell);

//exec
int		ft_exec(t_shell *shell, int fd);
int		ft_check_path(char **str, t_shell *shell);
char	*check_path_command(char **str, t_shell *shell);
char	*find_command(char *path, char **command);
void	check_standart_fd(t_shell *shell, int fd_in);

void	handle_sigquit(int sig);
void	sigint_handle_cmd(int sig);
void	sigint_handle(int sig);
void	config_sigaction(struct sigaction *act, void (*handler)(int), int sig);
void	handle_heredoc(int sig_num);
int		check_quotes(t_shell *shell);
char	**get_env_var(t_list **list_env, t_shell *shell);
int		all_number(char *str);

//parser
int		check_command(t_shell *shell, int fd);
int		check_pipe(t_shell *shell);
int		exec_pipe(t_shell *shell);
int		check_redic(t_shell *shell, int signal);
int		trating_quotes(t_shell *shell);

//title
int		exec_redic(t_shell *shell);

//aux parser
int		valid_redic(char *cmd, int pos);
void	remove_quotes(t_shell *shell, int pos);
void	store_delimiter(t_shell *shell);
int		treatment_redic(t_shell *shell, int signal, int fd);
#endif
