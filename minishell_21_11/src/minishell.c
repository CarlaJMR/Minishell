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
		free(str[i++]);
	free(str);
}

void	print_cmd_list(t_cmd *c)
{
	int	size;
	int	i;
	t_cmd *temp;

	temp = c;
 	while (temp)
 	{
 		i = 0;
	    size = 0;
        while (temp->comand[size])
		    size++;
        while (i < size)
            printf("%s$\n", temp->comand[i++]);
        printf("next %p\n", c->next);
 		temp = temp->next;
 	}
 }

void	print(t_env *stack)
{
	t_env	*tmp;

	tmp = stack;
	while (tmp)
	{
		printf("node------------\n");
		printf("nome = %s\n", tmp->name);
		printf("content = %s\n", tmp->content);
		printf("------------------\n");
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **first_split;
    //t_cmd   *cmdlist;
    //t_env	*ev;
    t_data sh;

    if (ac != 1)
        return (0);
    (void) av;
    (void) env;
	
	sh.env = NULL;
    get_env(env, &sh.env);
    //print(sh.env);
    while (1)
    {
        //sinais
        line = readline("\e[1;36mminishell$ \e[0m");
        if (line[0])
        {
            add_history(line);
            if (check_syntax(line, 0))
            {
                first_split = ft_split(line, 2);
                free(line);
                sh.cmds = parsing(first_split, sh.env);
                free_split(first_split);
                //print_cmd_list(sh.cmds);
                //execute(data ou data.cmd);
                free_comand(&sh.cmds);
            }
        }
    }
    //limpar tudo e sair com codigo correto
    return (0);
}
