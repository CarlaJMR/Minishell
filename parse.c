/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/24 13:56:38 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_com	*cmd;

	cmd = malloc(sizeof(t_com));
	if (!cmd)
		return (NULL);
    cmd->redir[0] = 0;
    cmd->redir[1] = 1;
	cmd->next = NULL;
	return (cmd);
}

void	process_infile(char *line, int *j, t_cmd *cm)
{

}

void	process_infile(char *line, int *j, t_cmd *cm)
{

}

void	skip_quotes(char *line, int *i, char c)
{
	(*i)++;
    while (line[*i] && line[*i] != c)
        (*i)++;
    if (line[*i] == c)
            (*i)++;
}

void manage_redirections(char *line, int *j, t_cmd *cm)
{
    while (line[*j])
    {
        if (line[*j] == '"' || line[*j] == '\'' )
            skip_quotes(line, &j, line[*j]);
        else if (line[*j] == '<')
            process_infile(line, j, cm);
        else if (line[*j] == '>')
            process_outfile(line, j, cm);
        else
            (*j)++;
    }
}

t_cmd parse(char **first)
{
	int i;
    int j;
    t_cmd   *cm;

    i = 0;
    while (first[i])
    {
        cm = cmd_new();
        j = 0;
        skip_spaces(first[i], &j);
        manage_redirections(first[i], &j, cm);
		//list_to_comand();
		i++;
	}
    return (cm);
}
