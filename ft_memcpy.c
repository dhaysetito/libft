/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:02:43 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/10/24 19:58:04 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str_dest;
	unsigned char	*str_src;

	i = 0;
	str_dest = (unsigned char *)dest;
	str_src = (unsigned char *)src;
	if (!str_dest && !str_src)
		return (NULL);
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (str_dest);
}
