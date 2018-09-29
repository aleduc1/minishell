/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:11:38 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 16:12:39 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	lil_cpy(home, &start, line, &size);
	count++;
	lil_cpy(env_s->line, &count, line, &size);
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
