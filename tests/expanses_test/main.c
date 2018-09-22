/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/22 16:43:30 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanses.h"
int		main(int ac, char **av, char **env)
{
	char *line;

	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &line))
		{
			if (line[0])
				expanse(line, env);
		}
	}
	return (0);
}
