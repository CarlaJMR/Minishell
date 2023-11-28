/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2023/11/22 16:22:59 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    choose_builtin(t_data *data)
{
	int i;
	i = 0;

	while(data->cmds->comand[i])
	{
		if(!ft_strncmp(data->cmds->comand[i], "env", 4))
			print_env(data->env);
		if(!ft_strncmp(data->cmds->comand[i], "pwd", 4))
			do_pwd(data->env);
		if(!ft_strncmp(data->cmds->comand[i], "echo", 5))
			do_echo(data->cmds);
		if(!ft_strncmp(data->cmds->comand[i], "export", 7))
			do_export(data->env, data->cmds);
		

		i++;     
	}

}

void 	do_export(t_env *env, t_cmd *cmd)
{
	int i;
	t_env	*tmp;
	i = 1;

	if(!cmd->comand[1])

	while(cmd->comand[i])
	{
		
	}

}

void 	export_utils(t_env *env)
{
	
}

void    do_echo(t_cmd *cmd)
{
	int flag;
	int j;
	j = 0;
	flag = 0;

	if(cmd->comand[1] && cmd->comand[1][0] && cmd->comand[1][0] == '-')
	{
		while(cmd->comand[1][++j] && cmd->comand[1][j] == 'n')
			flag = 1;
		if(cmd->comand[1][j] != 'n' && cmd->comand[1][j])
			flag = 0;

	}
	echo_util(cmd, flag);
}

void 	echo_util(t_cmd * cmd, int flag)
{
	int j;
	j = 1; 

	while(cmd->comand && cmd->comand[j])
	{
		if(flag == 1 && cmd->comand[2])
		{
			if (!ft_strncmp(cmd->comand[j], "-n", 2))
				j++;
			ft_putstr_fd(cmd->comand[j], 1);
			if (cmd->comand[j + 1])
				ft_putstr_fd(" ", 1);
		}
		else if (flag == 0)
		{
			ft_putstr_fd(cmd->comand[j], 1);
			if (cmd->comand[j + 1])
				ft_putstr_fd(" ", 1);
			else
				ft_putstr_fd("\n", 1);
		}
		j++;
	}
}


void	print_env(t_env *stack)
{
	t_env	*tmp;

	tmp = stack;
	while (tmp)
	{
		printf("%s=", tmp->name);
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void    do_pwd(t_env *stack)
{
	t_env   *tmp;

	tmp = stack;
	while(tmp)
	{
		if(!ft_strncmp(tmp->name, "PWD", 4))
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
