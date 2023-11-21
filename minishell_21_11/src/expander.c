/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
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
            while (str[i + len + 1])
            {
                if (str[i + len + 1] == '"')
                    count_double++;
                if (str[i + len + 1] !=' ' && count_double % 2)
                    break;
                len++;
            }
}
char    *expander(char *str, t_env *ev)
{
    int i;
    int j;
    int count_double;
    char    *final;
    char    *var;

    i = 0;
    j = 0;
    count_double = 0;
    final = malloc(1024);
    if (!final)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '"')
                count_double++;
        if (str[i] == '\'' && !(count_double % 2))
            copy_quotes(str, &i, final, &j);
        else if (str[i] != '$')
             final[j++] = str[i++];
        else
        {
            var = get_var_name(str, &i, );
        }
        /*{
            len = 0;
            while (str[i + len + 1])
            {
                if (str[i + len + 1] == '"')
                    count_double++;
                if (str[i + len + 1] !=' ' && count_double % 2)
                    break;
                len++;
            }
            if (len)
            {
                get_var_value(str, i, k, final);
                i = i + len + 1;
            }
        }*/
    }
    delete_quotes(final);
    return (final);
}
