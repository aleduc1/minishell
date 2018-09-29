/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:05:33 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 16:50:43 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(t_env *env_s, char *key, char *name, t_lst **head)
{
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
	size = -1;
	while (env_s->line[++size])
	{
		if (env_s->line[size] == '$')
			if (delimiter(env_s->line[size + 1]) == 0)
				break ;
		newline[size] = env_s->line[size];
	}
	dollars = size;
	lil_cpy(value, &count, newline, &size);
	dollars = dollars + ft_strlen(key);
	lil_cpy(env_s->line, &dollars, newline, &size);
	free(value);
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
	lil_cpy(env_s->line, &count, newline, &size);
	return (newline);
}

int		dollars(t_env *env_s, t_lst **head)
{
	t_norm	n;

	n.newline = NULL;
	n.count = 0;
	n.start = pod_2(env_s);
	if (env_s->line[n.start])
	{
		while (env_s->line[n.start])
		{
			n.start++;
			n.count++;
			if (delimiter(env_s->line[n.start]))
			{
				n.key = ft_strsub(env_s->line, (n.start - n.count), n.count);
				n.name = ft_strsub(n.key, 1, (ft_strlen(n.key) - 1));
				if (lst_check_name(n.name, head))
					pod(n.newline, env_s, replace(env_s, n.key, n.name, head));
				else
					pod(n.newline, env_s, del(env_s, n.key));
				free_stuff_dollars(n.newline, n.key, n.name);
				return (1);
			}
		}
	}
	return (0);
}

void	pod(char *newline, t_env *env_s, char *repl)
{
	newline = repl;
	set_line(env_s, newline);
	ft_strdel(&newline);
}

int		pod_2(t_env *env_s)
{
	int		start;

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
	return (start);
}
