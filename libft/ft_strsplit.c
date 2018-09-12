/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:29 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 09:16:34 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_index_mot(char *str, int mot, char separateur)
{
	int	i;
	int	cntword;

	i = 0;
	cntword = 0;
	while (str[i])
	{
		while (str[i] == separateur)
			i++;
		if (cntword == mot)
			return (i);
		while (str[i] != separateur && str[i])
			i++;
		cntword++;
	}
	return (0);
}

static int		ft_nb_mots(char *str, char separateur)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (str[i])
	{
		if (str[i] == separateur)
			i++;
		else
		{
			while (str[i] != separateur && str[i])
				i++;
			nbword++;
		}
	}
	return (nbword);
}

static int		ft_nb_ltr(char *str, int mot, char separateur)
{
	int	index;
	int	nbletter;

	index = ft_index_mot(str, mot, separateur);
	nbletter = 0;
	while (str[index] != separateur && str[index])
	{
		nbletter++;
		index++;
	}
	return (nbletter);
}

static void		ft_remplissage(char **tab_rt, char *str, int i, char c)
{
	int	j;
	int	k;

	j = 0;
	k = ft_index_mot(str, i, c);
	while (str[k] != c && str[k])
	{
		tab_rt[i][j] = str[k];
		k++;
		j++;
	}
	tab_rt[i][j] = '\0';
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	char		**tab_rt;
	char		*str;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	i = 0;
	if (!(tab_rt = (char**)malloc(sizeof(char*) * (ft_nb_mots(str, c) + 1))))
		return (NULL);
	while (i < ft_nb_mots(str, c))
	{
		tab_rt[i] = (char*)malloc(sizeof(char) * (ft_nb_ltr(str, i, c) + 1));
		if (tab_rt[i] == NULL)
			return (NULL);
		ft_remplissage(tab_rt, str, i, c);
		i++;
	}
	tab_rt[i] = NULL;
	return (tab_rt);
}
