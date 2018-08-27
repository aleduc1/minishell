/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:12:39 by aleduc            #+#    #+#             */
/*   Updated: 2018/07/26 12:20:44 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	set_start(t_struct **st)
{
	(*st)->j = (*st)->i;
	while ((*st)->realbuff[(*st)->i] != '\0')
		(*st)->i++;
	(*st)->k = (*st)->i - (*st)->j;
	(*st)->t = ft_strsub((*st)->realbuff, (*st)->j + 1, (*st)->k);
	free((*st)->realbuff);
	(*st)->realbuff = ft_strdup((*st)->t);
	free((*st)->t);
}

static	int		fill_line(t_struct **stock, char **line)
{
	(*stock)->i = 0;
	while ((*stock)->realbuff[(*stock)->i] != '\n'
			&& (*stock)->realbuff[(*stock)->i] != '\0')
		(*stock)->i++;
	(*line) = ft_strsub((*stock)->realbuff, 0, (*stock)->i);
	if ((*stock)->i == 0 && (*stock)->realbuff[(*stock)->i] != '\n')
		return (0);
	return (1);
}

static	int		check(int fd, t_struct **stock, char **line)
{
	if (!line)
		return (-1);
	if (fd < 0)
		return (-1);
	if (stock && !*stock)
		*stock = ft_memalloc(sizeof(t_struct));
	if (!((*stock)->realbuff))
		if (!((*stock)->realbuff = ft_memalloc(0)))
			return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_struct	*st = NULL;

	if (check(fd, &st, line) == -1)
		return (-1);
	while ((st->ret = read(fd, st->buff, BUFF_SIZE)))
	{
		if (st->ret == -1)
			return (-1);
		st->buff[st->ret] = '\0';
		st->tmp = ft_strjoin(st->realbuff, st->buff);
		free(st->realbuff);
		st->realbuff = st->tmp;
		if (ft_strrchr(st->realbuff, '\n'))
			break ;
	}
	if (fill_line(&st, line) == 1)
	{
		set_start(&st);
		return (1);
	}
	else
		return (0);
}
