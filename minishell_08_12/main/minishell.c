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

int	e_signal;

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
		printf("%d\n", c->redir[0]);
    	printf("%d\n", c->redir[1]);
        while (temp->comand[size])
		    size++;
        while (i < size)
            printf("%s$\n", temp->comand[i++]);
        printf("next %p\n", c->next);
 		temp = temp->next;
 	}
 }

void init_data(t_data *sh, char **env)
{
	e_signal = 0;
	sh->env = NULL;
    get_env(env, &sh->env);
	sh->env->status = 1;
}

int	handle_input(char *l)
{
	if (!l)
	{
		free(l);
		rl_on_new_line();
		ft_putendl_fd("exit", 1);
		return (0);
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **first_split;
    t_data sh;

    if (ac != 1)
        return (0);
    (void) av;
	
	init_data(&sh, env);
    while (1)
    {
		set_signals();
		line = readline("\e[1;36mminishell$ \e[0m");
        if (!handle_input(line))
			break;
		else if (line[0])
        {
			add_history(line);
            if (check_syntax(line, 0))
            {
                first_split = ft_split(line, 2);
				free(line);
                sh.cmds = parsing(first_split, sh);
                free_split(first_split);
				choose_builtin(&sh);
                //print_cmd_list(sh.cmds);
                free_comand(&sh.cmds);
            }
			else
				free(line);
		}
		else
			free(line);
	}
    free_env(&sh.env);
    //limpar tudo e sair com codigo correto
    return (0);
}
