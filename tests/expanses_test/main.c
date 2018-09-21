/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/18 07:15:58 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanses.h"

int	delimiter(char c)
{
	if (c == '-' || c == '+' || c == '/' || c == ' ' || c == '\t' || c == '=' || c == '|' || c == '$' || c == '\n' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

void	expanse(char *line)
{
	int	start;
	int	count;
	char	*key;
/*
	 * when $ is found							*
	 * everything in between $ and end delimiter has to be check
	 * if it is a env variable
	 * replace from $ to (delimiter - 1) with the value of that variable
	 * */

	count = 0;
	start = 0;
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
				break ;
			}
			start++;
			count++;
		}
	}
}

void	main(int ac, char **av)
{
	char *line;

	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &line))
		{
			if (line[0])
				expanse(line);
		}
	}
}
