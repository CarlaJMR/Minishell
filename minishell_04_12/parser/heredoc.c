/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/27 18:09:40 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			cm->redir[0] = 0; //ft_here_doc(line[(*i) + 1]);
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

int ft_here_doc(char *limiter)
{
    int     file;
    char	*line;
    
    file = open("heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	line = NULL;
	while (1)
	{
		line = get_next_line(0);
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

void	problem(void)
{
	ft_putendl_fd("\033[31mError: Bad argument!", 2);
	ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile", 2);
	ft_putendl_fd(\
		"./pipex here_doc LIMITER cmd1 cmd2 ... <outfile>\033[0m", 2);
	exit(EXIT_FAILURE);
}

int	open_files(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_RDONLY);
	else if (i == 1)
		file = open(av, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
	{
		perror("Error opening the infile/outfile");
		exit(EXIT_FAILURE);
	}
	return (file);
}

int	child_process(char *av, char **envp, int *pids)
{
	pid_t	child;
	int		pipefd[2];
	int		dupfd;

	if (pipe(pipefd) < 0)
		error();
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
	{
		dupfd = dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[1]), close(pipefd[0]));
		execute_cmd(av, envp, pids);
		close(dupfd);
		close(STDIN_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(STDIN_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
	}
	return (child);
}

void	last_process(char *file, char *arg, char **envp, int *pids)
{
	int	outfile;
	int	dupfd;

	outfile = open_files(file, 1);
	dupfd = dup2(outfile, STDOUT_FILENO);
	execute_cmd(arg, envp, pids);
	close(outfile);
	close(dupfd);
	close(STDIN_FILENO);
	exit(EXIT_FAILURE);
}

void	process(int ac, char **av, char **envp, int i)
{
	int	j;
	int	*pids;

	pids = ft_calloc(sizeof(int), (ac - 2));
	j = 0;
	while (i < ac - 2)
		pids[j++] = child_process(av[i++], envp, pids);
	i = fork();
	if (i < 0)
		error();
	if (!i)
		last_process(av[ac - 1], av[ac - 2], envp, pids);
	else
	{
		j = 0;
		while (j < (ac - 2))
		{
			if (pids[j])
				waitpid(pids[j], NULL, 0);
			j++;
		}
		waitpid(i, NULL, 0);
	}
	close(STDIN_FILENO);
	free(pids);
}

void	process_here_doc(int *pipefd, char *limiter)
{
	char	*line;

	line = NULL;
	close(pipefd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(line) - 1) && \
			!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	child;
	int		pipefd[2];

	if (ac < 6)
		problem();
	if (pipe(pipefd) < 0)
		error();
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
		process_here_doc(pipefd, limiter);
	else
	{
		waitpid(-1, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	i;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
		{
			i = 3;
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			infile = open_files(av[1], 0);
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		process(ac, av, envp, i);
	}
	else
		problem();
}
