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
# include <fcntl.h>
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
# include "../libft/libft.h"

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			**comand;
	int				redir[2];
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_cmd		*cmds;
	t_env		*env;
}					t_data;

int		check_syntax(char *line, int i);
void	print_syntax_error(char c);
void	skip_spaces(char *s, int *i);
int		ft_is_space(char c);
t_cmd	*parsing(char **first, t_env *ev);
void	free_split(char **str);
void	manage_redirections(char **line, int *i, t_cmd *cm);
void	copy_quotes(char *line, int *i, char *newline, int *j);
void	delete_quotes(char *line);
void	skip_quotes(char *line, int *i, char c);
t_cmd	*new_comand(void);
void	add_comand(t_cmd **lst, t_cmd *new);
int		count_quotes(char *line);
void	free_comand(t_cmd **lst);
void	print_cmd_list(t_cmd *c);
char    *expander(char *str, t_env *ev);

//env.c
void				get_env(char **env, t_env **ev);
int					g_size(char *s, int a);
t_env				*ev_lstnew(char *name, char *content);
void				ev_lstadd_back(t_env **lst, t_env *new);

#endif
