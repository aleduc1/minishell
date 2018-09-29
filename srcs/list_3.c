/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:52:11 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:37:59 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_lst(t_lst **dst, t_lst **src)
{
	int		loop;
	t_lst	*tmp;
	t_lst	*srcptr;

	loop = 0;
	tmp = NULL;
	srcptr = *src;
	while (srcptr)
	{
		if (loop == 0)
			tmp = create_new_node(srcptr->key, srcptr->value);
		else
			put_in_newlist(srcptr->key, srcptr->value, &tmp);
		loop = 1;
		srcptr = srcptr->next;
	}
	*dst = tmp;
}

t_lst	*create_new_node(char *key, char *value)
{
	t_lst	*node;

	if (!(node = (t_lst *)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (!(node->key = (char *)ft_memalloc(sizeof(char) * (ft_strlen(key) + 1))))
		node->key = NULL;
	else
		node->key = ft_strcpy(node->key, key);
	if (!(node->value = (char *)ft_memalloc(sizeof(char) \
					* (ft_strlen(value) + 1))))
		node->value = NULL;
	else
		node->value = ft_strcpy(node->value, value);
	node->next = NULL;
	return (node);
}

void	put_in_newlist(char *key, char *value, t_lst **start)
{
	t_lst	*node;

	node = create_new_node(key, value);
	add_node(start, node);
}
