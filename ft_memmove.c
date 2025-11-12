/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:02:43 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/10/24 19:58:42 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*str_dest;
	unsigned char	*str_src;

	str_dest = (unsigned char *)dest;
	str_src = (unsigned char *)src;
	if (!str_dest && !str_src)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			str_dest[n - 1] = str_src[n - 1];
			n--;
		}
	}
	return (str_dest);
}
