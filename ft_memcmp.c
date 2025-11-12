/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:49:30 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/01 17:10:16 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*str1;
	const char	*str2;

	i = 0;
	str1 = (const char *)s1;
	str2 = (const char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			break ;
		if (str1[i] == str2[i] && i == n - 1)
			break ;
		i++;
	}
	return (str1[i] - str2[i]);
}
