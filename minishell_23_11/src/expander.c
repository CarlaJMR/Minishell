/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/24 10:54:01 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_var_name(char *str, int *i)
{
    char    *name;
    int len;

    len = 0;
    name = NULL;
    while (str[*i + len + 1])
    {
        if (str[*i + len + 1] == '"' || str[*i + len + 1] == '\'' \
            || str[*i + len + 1] == ' ' || str[*i + len + 1] == '$')
            break;
        len++;
    }
    if (len)
    {
        name = ft_substr(str, *i + 1, len);
        *i = *i +  len + 1;
    }
    return (name);
}

char    *get_var_value(char *str, int *i, t_env *ev)
{
    char    *name;
    char    *value;

    name = get_var_name(str, i);
    value = NULL;
    if (name)
    {
        while (ev->next)
        {
            if (!ft_strcmp(name, ev->name))
            {
                value = ft_strdup(ev->content);
                free(name);
                break;
            }
            ev = ev->next;
        }
    }
    return (value);
}

void    expand_loop(char *str, char *final, int *j, t_env *ev)
{
    int i;
    int count_double;
    char    *var;

    i = 0;
    count_double = 0;
    var = NULL;
    while (str[i])
    {
        if (str[i] == '"')
                count_double++;
        if (str[i] == '\'' && !(count_double % 2))
            copy_quotes(str, &i, final, j);
        if (str[i] != '$' || ((str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))))
             final[(*j)++] = str[i++];
        else //if (str[i + 1] != '?')
        {
            var = get_var_value(str, &i, ev);
            copy_var_value(final, j, var);
        }
        /*else
            //aqui falta expandir $? para o exit status*/
    }
}

char    *expander(char *str, t_env *ev)
{
    char    *final;
    int j;

    final = malloc(2048);
    if (!final)
        return (NULL);
    j = 0;
    expand_loop(str, final, &j, ev);
    final[j] = 0;
    delete_quotes(final);
    return (final);
}


/*char    *expander(char *str, t_env *ev)
{
    int i;
    int j;
    int count_double;
    char    *final;
    char    *var;

    i = 0;
    j = 0;
    count_double = 0;
    var = NULL;
    final = malloc(2048);
    if (!final)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '"')
                count_double++;
        if (str[i] == '\'' && !(count_double % 2))
            copy_quotes(str, &i, final, &j);
        else if (str[i] != '$' || ((str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))))
             final[j++] = str[i++];
        else
        {
            var = get_var_value(str, &i, ev);
            copy_var_value(final, &j, var);
        }
    }
    final[j] = 0;
    delete_quotes(final);
    return (final);
}*/

void    expand_comands(t_cmd **list, t_env *ev)
{
    t_cmd *aux;
    int i;

    aux = *list;
	while (*list && aux)
	{
		i = 0;
        while (aux->comand[i])
        {
            aux->comand[i] = expander(aux->comand[i], ev);
            i++;
        }
		aux = aux->next;
	}
}
