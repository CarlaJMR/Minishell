/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:12:25 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/11/22 16:04:29 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			**comand;
	int				redir[2];
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_cmd			*cmds;
	t_env			*env;
	int				exit_status;
}					t_data;

//main - minishell.c
void				free_split(char **str);
void				print_cmd_list(t_cmd *c);

//parser - syntax.c
int					check_syntax(char *line, int i);
int					check_quotes(char *line, int *i);
int					check_redir(char *line, int *i);
int					check_pipe(char *line, int *i);

//parser - syntax_utils.c
int					ft_is_space(char c);
void				skip_spaces(char *s, int *i);
void				print_syntax_error(char c);
int					matrixlen(char **str);
//int					ft_strcmp(char *s1, char *s2);

//parser - redirections.c
void				manage_redirections(char **line, int *i, t_cmd *cm);
int					redir_type(char *str);

//parser - quote_utils.
void				skip_quotes(char *line, int *i, char c);
void				delete_char(char *line, int i);
void				delete_quotes(char *line);
void				copy_quotes(char *line, int *i, char *newline, int *j);

//parser - parse.c
t_cmd				*parsing(char **first, t_data sh);
void				set_comand_list(char **line, t_cmd *cm, t_data sh);
char				*prepare_2nd_split(char *line);
void				replace_spaces(char *line);
void    			treat_great_less(char *line, int *i, char *newline, int *j);

//parser - command_list_utils.c
t_cmd				*new_comand(void);
t_cmd				*last_comand(t_cmd *c);
void				add_comand(t_cmd **lst, t_cmd *new);
void				free_comand(t_cmd **lst);

//parser - expander.c
void				expand_comands(t_cmd **list, t_data sh);
char				*expander(char *str, t_data sh);
void				expand_loop(char *str, char *final, int *j, t_data sh);
char				*get_var_value(char *str, int *i, t_data sh);
char				*get_var_name(char *str, int *i);

//parser - expander_utils.c
void				copy_var_value(char *s1, int *j, char *s2);

//utils - env.c
void				get_env(char **env, t_env **ev);
int					g_size(char *s, int a);
t_env				*ev_lstnew(char *name, char *content);
void				ev_lstadd_back(t_env **lst, t_env *new);

//utils - get_next_line.c
char				*get_next_line(int fd);

//builtins - builtins.c
void				choose_builtin(t_data *data);
void				print_env(t_env *stack);
void				do_pwd(t_env *stack);
void    			do_echo(t_cmd *cmd);
void 				echo_util(t_cmd * cmd, int flag);
void 				do_export(t_env *env, t_cmd *cmd);

#endif
