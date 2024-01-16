/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:46:43 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/16 19:50:16 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	error_value;

static void	parse_dollar_value(t_data *data, char *new_line, int *i, int *j)
{
	char	*var;
	int		k;

	k = 0;
	while (data->line[*i + k] && data->line[*i + k] != ' '
		&& data->line[*i + k] != '\'' && data->line[*i + k] != '\"'
		&& data->line[*i + k] != '/' && data->line[*i + k] != '\\')
		k++;
	var = get_dollar_var(data, i, &k);
	k = 0;
	while (var && var[k])
	{
		new_line[*j] = var[k];
		(*j)++;
		k++;
	}
	if (var)
		free(var);
}

static void	parse_dollar_var(t_data *data, char *new_line, int *i, int *j)
{
	char	*err_val;
	int		k;

	k = 0;
	if (data->line[*i + 1] == ' ' || data->line[*i + 1] == '\0')
		return ;
	(*i)++;
	if (data->line[*i] == '?')
	{
		err_val = ft_itoa(error_value);
		while (err_val[k])
		{
			new_line[*j] = err_val[k];
			(*j)++;
			k++;
		}
		free(err_val);
	}
	else if (data->line[*i] >= '0' && data->line[*i] <= '9')
		(*i)++;
	else
		parse_dollar_value(data, new_line, i, j);
}

static void	parse_tilde(t_data *data, char *newline, int *i, int *j)
{
	char	*home_path;
	int		k;

	if (data->line[*i + 1])
		(*i)++;
	home_path = get_home_path(data);
	k = 0;
	while (home_path && home_path[k])
	{
		newline[*j] = home_path[k];
		(*j)++;
		k++;
	}
	if (home_path)
		free(home_path);
}

static void	parsed_line(t_data *data, char *new_line,
		int *in_singleq, int *in_doubleq)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (data->line[++i])
	{
		if (data->line[i] == ' ' && !(*in_singleq) && !(*in_doubleq))
			parse_spaces(data->line, &i);
		if (data->line[i] == '\\' && !(*in_singleq) && !(*in_doubleq))
			i++;
		if (data->line[i] == '$' && !(*in_singleq) && (i == 0
				|| data->line[i - 1] != '\\') && data->line[i + 1] != '~')
			parse_dollar_var(data, new_line, &i, &j);
		if (data->line[i] == '~' && !(*in_singleq) && !(*in_doubleq)
			&& data->line[i - 1] == ' ' && (data->line[i + 1] == ' '
				|| data->line[i + 1] == '/' || !data->line[i + 1]))
			parse_tilde(data, new_line, &i, &j);
		if (parse_conditions(data->line, i, *in_singleq, *in_doubleq))
			new_line[j++] = data->line[i];
		if ((data->line[i] == '\'' || data->line[i] == '\"'))
			in_or_out_quotes(data->line, in_singleq, in_doubleq, i);
	}
}

char	*parse_line(char *line, char **env)
{
	t_data	data;
	char	*new_line;
	int		in_singleq;
	int		in_doubleq;
	int		len;

	data.line = ft_strtrim(line, " ");
	data.env = env;
	in_singleq = 0;
	in_doubleq = 0;
	if (count_double_quotes(line) % 2
		|| count_single_quotes(line) % 2)
	{
		ft_putstr("minishell: quotes error\n", 2);
		return (NULL);
	}
	len = 0;
	new_line_len(&data, &len, in_singleq, in_doubleq);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	parsed_line(&data, new_line, &in_singleq, &in_doubleq);
	free(line);
	free(data.line);
	return (new_line);
}