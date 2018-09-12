/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:27:24 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 17:51:05 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return one if a node with name exist in the list */

int		lst_check_name(char *name, t_lst **head)
{
	t_lst	*curlist;

	curlist = *head;
	while (curlist)
	{
		if (!(ft_strcmp(name, curlist->key)))
			return (1);
		curlist = curlist->next;
	}
	return (0);
}

/* Once the right key is found, replace the current value with the one we want */

void	modify_value(char *key, char *value, t_lst **head)
{
	t_lst	*curlist;

	curlist = *head;
	while (curlist)
	{
		if (!(ft_strcmp(curlist->key, key)))
		{
			free(curlist->value);
			if (!(curlist->value = (char *)ft_memalloc(sizeof(char) * (ft_strlen(value) + 1))))
				curlist->value = 0;
			else
				curlist->value = ft_strcpy(curlist->value, value);
			return ;
		}
		curlist = curlist->next;
	}
}

void	setoldpwd(t_lst **head)
{
	if (head)
		return ;
	return ;
}

void	setpwd(char *cwd, t_lst **head)
{
	if (cwd && head)
		return ;
	return ;
}

char	*get_value_of_key(t_lst **head, char *key)
{
	if (head && key)
		return (NULL);
	return (NULL);
}
