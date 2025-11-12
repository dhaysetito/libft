/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:17:53 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/01 19:09:00 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *npt)
{
	int	nb;
	int	i;
	int	signal;

	nb = 0;
	i = 0;
	signal = 1;
	while ((npt[i] >= 9 && npt[i] <= 13) || npt[i] == 32)
		i++;
	if (npt[i] == '-')
	{
		signal = -1;
		i++;
	}
	if (npt[i] == '+')
		i++;
	while (npt[i] >= '0' && npt[i] <= '9')
	{
		nb *= 10;
		nb += (npt[i++] - 48);
	}
	return (nb * signal);
}
