/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:12:25 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/24 10:53:27 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdarg.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**comand;
	int				redir[2];
}	t_cmd;

int		check_syntax(char *line, int i);
void	print_syntax_error(char c);
void	skip_spaces(char *s, int *i);
int		ft_is_space(char c);

#endif
