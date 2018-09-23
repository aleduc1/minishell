/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/23 16:18:34 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(t_env *env_s, char *key, char *name, t_lst **head)
{
	/*
	 * But = avoir dans newline le line mais en ayant remplace $key par sa value *
	 * Malloc le newline de la bonne taille					*
	 * Cpy tant que on est pas sur le $						*
	 * une fois sur le $ ecrire la value de key				*
	 * une fois la value de la key ecrite cpy jusqua la fin	*
	 * */
	int		dollars;
	int		size;
	int		count;
	char	*value;
	char	*newline;

	count = 0;
	value = get_value_of_key(head, name);
	size = (ft_strlen(env_s->line) - ft_strlen(key) + ft_strlen(value));
	if (!(newline = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	size = 0;
	while (env_s->line[size])
	{
		if (env_s->line[size] == '$')
		{
			if (delimiter(env_s->line[size + 1]) == 0)
				break ;
		}
		newline[size] = env_s->line[size];
		size++;
	}
	dollars = size;
	while (value[count])
	{
		newline[size] = value[count];
		count++;
		size++;
	}
	dollars = dollars + ft_strlen(key);
	while (env_s->line[dollars])
	{
		newline[size] = env_s->line[dollars];
		size++;
		dollars++;
	}
	return (newline);
}

char	*del(t_env *env_s, char *key)
{
	char	*newline;
	int		size;
	int		count;

	size = (ft_strlen(env_s->line) - ft_strlen(key));
	if (!(newline = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	size = 0;
	while (env_s->line[size])
	{
		if (env_s->line[size] == '$')
		{
			if (delimiter(env_s->line[size + 1]) == 0)
				break ;
		}
		newline[size] = env_s->line[size];
		size++;
	}
	count = size;
	count = count + ft_strlen(key);
	while (env_s->line[count])
	{
		newline[size] = env_s->line[count];
		size++;
		count++;
	}
	return (newline);
}

int		delimiter(char c)
{
	if (c == '-' || c == '+' || c == '/' || c == ' ' || c == '\t' || c == '=' || c == '|' || c == '$' || c == '\n' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

void	set_line(t_env *env_s, char *newline)
{
	free(env_s->line);
	if (!(env_s->line = (char *)ft_memalloc(sizeof(char) * (ft_strlen(newline) + 1))))
		return ;
	ft_strcpy(env_s->line, newline);
}

int		dollars(t_env *env_s, t_lst **head)
{
	int		start;
	int		count;
	char	*key;
	char	*name;
	char	*newline;
	/*
	 * when $ is found														*
	 * everything in between $ and end delimiter has to be check			*
	 * if it is an env variable												*
	 * replace from $ to (delimiter - 1) with the value of that variable	*
	 * */

	count = 0;
	start = 0;
	while (env_s->line[start])
	{
		if (env_s->line[start] == '$')
		{
			if (delimiter(env_s->line[start + 1]) == 0)
				break ;
		}
		start++;
	}
	if (env_s->line[start])
	{
		while (env_s->line[start])
		{
			start++;
			count++;
			if (delimiter(env_s->line[start]))
			{
				key = ft_strsub(env_s->line, (start - count), count);
				name = ft_strsub(key, 1, (ft_strlen(key) - 1));
				if (lst_check_name(name, head))
				{
					newline = replace(env_s, key, name, head);
					set_line(env_s, newline);
				}
				else
				{
					newline = del(env_s, key);
					set_line(env_s, newline);
				}
				free(newline);
				free(key);
				free(name);
				return (1);
			}
		}
	}
	return (0);
}
