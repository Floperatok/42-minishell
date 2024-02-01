/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:03:53 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/01 17:00:41 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Returns the variable name, including the '=' character at the end
 *	if there is one.
*/
char	*get_var_name(char *export_line, int i)
{
	char	*var_name;
	int		start;

	start = i;
	while (export_line[i])
	{
		if (export_line[i] == '=')
			break ;
		i++;
	}
	var_name = ft_substr(export_line, start, i - start);
	return (var_name);
}

/*
 *	Adds a new variable in export list.
*/
static void	add_export_new_var(t_data *data, char *var)
{
	t_export	*new;

	if (!var)
		return ;
	new = lst_new_node(convert_env_export(var));
	lst_add_back(&data->export, new);
	sort_export(data);
}

/*
 *	Adds a variable in export or modifies his value. Adds it in env too
 *	if a value is specified, or modifies his value if it already exists.
*/
static void	add_export_var(t_data *data, char *var)
{
	t_export	*ptr;
	char		*var_name;

	add_env_var(data, var);
	ptr = data->export;
	while (ptr)
	{
		var_name = get_var_name(ptr->content, 11);
		if (!ft_strncmp(var_name, var, ft_strlen(var_name)))
		{
			if (var[ft_strlen(var_name)] == '=')
			{
				free(ptr->content);
				ptr->content = convert_env_export(var);
				sort_export(data);
				return (free(var_name));
			}
			else if (!var[ft_strlen(var_name)])
				return (free(var_name));
		}
		free(var_name);
		ptr = ptr->next;
	}
	add_export_new_var(data, var);
}

/*
 *	Export variables in export, and environnement if a value is specified.
 *	In case of invalid argument, exit status code is 1 and it returns
 *	an error, but it still exports other variables.
*/
static void	export_var(char *command, t_data *data)
{
	char	*var;
	int		i;
	int		j;

	i = 6;
	while (command[i])
	{
		j = 0;
		i++;
		while (command[i + j] && command[i + j] != ' ')
			j++;
		var = ft_substr(command, i, j);
		if (var[0] == '=')
		{
			ft_putstr("minishell: export: `", 2);
			ft_putstr(var, 2);
			ft_putstr("': not a valid identifier\n", 2);
			g_exit_status = 1;
		}
		else
			add_export_var(data, var);
		free(var);
		i += j;
	}
}

/*
 *	Builtin: export.
 *	Prints the export variables on new lines if no argument is specified.
 *	If the export command is followed by arguments, exports the corresponding
 *	variables into export, and into env if values are specified.
 *	Exit status code is 0 in case of success or 1 if one of the variables
 *	failed to be added.
*/
void	ft_export(char *command, t_data *data)
{
	char	*arg;

	g_exit_status = 0;
	if (!command[6])
	{
		sort_export(data);
		print_export(data);
	}
	else
	{
		if (!((command[7] >= 'a' && command[7] <= 'z')
			|| (command[7] >= 'A' && command[7] <= 'Z')))
		{
			arg = ft_substr(command, 7, ft_strlen(command) - 7);
			ft_putstr("bash: export: `", 2);
			ft_putstr(arg, 2);
			ft_putstr("': not a valid identifier\n", 2);
			free(arg);
			return ;
		}
		export_var(command, data);
	}
}
