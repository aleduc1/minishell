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

void	main(int ac, char **av)
{
	char *line;

	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &line))
		{
			if (line[0])
				expanse(&line);
		}
		if (line)
			free(line);
	}
}

void	expanse(char **line)
{
	int	start;
	int	count;
/*
	 * when $ is found							*
	 * everything in between $ and end delimiter has to be check
	 * if it is a env variable
	 * replace from $ to (delimiter - 1) with the value of that variable
	 * */

	count = 0;
	start = 0;
	while (*line[start] && (*line[start] != '$'))
		start++;
	if (*line[start])
	{
		while (*line[start])
		{
			if (!(delimiter(*line[start])))
			{
				//ft_strsub(buff, start - count, count);
			}
			start++;
			count++;
		}
	}
}
