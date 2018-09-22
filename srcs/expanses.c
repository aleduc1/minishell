/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/22 17:10:22 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(char **line, char **newline, char *key, char *name, t_lst **head)
{
/*
 * But = avoir dans newline le line mais en ayant remplace $key par sa value
 * Etapes  =
 * Malloc le newline de la bonne taille
 * Cpy tant que on est pas sur le $
 * une fois sur le $ ecrire la value de key
 * une fois la value de la key ecrite cpy jusqua la fin
 * */

	char	*value;

	value = get_value_of_key(head, name);
	ft_putendl(value);
	*newline = ft_memalloc(sizeof(char) * (ft_strlen(*line) - ft_strlen(key) + ft_strlen(value)));
	ft_putnbr(ft_strlen(*newline));
}

char	*to_check(char *str)
{
	char	*name;

	name = ft_strsub(str, 1, (ft_strlen(str) - 1));
	return (name);
}

int		delimiter(char c)
{
	if (c == '-' || c == '+' || c == '/' || c == ' ' || c == '\t' || c == '=' || c == '|' || c == '$' || c == '\n' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

void	expanse(char *line, t_lst **head)
{
	int		start;
	int		count;
	char	*key;
	char	*name;
	char	*newline;
/*
	 * when $ is found												*
	 * everything in between $ and end delimiter has to be check	*
	 * if it is an env variable
	 * replace from $ to (delimiter - 1) with the value of that variable
	 * */

	count = 0;
	start = 0;
	key = NULL;
	name = NULL;
	newline = NULL;
	while (line[start] && (line[start] != '$'))
		start++;
	if (line[start])
	{
		start++;
		count++;
		while (42)
		{
			if (delimiter(line[start]))
			{
				key = ft_strsub(line, (start - count), count);
				ft_putendl(key);
				name = to_check(key);
				ft_putendl(name);
				if (lst_check_name(name, head))
					replace(&line, &newline, key, name, head);
				break ;
			}
			start++;
			count++;
		}
	}
}
