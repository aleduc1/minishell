/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:35:51 by aleduc            #+#    #+#             */
/*   Updated: 2018/08/25 17:09:48 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_alloc_len(char const *s, char **tab, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i])
	{
		i++;
		if (s[i] == c || s[i] == '\0')
		{
			if (!(tab[j] = (char*)malloc(sizeof(char) * (len + 1))))
				return (NULL);
			j++;
			len = 0;
		}
		while (s[i] == c)
			i++;
		len++;
	}
	return (tab);
}

static	char	**ft_fill_memories(char const *s, char **tab, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		tab[j][len] = s[i];
		i++;
		len++;
		if (s[i] == '\0' || s[i] == c)
		{
			tab[j][len] = '\0';
			j++;
			len = 0;
		}
		while (s[i] == c)
			i++;
	}
	return (tab);
}

static	char	**ft_alloc_words(char const *s, char **tab, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (!(s[i] == c))
		{
			words++;
			while (s[i] && !(s[i] == c))
				i++;
		}
		else
			i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	tab[words] = 0;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = 0;
	if (!(tab = ft_alloc_words(s, tab, c)))
		return (NULL);
	if (!(tab = ft_alloc_len(s, tab, c)))
		return (NULL);
	tab = ft_fill_memories(s, tab, c);
	return (tab);
}
