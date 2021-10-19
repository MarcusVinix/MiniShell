
#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
# define NO_FILE "No such file or directory"
# define NO_OLDPWD "OLDPWD not set"


typedef struct s_shell
{
	char	*command;
	char	**split_cmd;
	t_list	*lst_env;
	char	*parse_cmd;
}			t_shell;

//builtins
int		ft_pwd(t_shell *shell, char *command);
void	ft_echo(t_shell *sh);
int		ft_env(t_shell *sh);
int		ft_cd(t_shell *shell);
int		ft_export(t_shell *sh);
int		ft_unset(t_shell *shell, t_list **lst);


//errors
int		not_found(char *command);
int		error_cd(char *message);
int		error_no_file(char *path);
int		invalid_option(char *s);
void	invalid_identifier(char *str);

//free
void	free_all(t_shell *shell);
void	free_list_string(char **str);

//utils
t_list	*create_bckup_env(char **env);
char	*find_value(t_list **lst, char *key);
int		change_value(t_list **lst, char *key, char *new_value);
int		ft_exec(t_shell *shell);
void	get_command(t_shell  *shell);
void	sigquit_handle(int sig_num);
int		check_quotes(t_shell *shell);

//parser
int		check_command(t_shell *shell, int *status);
void	check_pipe(t_shell *shell);

#endif
