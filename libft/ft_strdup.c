/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:16:52 by cjoao-me          #+#    #+#             */
/*   Updated: 2022/10/28 08:36:22 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*arr;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	arr = malloc(sizeof(*arr) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
