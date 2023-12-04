/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/31 11:24:51 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_comand(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir[0] = 0;
	cmd->redir[1] = 1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*last_comand(t_cmd *c)
{
	if (!c)
		return (0);
	while (c->next)
		c = c->next;
	return (c);
}

void	add_comand(t_cmd **lst, t_cmd *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = last_comand(*lst);
			last_comand(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

void	free_comand(t_cmd **lst)
{
	t_cmd	*aux;

	while (lst && *lst)
	{
		aux = (*lst)->next;
		//close((*lst)->redir[0]);
		//close((*lst)->redir[1]);
		free_split((*lst)->comand);
		free (*lst);
		*lst = aux;
	}
}

void	free_one_comand(t_cmd *cm)
{
	free_split(cm->comand);
	cm->next = NULL;
	cm->prev = NULL;
}