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

int	matrixlen(char **str)
{
	int	size;

	size = 0;
	while (str && str[size])
		size++;
	return (size);
}

void    replace_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '"' || line[i] == '\'' )
            skip_quotes(line, &i, line[i]);
        if (ft_is_space(line[i]))
            line[i] = 2;
        if (line[i])
            i++;
    }
}

char    *prepare_2nd_split(char *line)
{
    int i;
    int j;
    char    *newline;

    i = 0;
    j = 0;
    newline = malloc(ft_strlen(line) * 4);
    if (!newline)
        return (NULL);
    while (line[i])
    {
        copy_quotes(line, &i, newline, &j);
        if (line[i] && (line[i] == '<' || line[i] == '>'))
        {
            while (line[i] == '<' || line[i] == '>')
                newline[j++] = line[i++];
            if (!ft_is_space(line[i]))
                newline[j++] = 32;
        }
        if (line[i])
            newline[j++] = line[i++];
    }
    newline[j] = '\0';
    replace_spaces(newline);
    return (newline);
}

void    set_comand_list(char    **line, t_cmd   *cm, t_env *ev)
{
    int i;
    int j;
    (void) ev;

    cm->comand = malloc(sizeof(char *) * (matrixlen(line) + 1));
    if (!cm->comand)
        return ;
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i][0] == '<' || line[i][0] == '>')
        {
            //expander(line[i + 1], ev);
            delete_quotes(line[i + 1]);
            manage_redirections(line, &i, cm);
        }
        else
        {
             cm->comand[j] = ft_strdup(line[i]);
             j++;
        }
        i++;
    }
    cm->comand[j] = 0;
    /*printf("%d\n", cm->redir[0]);
    printf("%d\n", cm->redir[1]);
    printf("next %p\n", cm->next);
	i = 0;
	j = 0;
	while (cm->comand[j])
		j++;
    while (i < j)
        printf("%s$\n", cm->comand[i++]);
    printf("quebra\n");*/
}

t_cmd    *parsing(char **first, t_env *ev)
{
	int i;
    char    **second_split;
    t_cmd   **cm_list;
    t_cmd   *cm;

    i = 0;
    cm_list = malloc(sizeof(t_cmd *));
    if (!cm_list)
        return (NULL);
    *cm_list = NULL;
    while (first[i] && first[i][0])
    {
        cm = new_comand();
        second_split = ft_split(prepare_2nd_split(first[i]), 2);
        set_comand_list(second_split, cm, ev);
        add_comand(cm_list, cm);
        free_split(second_split);
		i++;
	}
    cm = *cm_list;
    free(cm_list);
    return (cm);
}
