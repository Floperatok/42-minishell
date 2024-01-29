/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:39:17 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/29 22:59:20 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	Initializes a memory space with 0.
*/
void	ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = '\0';
		i++;
	}
}

/*
 *	Allocates a memory space with malloc and sets it to 0.
*/
void	*ft_calloc(size_t n, size_t size)
{
	void	*pointer;

	if (size != 0 && n * size / size != n)
		return (NULL);
	pointer = malloc(n * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, n * size);
	return (pointer);
}

/*
 *	Frees a double array of characters
*/
void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
 *	At the end of the program, frees all allocated memory
 *	if the corresponding space exists.
*/
void	free_all(t_data *data)
{
	rl_clear_history();
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->env)
		free_double_array(data->env);
	if (data->export)
		free_export(&data->export);
}

/*
 *	Frees the export list and sets it on NULL.
*/
void	free_export(t_export **lst)
{
	if (lst && *lst)
	{
		free_export(&(*lst)->next);
		free((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
