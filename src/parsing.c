/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotine <nikotine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:51:45 by nikotine          #+#    #+#             */
/*   Updated: 2024/01/03 21:13:58 by nikotine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 *	Returns the index of the next minishell's operator in the string,
 *	returns -1 if no operator is found.
*/
int	operator_pos(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (i);
	return (-1);
}

/*
 *	Returns the next operator id found in the given string
 *	id list : 
 *		0 : no operator found
 *		1 : pipe								; |
 *		2 : output redirection					; >
 *		3 : input redirection					; <
 *		4 : output redirection in append mode	; >>
 *		5 : here_doc							; <<
*/
int get_next_operator(char *str)
{
	int 	pos;

	pos = operator_pos(str);
	if (pos == -1)
		return (0);
	if (str[pos] == '|')
		return (1);
	if (str[pos] == '>' && str[pos + 1] != '>')
		return (2);
	if (str[pos] == '<' && str[pos + 1] != '<')
		return (3);
	if (str[pos] == '>' && str[pos + 1] == '>')
		return (4);
	if (str[pos] == '<' && str[pos + 1] == '<')
		return (5);
	return (-1);
}

/*	WORK IN PROGRESS
 *	Parses the line by cutting the commands from the operators then
 *	run the commands.
*/
void input_handler(t_data *data)
{
	char	*line;
	int		pos;

	line = ft_strdup(data->line);
	pos = operator_pos(line);
	while (pos != -1)
	{
		free(data->line);
		data->line = ft_substr(line, 0, pos);
		command_launcher(data);
		line += pos;
		pos = operator_pos(line);
	}
	free(data->line);
	data->line = line;
	command_launcher(data);
}
