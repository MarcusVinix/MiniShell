
#include "minishell.h"

int	status;

void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;
	int		ret;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	if (shell->command)
		free(shell->command);
	shell->command = readline(prompt);
	ret = 0;
	free(prompt);
	add_history(shell->command);
}

void	start_struct(t_shell *shell, char **env)
{
	shell->command = NULL;
	shell->lst_env = create_bckup_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	status = 0;
	if (argc != 1 || argv[1])
		return (0);
	start_struct(&shell, env);
	while (1)
	{
		get_command(&shell);
		check_pipe(&shell);
		while (shell.parse_cmd)
		{
			check_command(&shell, &status);
			free(shell.parse_cmd);
			shell.parse_cmd = NULL;
			check_pipe(&shell);
		}
		check_command(&shell, &status);
		free_list_string(shell.split_cmd);
	}
	return (status);
}
