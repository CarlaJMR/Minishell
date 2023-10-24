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

void	free_split(char **str)
{
	int	size;
	int	i;

	i = 0;
	size = 0;

	while (str[size])
		size++;
    while (i < size)
        printf("%s$\n", str[i++]);
    i = 0;
	while (i < size)
		free(str[i++]);
	free(str);
}

void    trimm_spaces(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        arr[i]=ft_strtrim(arr[i], " \t\n\v\f\r");
        i++;
    }
}

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **first_split;
    //int i;
    //t_cmd   *cmdlist;

    //t_shell data;

    if (ac != 1)
        return (0);
    (void) av;
    (void) env;
    //iniciar env
    while (1)
    {
        //sinais
        line = readline("\e[1;36mminishell$ \e[0m");
        if (line[0])
            add_history(line);
        if (check_syntax(line, 0))
        {
            //printf("%s\n", line);
            first_split = ft_split(line, 2);
            free(line);
            //cmdlist = parse(first_split);
            //execute(data ou data.cmd);
            free_split(first_split);
        }

    }
    //limpar tudo e sair com codigo correto
    return (0);
}
