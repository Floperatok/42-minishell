/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:09:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/14 00:05:37 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_launcher(t_data *data)
{
	if (!data->line)
		return (1);
	if (!ft_strncmp(data->line, "pwd", 3)
		&& (data->line[3] == ' ' || !data->line[3]))
		ft_pwd();
	else if (!ft_strcmp(data->line, "echo")
		|| !ft_strncmp(data->line, "echo ", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->line, "cd", 2))
		ft_cd(data);
	else if (!ft_strcmp(data->line, "env")
		|| !ft_strncmp(data->line, "env ", 4))
		ft_env(data);
	else if (!ft_strncmp(data->line, "export", 6))
		ft_export(data);
	else if (!ft_strcmp(data->line, "exit")
		|| !ft_strncmp(data->line, "exit ", 5))
		ft_exit(data);
	else
		return (0);
	return (1);
}

void	minishell(t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		refresh_prompt(data);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		data->line = readline(data->prompt);
		if (!data->line)
		{
			free_double_array(data->env);
			clear_history();
			break ;
		}
		add_history(data->line);
		if (ft_strlen(data->line) != 0)
			input_handler(data);
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
	minishell(&data);
	return (0);
}
