/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:31:29 by dhde-lim          #+#    #+#             */
/*   Updated: 2025/11/16 23:52:33 by dhde-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_strs(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*aux;
	char	set[2];

	set[0] = c;
	set[1] = '\0';
	aux = ft_strtrim(s, set);
	i = 0;
	len = 1;
	if (aux[0] == '\0' || s == NULL || s[0] == '\0')
	{
		free(aux);
		return (0);
	}
	while (aux[i])
	{
		if (aux[i] == c && aux[i + 1] != c)
			len++;
		i++;
	}
	free(aux);
	return (len);
}

static void	free_all(char **strs, int i)
{
	while (i > 0)
		free(strs[--i]);
	free(strs);
}

static char	**word_alloc(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)malloc((ft_len_strs(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	const char	*str_begin;
	size_t		i;

	strs = word_alloc(s, c);
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			str_begin = s;
			while (*s && *s != c)
				s++;
			strs[i] = ft_substr(str_begin, 0, s - str_begin);
			if (!strs[i])
				return (free_all(strs, i), NULL);
			i++;
		}
	}
	strs[i] = NULL;
	return (strs);
}
