/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:41:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 15:03:08 by aleduc           ###   ########.fr       */
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

int		dollars(t_env *env_s, t_lst **head)
{
	int		start;
	int		count;
	char	*key;
	char	*name;
	char	*newline;

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

char	*replace_tld(int count, t_env *env_s, t_lst **head)
{
	int		size;
	int		start;
	char	*line;
	char	*home;

	start = 0;
	if (!(home = get_value_of_key(head, "HOME")))
		return (NULL);
	size = (ft_strlen(home) + ft_strlen(env_s->line));
	if (!(line = (char *)ft_memalloc(sizeof(char) * size)))
		return (NULL);
	size = 0;
	while (size < count)
	{
		line[size] = env_s->line[size];
		size++;
	}
	while (home[start])
	{
		line[size] = home[start];
		start++;
		size++;
	}
	count++;
	while (env_s->line[count])
	{
		line[size] = env_s->line[count];
		size++;
		count++;
	}
	free(home);
	return (line);
}

void	tilde(t_env *env_s, t_lst **head)
{
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	while (env_s->line[count])
	{
		if (env_s->line[count] == '~')
		{
			if (rules(env_s, count))
			{
				if (!(line = replace_tld(count, env_s, head)))
				{
					ft_putendl("Error : A var in your ENV is needed");
					return ;
				}
				set_line(env_s, line);
				free(line);
			}
		}
		count++;
	}
}
