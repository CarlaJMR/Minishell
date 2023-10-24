/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/24 10:20:38 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

void	skip_spaces(char *s, int *i)
{
	while (ft_is_space(s[*i]))
		(*i)++;
}

void	print_syntax_error(char c)
{
	ft_putstr_fd("Syntax error near unspected token ", 2);
	if (c != '\n')
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline ", 2);
	write(2, "\n", 1);
}
