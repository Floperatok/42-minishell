/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:21:43 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/14 16:58:09 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_redirection(char **cmds, int *index, t_data *data)
{
	int		fd;
	char	*file;

	file = cmds[*index + 1];
	if (!file)
	{
		ft_putstr("minishell: syntax error: ", 2);
		ft_putstr("unexpected pipe or redirection\n", 2);
		return ;
	}
	file = parse_line(ft_strdup(file), data->env);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2);
		write(2, file, ft_strlen(file));
		perror("");
		return ;
	}
	data->line = parse_line(ft_strdup(cmds[*index]), data->env);
	free(file);
	(*index)++;
	dup2(fd, STDOUT_FILENO);
	if (!builtin_launcher(data))
		ft_fork_exec(data->line, data->env);
}
