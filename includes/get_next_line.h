/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 23:51:00 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 12:06:50 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# define BUFF_SIZE 1

typedef	struct	s_struct
{
	char	*realbuff;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	char	*t;
	int		i;
	int		j;
	int		flag;
	int		k;
	int		ret;
}				t_struct;

int				get_next_line(int const fd, char **line);
#endif
