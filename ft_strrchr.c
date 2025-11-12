/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 00:04:12 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/10/25 00:41:03 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[len]);
	while (len > 0)
	{
		if (s[len - 1] == c)
			return ((char *)&s[len - 1]);
		len--;
	}
	return (NULL);
}
