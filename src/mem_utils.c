/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 22:39:17 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/27 22:40:17 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = '\0';
		i++;
	}
}

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
