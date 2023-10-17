/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:08:05 by cjoao-me          #+#    #+#             */
/*   Updated: 2022/11/25 10:06:55 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numbwords(char const *s, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (s[0] == c && c != 0)
	{
		while (s[++i])
		{
			if (s[i] != c && s[i -1] == c)
				count++;
		}
	}
	else if (s[0] != 0)
	{
		while (s[++i])
		{
			if (s[i] == c && s[i -1] != c)
				count++;
		}
		if (s[i - 1] != c)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	**arr;

	arr = malloc(sizeof(char *) * (numbwords(s, c) + 1));
	if (!arr)
		return (0);
	end = 0;
	i = 0;
	while (i < numbwords(s, c))
	{
		start = end;
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		arr[i] = ft_substr(s, start, end - start);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
