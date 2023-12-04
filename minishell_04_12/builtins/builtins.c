/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2023/11/30 17:34:12 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_builtin(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds->comand[i])
	{
		if (!ft_strncmp(data->cmds->comand[i], "env", 4))
			print_env(data->env);
		if (!ft_strncmp(data->cmds->comand[i], "pwd", 4))
			do_pwd(data->env);
		if (!ft_strncmp(data->cmds->comand[i], "echo", 5))
			do_echo(data->cmds);
		if (!ft_strncmp(data->cmds->comand[i], "export", 7))
			do_export(data->env, data->cmds);
		i++;
	}
}

void	do_echo(t_cmd *cmd)
{
	int	flag;
	int	j;

	j = 0;
	flag = 0;
	if (cmd->comand[1] && cmd->comand[1][0] && cmd->comand[1][0] == '-')
	{
		while (cmd->comand[1][++j] && cmd->comand[1][j] == 'n')
			flag = 1;
		if (cmd->comand[1][j] != 'n' && cmd->comand[1][j])
			flag = 0;
	}
	echo_util(cmd, flag);
}



void	print_env(t_env *stack)
{
	t_env	*tmp;

	tmp = stack;
	while (tmp)
	{
		if(tmp->content)
		{
			printf("%s=", tmp->name);
			printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}

void	do_pwd(t_env *stack)
{
	t_env	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4))
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
