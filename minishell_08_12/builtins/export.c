/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:50:42 by mneves-l          #+#    #+#             */
/*   Updated: 2023/12/04 20:47:26 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_var(char *cmd, t_env *env)
{
	char	*name;
	char	*content;
	int		size;
	int		len;

	if (ft_strchr(cmd, '=') == NULL)
		return ;
	size = g_size(cmd, '=');
	name = ft_substr(cmd, 0, size);
	len = ft_strlen(cmd);
	content = ft_substr(cmd, size + 1, len - size);
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			env->content = content;
		env = env->next;
	}
}

int	check_repeat(char *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, cmd, ft_strlen(tmp->name)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	set_variable(t_env *env, char *cmd)
{
	char	*name;
	char	*content;
	int		size;
	int		len;

	if (ft_strchr(cmd, '=') == NULL)
		ev_lstadd_back(&env, ev_lstnew(ft_strdup(cmd), 0));
	else
	{
		size = g_size(cmd, '=');
		name = ft_substr(cmd, 0, size);
		len = ft_strlen(cmd);
		content = ft_substr(cmd, size + 1, len - size);
		ev_lstadd_back(&env, ev_lstnew(name, content));
	}
}

void	print_export(t_env *env, t_data *data)
{
	t_env	*tmp;

	(void) *data;
	tmp = env;
	if (e_signal == 1)
	{
		e_signal = 0;
		bubble_sort(env);
	}
	while (tmp)
	{
		printf("declare -x: ");
		if (tmp->content)
		{
			printf("%s=", tmp->name);
			printf("\"%s\"\n", tmp->content);
		}
		else
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

void	bubble_sort(t_env *env)
{
	int		size;
	int		i;
	t_env	*tmp;
	t_env	*head;

	i = 0;
	size = ev_lstsize(env);
	head = env;
	while (i < size)
	{
		tmp = head;
		while (tmp && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
				do_swap(tmp);
			tmp = tmp->next;
		}
		i++;
	}
}
