/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 16:27:24 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/23 18:19:44 by aleduc           ###   ########.fr       */
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

/* Set value of OLDPWD being the one of PWD */

void	setoldpwd(t_lst **head)
{
	char	*value;

	value = get_value_of_key(head, "PWD");
	modify_value("OLDPWD", value, head);
	free(value);
}

/* Get the value of the key sent in param and return it in a alloc'd char* */

char	*get_value_of_key(t_lst **head, char *key)
{
	t_lst	*curlist;
	char	*value;

	value = NULL;
	curlist = *head;
	while (curlist)
	{
		if (!(ft_strcmp(curlist->key, key)))
		{
			if (!(value = (char*)ft_memalloc(sizeof(char) * (ft_strlen(curlist->value) + 1))))
				value = NULL;
			else
				value = ft_strcpy(value, curlist->value);
			return (value);
		}
		curlist = curlist->next;
	}
	return (NULL);
}

/* Turn a lst** to char** */

char	**list_to_char(t_lst **head)
{
	int		count;
	int		size;
	char	**tab;
	t_lst	*curlist;

	size = 0;
	curlist = *head;
	count = ft_lstsize(head);
	if (!(tab = ft_memalloc(sizeof(char *) * (count + 1))))
		return (NULL);
	count = 0;
	while (curlist)
	{
		size = ft_strlen(curlist->key) + ft_strlen(curlist->value);
		if (!(tab[count] = ft_memalloc(sizeof(char) * (size + 2))))
			return (NULL);
		ft_fill_str(tab[count], curlist->key, curlist->value);
		curlist = curlist->next;
		count++;
	}
	return (tab);
}
