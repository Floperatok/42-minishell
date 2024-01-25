/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:35:30 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/25 21:52:54 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(t_data *data)
{
	char	*line;

	line = ft_strdup(data->line); // Avant il y avait un parse line ici
	if (!line)
		return (0);
	if (line && line[0] == 4)
		ft_exit(data);
	if (!ft_strcmp(line, "exit") || !ft_strncmp(data->line, "exit ", 5))
	{
		free(line);
		ft_exit(data);
	}
	free(line);
	return (0);
}

static void	check_exit_args(t_data *data, int *i)
{
	if (data->line[*i] != ' '
		&& (data->line[*i] < '0' || data->line[*i] > '9'))
	{
		*i = 5;
		while (data->line[*i] == ' ')
			(*i)++;
		ft_putstr("exit\n", 1);
		ft_putstr("minishell: exit: ", 2);
		while (data->line[*i])
			write(2, &data->line[(*i)++], 1);
		ft_putstr(": numeric argument required\n", 2);
		free_all(data);
		g_exit_status = 2;
		exit(g_exit_status);
	}
}

/* exit builtin */
void	ft_exit(t_data *data)
{
	int		i;
	char	*arg;

	i = 5;
	if (!ft_strncmp(data->line, "exit ", 5))
	{
		if (data->line[i] == '-')
			i++;
		while (data->line[i])
		{
			check_exit_args(data, &i);
			i++;
		}
	}
	g_exit_status = 0;
	if (data->line[4] && data->line[5])
	{
		arg = ft_substr(data->line, 5, ft_strlen(data->line) - 5);
		g_exit_status = ft_atoi(arg) % 256;
		free(arg);
	}
	ft_putstr("exit\n", 1);
	free_all(data);
	exit(g_exit_status);
}
