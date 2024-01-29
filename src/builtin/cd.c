/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:24:16 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 20:45:48 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Checks if there is a space after 'cd'. If not, executes the specified
 *	command.
*/
static int	cd_error(t_data *data)
{
	if (data->line[2] && data->line[2] != ' ')
	{
		ft_exec(data->line, data->env);
		return (1);
	}
	return (0);
}

/*
 *	Returns an error when too much arguments are specified in 'cd' command.
 *	Exit status code is 1;
*/
static int	cd_check_args(t_data *data)
{
	int	i;

	i = 3;
	while (data->line[2] && data->line[i])
	{
		if (data->line[i] == ' ')
		{
			ft_putstr("minishell: cd: too many arguments\n", 2);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

/*
 *	Returns the HOME path from the env.
*/
static char	*cd_home_path(t_data *data)
{
	char	*home_path;
	int		i;

	home_path = NULL;
	i = 0;
	while (data->env[i])
	{
		if (!strncmp(data->env[i], "HOME", 4))
			home_path = ft_substr(data->env[i], 5, ft_strlen(data->env[i]) - 5);
		i++;
	}
	return (home_path);
}

/*
 *	Returns the path specified as argument for the 'cd' command.
*/
static char	*get_cd_path(t_data *data)
{
	char	*path;

	if (!data->line[2])
		path = cd_home_path(data);
	else if (!ft_strcmp(data->line, "cd -"))
	{
		path = get_oldpwd(data);
		ft_putstr(path, 1);
		ft_putstr("\n", 1);
	}
	else
		path = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
	return (path);
}


/*
 *	Builtin: cd.
 *	When the 'cd' command is used, this function will change 
 *	the current directory according to the path specified as argument.
 *	If no path is specified, it will make a cd to the HOME directory.
 *	If '~' is used as an argument, it will be replaced by the HOME path.
 *	If 'cd -' command is used, it will return to the previous location.
 *	Exit status code is 0 in case of success or 1 in case of failure.
*/
void	ft_cd(t_data *data)
{
	char	*error_msg;
	char	*path;
	char	*oldpwd;

	path = NULL;
	if (cd_error(data))
		return ;
	if (!cd_check_args(data))
		return ;
	path = get_cd_path(data);
	oldpwd = get_oldpwd(data);
	set_old_pwd(data, NULL);
	g_exit_status = 0;
	if (chdir(path) == -1)
	{
		set_old_pwd(data, oldpwd);
		free(oldpwd);
		error_msg = ft_strjoin("minishell: cd: ", path);
		perror(error_msg);
		g_exit_status = 1;
		free(error_msg);
	}
	set_pwd(data);
	free(oldpwd);
	free(path);
}
