/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:37:10 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/01 22:42:50 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	join = ft_strdup(s1);
	ft_strlcat(join, s2, sizeof(len_s2));
	return (join);
}
