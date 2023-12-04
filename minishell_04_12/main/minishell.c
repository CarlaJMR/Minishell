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

void    signal_handler(int sig)
{
    if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    set_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **first_split;
    t_data sh;

    if (ac != 1)
        return (0);
    (void) av;
	
	sh.exit_status = 0;
	sh.env = NULL;
    get_env(env, &sh.env);
	sh.env->status = 1;
	set_signals();
    while (1)
    {
        
		line = readline("\e[1;36mminishell$ \e[0m");
		if (!line && printf("exit\n"))
			break;
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
	}
    free_env(&sh.env);
    //limpar tudo e sair com codigo correto
    return (0);
}
