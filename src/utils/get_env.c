/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:09:20 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/10 17:07:36 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_data *data)
{
	char	*pwd;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD", 3))
			pwd = ft_substr(data->env[i], 4, ft_strlen(data->env[i]) - 4);
		i++;
	}
	return (pwd);
}

char	*get_oldpwd(t_data *data)
{
	char	*oldpwd;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "OLDPWD", 6))
			oldpwd = ft_substr(data->env[i], 7, ft_strlen(data->env[i]) - 7);
		i++;
	}
	return (oldpwd);
}

char	*get_home_path(t_data *data)
{
	char	*home_path;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "HOME", 4))
			home_path = ft_substr(data->env[i], 5,
				ft_strlen(data->env[i]) - 5);
		i++;
	}
	return (home_path);
}
