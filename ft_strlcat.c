/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:03:14 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/01 18:48:40 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len2;

	len = ft_strlen(dst);
	len2 = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len2);
	if (size <= len)
		return (size + len2);
	while (src[i] != '\0' && i < size - len - 1)
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + len2);
}
