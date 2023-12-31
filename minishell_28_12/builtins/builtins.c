/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2023/12/29 11:25:22 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_builtin(t_data *data)
{
	if (data->cmds->comand[0])
	{
		if (!ft_strncmp(data->cmds->comand[0], "env", 4))
			print_env(&data->env, data->cmds);
		else if (!ft_strncmp(data->cmds->comand[0], "pwd", 4))
			do_pwd(&data->env, data->cmds);
		else if (!ft_strncmp(data->cmds->comand[0], "echo", 5))
			do_echo(data->cmds);
		else if (!ft_strncmp(data->cmds->comand[0], "export", 7))
			do_export(data->env, data->cmds, data);
		else if (!ft_strncmp(data->cmds->comand[0], "unset", 6))
			do_unset(data->cmds, &data->env);
		else if (!ft_strncmp(data->cmds->comand[0], "cd", 3))
			do_cd(data->env, data->cmds);
		else if (!ft_strncmp(data->cmds->comand[0], "exit", 5))
			do_exit(data->cmds);
		else
			do_execve(data);
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

void	print_env(t_env **stack, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if (tmp->content)
		{
			ft_putstr_fd(tmp->name, cmd->fd_out);
			ft_putstr_fd("=", cmd->fd_out);
			ft_putendl_fd(tmp->content, cmd->fd_out);
		}
		tmp = tmp->next;
	}
}

void	do_pwd(t_env **stack, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4))
			ft_putendl_fd(tmp->content, cmd->fd_out);
		tmp = tmp->next;
	}
}

void	do_export(t_env *env, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd->comand[1])
		print_export(env, data);
	else
	{
		while (cmd->comand[i])
		{
			if (ft_isalpha(cmd->comand[i][0]) || cmd->comand[i][0] == '_')
			{
				if (check_repeat(cmd->comand[i], env))
					set_variable(env, cmd->comand[i]);
				else
					check_var(cmd->comand[i], env);
			}
			else
			{
				printf("export: '%c': not a valid identifier\n",
					cmd->comand[i][0]);
				return ;
			}
			i++;
		}
	}
}
