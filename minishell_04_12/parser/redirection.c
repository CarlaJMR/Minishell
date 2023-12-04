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

int ft_here_doc(char *limiter)
{
    int     file;
    char	*line;
    
    file = open("heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
		{
			printf("heredoc delimited by eof (wanted '%s')\n", limiter);
			break ;
		}
		if (!ft_strncmp(line, limiter, ft_strlen(line) - 1) && \
			!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(file, line, ft_strlen(line));
		free(line);
	}
	return (file);
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

void	manage_redirections(char **line, int *i, t_cmd *cm)
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
			cm->redir[0] = ft_here_doc(line[(*i) + 1]);
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
	//invalid_fd??
}
