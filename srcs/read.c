/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 12:20:15 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_lst **head)
{
	if (head)
		return (NULL);
	return (NULL);
}

void	ft_search_bin(t_env *env_s, t_lst **head)
{
/* Search bin in $PATH To fork and exec on it */
	char	*envpath;
	char	**paths;
	int		counts;
/*
	 * Some ideas on how to do it :
	 * Break up every path from $PATH in a doubletab						*
	 * While there is directory												*
	 * Open and read directory pointed to by $PATH							*
	 * If in a dir you found the command the user entered					*
	 * Then invok the binary with fork and exec								*
	 * If not check the next directory from $PATH							*
	 * If you finished all path from $PATH									*
	 * And you didnt found any built_in or binary, display error message	*
*/

	counts = 0;
	envpath = get_path(head);
	paths = ft_strsplit(envpath, ':');
	while (paths[counts])
	{
		if (dir_functs(paths[counts], env_s) == 1)
			break ;
		counts++;
	}
	if (paths[counts])
		return ;
	ft_putstr("minishell: command not found");
	if (env_s->tab[0])
	{
		ft_putstr(": ");
		ft_putendl(env_s->tab[0]);
	}
}

void	read_fct(t_env *env_s, t_lst **head)
{
	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &env_s->line))
		{
			if (env_s->line[0])
			{
				ft_lexer(env_s) == 0 ? ft_parser(env_s, head) : 0;
				env_s->bin == 0 ? ft_search_bin(env_s, head) : 0;
			}
		}
	}
}
