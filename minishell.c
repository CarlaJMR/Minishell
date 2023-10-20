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

//testar um commit

/*t_com	*cmd_new(void)
{
	t_com	*cmd;

	com = malloc(sizeof(t_com));
	if (!cmd)
		return (NULL);
    cmd->redir[0] = 0;
    cmd->redir[1] = 1;
	cmd->next = NULL;
	return (cmd);
}

void    redirections(char **list, int *j, t_cmd   *cmd)
{
    int	i;

	i = j;
	while ((*list)[j])
	{
		if (((*list)[j] == '<')
            process_infile(list, &j, cmd);
        else if (*list)[j] == '>'))
            process_outfile(list, &j, cmd);
        //ver acerto dos indices (tman);
    }

		else
			(*line)[j++] = (*line)[i++];
	}
}

t_cmd   *parse(char **list)
{
    int i;
    int j;
    t_cmd   *cmd;

    i = 0
    while (list[i])
    {
        cmd = cmd_new();
        j = 0;
        while (j < ft_strlen(list[i]))
        {
            rediretions(list[i], &j, cmd);
            trimm_rediretions();pode ser na mesma;
            list_to_comand();
        }

        i++;
    }
    return (cmd);
}*/

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
    int i = 0;
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
            //trimm_spaces(first_split);
            while (first_split[i])
            {
                printf("%s$\n", first_split[i]);
                i++;
            }
            //cmdlist = parse(first_split);
            //execute(data ou data.cmd);
            //free(first_split);
        }

    }
    //limpar tudo e sair com codigo correto
    return (0);
}
