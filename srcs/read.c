/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/08/26 19:16:41 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_search_bin(t_env *env_s)
{
/* Search bin in $PATH To fork and exec on it */

/*
	 * Some ideas on how to do it :
	 * Break up every path from $PATH in a char **
	 * While there is directory
	 * Open and read directory pointed to by $PATH
	 * If in a dir you found the command the user entered.
	 * Then invok the binary with fork and exec
	 * If not check the next directory from $PATH
	 * If you finished all path from $PATH
	 * And you didnt found any built_in or binary, display error message
*/
	if (env_s)
		ft_putendl("Salut");
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
				env_s->bin == 0 ? ft_search_bin(env_s) : 0;
			}
		}
	}
}
