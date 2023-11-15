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
	cmd->next = 0;
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

/*t_cmd	*ft_lstlast(t_cmd *lst)
{
	while (lst)
	{
		printf("next %p\n", lst->next);
		if (!lst->next)
			lst = lst->next;
	}
	return (lst);
}*/

void	add_comand(t_cmd **lst, t_cmd *new)
{
	t_cmd	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = *lst;
			while (elem)
			{
				if (!elem->next)
					break ;
				printf("next %p\n", elem->next);
				elem = elem->next;
			}
			elem->next = new;
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

/*void	free_comand(t_cmd **lst)
{
	t_cmd	*aux;

	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		free_split((*lst)->comand);
		aux = (*lst)->next;
		free (*lst);
		*lst = aux;
	}
}*/
	
	/*while (lst && *lst)
	{

		free_split((*lst)->comand);
		aux = (*lst)->next;
		if ((*lst)->redir[1] > 0)
			close((*lst)->redir[1]);
		if ((*lst)->redir[0])
			close((*lst)->redir[0]);
		free (*lst);
		*lst = aux;
	}
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		close((*lst)->fd[0]);
		close((*lst)->fd[1]);
		ft_free_matrix(&(*lst)->content);
		free((*lst)->path);
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	g_data.vars->head = NULL;*/

