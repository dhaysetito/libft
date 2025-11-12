/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:13:14 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/01 22:08:56 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_out;
	size_t	len_s;
	char	*out;
	size_t	i;

	len_s = ft_strlen((char *)s);
	len_out = len;
	i = 0;
	if (len_s - start < len)
		len_out = len_s - start;
	out = (char *)malloc((len_out + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (i < len_out)
	{
		out[i] = s[start];
		i++;
		start++;
	}
	out[i] = '\0';
	return (out);
}
