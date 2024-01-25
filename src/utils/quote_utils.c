/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:03:08 by nsalles           #+#    #+#             */
/*   Updated: 2024/01/25 17:10:18 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote(char *str, int pos) // unused
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] == 39 && (i == 0 || str[i - 1] != 92))
			single_quote++;
		else if (str[i] == 34 && (i == 0 || str[i - 1] != 92) && 
				single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	return (double_quote % 2 == 1 || single_quote % 2 == 1);
}

void	unclosed_parenthesis(char *str) // unfinished
{
	int	i;
	int	parenthesis_depth;

	parenthesis_depth = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
			parenthesis_depth++;
		else if (str[i] == ')')
			parenthesis_depth--;
	}
}
