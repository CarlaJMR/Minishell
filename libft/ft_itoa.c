/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:08:05 by cjoao-me          #+#    #+#             */
/*   Updated: 2022/11/04 15:25:17 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ndig(long int n)
{
	long int	ndig;

	ndig = 1;
	while (n > 9)
	{
		n = n / 10;
		ndig++;
	}
	return (ndig);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			len;
	long int	naux;

	naux = n;
	if (n < 0)
		naux = -naux;
	len = ndig(naux);
	if (n < 0)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		str[i--] = naux % 10 + 48;
		naux = naux / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
