/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/27 18:09:40 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *expander_heredoc(char *str, t_data sh)
{
    char    *final;
	char    *var;
    int 	j;
	int		i;

    var = NULL;
	final = malloc(2048);
    if (!final)
        return (NULL);
    j = 0;
	i = 0;
    while (str[i])
    {
        if (str[i] != '$' || ((str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '"' || str[i + 1] == '\''))))
             final[j++] = str[i++];
        else
        {
            var = get_var_value(str, &i, sh);
            copy_var_value(final, &j, var);
        }
    }
    final[j] = 0;
    free(str);
    return (final);
}

void	ft_hd_child(char *limiter, int fd, t_data sh)
{
	char *line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			printf("warning: here-doc delimited by ");
			printf("end-of-file (wanted '%s')\n", limiter);
			break ;
		}
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0) && \
			(ft_strlen(line) - 1 == ft_strlen(limiter)))
			break ;
		line = expander_heredoc(line, sh);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	exit(0);
}

int	ft_here_doc(char *limiter, t_data sh)
{
	pid_t	pid;
	int		file;
	int		status;

	status = 0;
	file = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		set_exit_code(126, 1);
		return (-1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_here_doc);
	pid = fork();
	if (pid < 0)
	{
		set_exit_code(1, 1);
		return (-1);
	}
	if (pid == 0)
		ft_hd_child(limiter, file, sh);
	signal(SIGINT, SIG_IGN);
	waitpid(0, &status, 0);
	set_exit_code(0, 0);
	return (open("heredoc", R_OK));
}

int	redir_type(char *str)
{
	if (str[0] == '>' && !str[1])
		return (1);
	else if (str[0] == '>')
		return (2);
	else if (str[0] == '<' && !str[1])
		return (3);
	else
		return (4);
}

void	manage_redirections(char **line, int *i, t_cmd *cm, t_data sh)
{
	int	option;

	option = redir_type(line[*i]);
	if (cm->redir[0] != -1)
	{
		if (cm->redir[0] > 2 && (option == 3 || option == 4))
			close(cm->redir[0]);
		if (option == 3)
			cm->redir[0] = open(line[(*i) + 1], O_RDONLY, 0644);
		else if (option == 4)
			cm->redir[0] = ft_here_doc(line[(*i) + 1], sh);
	}
	if (cm->redir[1] != -1)
	{
		if (cm->redir[1] > 2 && (option == 1 || option == 2))
			close(cm->redir[1]);
		if (option == 2)
			cm->redir[1] = open(line[(*i) + 1], \
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (option == 1)
			cm->redir[1] = open(line[(*i) + 1], \
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	(*i)++;
}
