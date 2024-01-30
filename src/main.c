/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/30 15:04:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;
int	g_sigint;
int	g_pid;

void	minishell(t_data *data, int	saved_stdin)
{
	int	is_old_line_null;

	is_old_line_null = 1;
	while (1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		if (g_sigint && is_old_line_null)
			ft_putstr("\n", 1);
		g_sigint = 0;
		refresh_prompt(data);
		data->line = readline(data->prompt);
		if (!data->line && !g_sigint)
			return (ft_putstr("exit\n", 1), free_all(data), rl_clear_history());
		if (!data->line && g_sigint && is_old_line_null)
			ft_putstr("\n", 1);
		// printf("old = %d\n", is_old_line_null);	
		is_old_line_null = data->line != NULL;
		if (ft_strlen(data->line) > 0)
		{
			if (!is_unclosed_quotes(data))
				add_history(data->line);
			parse_logic_operators(data);
		}
		free(data->line);
	}
}

int	main(int ac, char **av, char **base_env)
{
	t_data	data;

	(void) av;
	if (ac != 1)
	{
		ft_putstr("Error: Too much arguments. No argument needed.\n", 2);
		return (1);
	}
	data.env = cpy_env(base_env);
	data.prompt = NULL;
	init_export(&data);
	g_exit_status = 0;
	g_pid = 1;
	g_sigint = 0;
	signal(SIGINT, signals_handler);
	sigquit_handler();
	minishell(&data, dup(STDIN_FILENO));
	return (0);
}

// int main(void)
// {
// 	char *line = ft_strdup("");
// 	char **array;
	
// 	printf("minishell\n");
// 	while (ft_strncmp(line, "exit", 4))
// 	{
// 		free(line);
// 		line = get_next_line(0);
// 		line[ft_strlen(line) - 1] = '\0';
// 		array = split_commands(line);
// 		printf("array[0] = %s\n", array[0]);
// 		int i = 0;
// 		while (array[++i])
// 		{
// 			printf("array[%d] = %s\n", i, array[i]);
// 			free(array[i]);
// 		}
// 		printf("array[%d] = %s\n", i, array[i]);
// 		free(array);
// 	}
// 	free(line);
// 	return (0);
// }