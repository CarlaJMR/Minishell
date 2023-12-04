/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:33:05 by mneves-l          #+#    #+#             */
/*   Updated: 2023/11/30 17:33:41 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_util(t_cmd *cmd, int flag)
{
	int	j;

	j = 1;
	while (cmd->comand && cmd->comand[j])
	{
		if (flag == 1 && cmd->comand[2])
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