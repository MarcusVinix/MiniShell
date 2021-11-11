#include "minishell.h"

static void remove_quotes(t_shell *shell, int pos)
{
	char	*str_left;
	char	*str_right;

	str_left = ft_substr(shell->command, 0, pos);
	str_right = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));
	set_free_and_null(&shell->command);
	shell->command = ft_strjoin(str_left, str_right);
	free(str_left);
	free(str_right);
}

static void put_variable(t_shell *shell, int pos)
{
	char	*str_left;
	char	*str_middle;
	char	*str_right;
	char	*value;
	char	*key;

	if (shell->command[pos + 1] == ' ' || shell->command[pos + 1] == '\0')
		return ;
	str_left = ft_substr(shell->command, 0, pos);
	while (shell->command[++pos])
	{
		if (shell->command[pos] == ' ' || shell->command[pos] == '?' || shell->command[pos + 1] == '\"')
			break ;
	}
	printf("char: %c %i\n", shell->command[pos], pos);
	key = ft_substr(shell->command, ft_strlen(str_left) + 1, pos - (ft_strlen(str_left)));
	printf("KEYY |%s|\n", key);
	if (key[0] != '?')
		value = ft_strdup(find_value(&shell->lst_env, key));
	else
	{
		pos++;
		value = ft_itoa(*shell->p_status);
	}
	printf("value |%s|\n", value);
	if (value == NULL)
		value = ft_strdup("");
	str_middle = ft_strjoin(str_left, value);
	str_right = ft_substr(shell->command, pos, ft_strlen(shell->command));
	printf("RIGHT |%s|\n", str_right);
	set_free_and_null(&shell->command);
	shell->command = ft_strjoin(str_middle, str_right);
	printf("command |%s|\n", shell->command);

	free(str_left);
	free(str_middle);
	free(str_right);
	free(value);
	free(key);
}

int	trating_quotes(t_shell *shell)
{
	char	quote;
	int		i;
	int		sig;

	i = 0;
	sig = 0;
	quote = ' ';
	while (shell->command[i])
	{
		if (sig == 1)
		{
			if (shell->command[i] == quote)
			{
				sig = 0;
				remove_quotes(shell, i);
				continue ;
			}
		}
		else
		{
			if (shell->command[i] == '\'' || shell->command[i] == '"')
			{
				quote = shell->command[i];
				sig = 1;
				remove_quotes(shell, i);
				continue ;
			}
		}
		if (quote != '\'' && shell->command[i] == '$')
		{
			put_variable(shell, i);
			printf("cmd |%s|\n", shell->command);
		}
		i++;
	}
	printf("commanddddd  |%s|\n", shell->command);
	return (0);
}