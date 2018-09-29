/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 16:12:54 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lil_cpy(char *s1, int *i1, char *s2, int *i2)
{
	while (s1[*i1])
	{
		s2[*i2] = s1[*i1];
		(*i1)++;
		(*i2)++;
	}
}

int		delimiter(char c)
{
	if (c == '-' || c == '+' || c == '/' || c == ' ' || c == '\t' || c == '=' \
			|| c == '|' || c == '$' || c == '\n' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

void	set_line(t_env *env_s, char *newline)
{
	free(env_s->line);
	if (!(env_s->line = (char *)ft_memalloc(sizeof(char) \
					* (ft_strlen(newline) + 1))))
		return ;
	ft_strcpy(env_s->line, newline);
}

void	free_stuff_dollars(char *newline, char *key, char *name)
{
	free(newline);
	free(key);
	free(name);
}

int		rules(t_env *env_s, int count)
{
	if (count == 0 || env_s->line[count - 1] == ' ' \
			|| env_s->line[count - 1] == '\t')
	{
		if (env_s->line[count + 1] == '\0')
			return (1);
		if (env_s->line[count + 1] == '/')
			return (1);
		if (env_s->line[count + 1] == ' ' || env_s->line[count + 1] == '\t')
			return (1);
	}
	return (0);
}
