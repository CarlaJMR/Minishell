#include "minishell.h"

/*tratar redirecoes
separar comando
expansao das aspas*/

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

/*void    redirections(char **list, int *j, t_cmd   *cmd)
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
        if (line[*j] == '<')
            process_infile();
        else if (line[*j] == '>')
            process_outfile();
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
		i++;
	}
    return (cm);
    
}

