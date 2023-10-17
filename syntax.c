/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/06 15:25:53 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	if (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ')
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
	ft_putchar_fd(c, 2);
	write(2, "\n", 1);
}

int	check_pipe(char *line, int *i)
{
    (*i)++;
	if (line[*i] == '|' || line[*i]  == '\0')
    {
		print_syntax_error('|');
		return (0);
    }
	else
		skip_spaces(line, i);
	if (line[*i] == '|' || line[*i]  == '\0')
    {
		print_syntax_error('|');
		return (0);
    }
	return (1);
}

int	check_redir(char *line, int *i)
{
	char	c;

	if (line[*i] == '>' || line[*i] == '<')
	{
    	c = line[*i];
		(*i)++;
		if (line[*i] == c)
			(*i)++;
		else if (line[*i] != c && (line[*i] == '>' || line[*i] == '>'))
        {
			print_syntax_error(line[*i]);
			return (0);
        }
		skip_spaces(line, i);
		if (line[*i] == '>' || line[*i] == '<')
        {
			print_syntax_error(line[*i]);
			return (0);
        }
    }
	return (1);
}

int	check_quotes(char *line, int *i)
{
	char    c;

	if (line[*i] == '"' || line[*i] == '\'' )
    {
        c = line[*i];
        (*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
        if (line[*i] == '\0')
        {
                print_syntax_error(c);;
                return (0);
        }
		else
			(*i)++;
    }
	return (1);
}

int check_syntax(char *line, int i)
{
	skip_spaces(line, &i);
	if (line [i] == '|')
	{
		print_syntax_error('|');
		return (0);
	}
    while (line [i])
    {
        if (!check_quotes(line, &i))
		{
       		return (0);
		}
		//printf("%c\n", line[i]);
		if (line[i] == '|')
		{
			line[i] = 2;
			if (!check_pipe(line, &i))
				return (0);
		}
		if (!check_redir(line, &i))
			return (0);
		i++;
	}
    return (1);
}

