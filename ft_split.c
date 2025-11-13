/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:31:29 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/12 01:53:02 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_strs(size_t len_strs, size_t len_str)
{
	char	**strs;
	size_t	i;

	i = 0;
	strs = (char **)malloc((len_strs + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (len_strs == 0)
		strs[i++] = NULL;
	while (i <= len_strs)
	{
		strs[i] = (char *)malloc((len_str + 1) * sizeof(char));
		if (!strs[i])
		{
			while (i != 0)
				free(strs[i--]);
			free(strs[0]);
			return (NULL);
		}
		i++;
	}
	return (strs);
}

static size_t	ft_len_strs(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*aux;

	aux = ft_strtrim(s, &c);
	i = 0;
	len = 1;
	if (aux[0] == '\0' || s == NULL || s[0] == '\0')
		return (0);
	while (aux[i])
	{
		if (aux[i] == c && aux[i + 1] != c)
			len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**strs;

	if (!s || c)
		return (NULL);
	len = ft_len_strs(s, c);
	strs = malloc_strs(len, ft_strlen(s));
	i = 0;
	j = 0;
	while (*s && len != 0)
	{
		if (*s == c && j != 0)
		{
			strs[i++][j] = '\0';
			j = 0;
		}
		else if (*s != c)
			strs[i][j++] = *s;
		if (i + 1 == len)
			strs[i + 1] = NULL;
		s++;
	}
	return (strs);
}
