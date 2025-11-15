/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 00:27:24 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/12 01:52:31 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lennbr(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	signal_aux(int n, char *nbr)
{
	int	signal;

	signal = 1;
	if (n < 0)
	{
		nbr[0] = '-';
		signal = -1;
	}
	if (n == 0)
		nbr[0] = '0';
	return (n * signal);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	size_t	len;

	if (n == INT32_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_lennbr(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	n = signal_aux(n, nbr);
	nbr[len] = '\0';
	while (n > 0)
	{
		nbr[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (nbr);
}
