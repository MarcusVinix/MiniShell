
#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
# define NO_FILE "No such file or directory"
# define NO_OLDPWD "OLDPWD not set"

typedef struct s_redic
{
	int 	in;
	int		out;
	int		redic;
	char	*file;
	char	*delimiter;
}			t_redic;

typedef struct s_shell
{
	char	*command;
	char	**split_cmd;
	t_list	*lst_env;
	char	*parse_cmd;
	int		fd_in;
	int		fd_out;
	int		*p_status;
	int		len_env;
	t_redic	*s_redic;
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
int	error_newline(t_shell *shell);

//free
void	free_all(t_shell *shell);
void	free_list_string(char **str);
void	exit_shell(t_shell *shell, int *status);

//utils
t_list	*create_bckup_env(char **env, t_shell *shell);
char	*find_value(t_list **lst, char *key);
int		change_value(t_list **lst, char *key, char *new_value, int sig);
int		ft_exec(t_shell *shell, int fd);
void	get_command(t_shell  *shell);
void	sigint_handle(int sig_num);
void	sigquit_handle(int sig);
void	handle_heredoc(int sig_num);
int		check_quotes(t_shell *shell);
char	**get_env_var(t_list **list_env, t_shell *shell);
int		all_number(char *str);

//parser
int		check_command(t_shell *shell, int *status, int fd);
int		check_pipe(t_shell *shell);
int		check_redic(t_shell *shell);

//title
int		exec_redic(t_shell *shell);
#endif
