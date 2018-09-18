/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 14:52:38 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/18 02:13:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction pour create node */

t_lst	*create_node(char **scd_cut)
{
	t_lst	*node;

	if (!(node = (t_lst *)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (!(node->key = (char *)ft_memalloc(sizeof(char) * (ft_strlen(scd_cut[0]) + 1))))
		node->key = NULL;
	else
		node->key = ft_strcpy(node->key, scd_cut[0]);
//	printf("scd_cut[0] = |%s|\n", scd_cut[0]);
//	printf("scd_cut[1] = |%s|\n", scd_cut[1]);
	if (!(node->value = (char *)ft_memalloc(sizeof(char) * (ft_strlen(scd_cut[1]) + 1))))
		node->value = NULL;
	else
		node->value = ft_strcpy(node->value, scd_cut[1]);
	node->next = NULL;
	return (node);
}

/* Fonction pour ajouter une node */

void	add_node(t_lst **head, t_lst *node)
{
	t_lst	*curlist;

	curlist = *head;
	while (curlist->next)
		curlist = curlist->next;
	curlist->next = node;
}

/* Print list */

void	ft_print_env(t_lst **head)
{
	t_lst	*curlist;

	curlist = *head;
	while (curlist)
	{
		ft_putstr(curlist->key);
		ft_putstr("=");
		ft_putendl(curlist->value);
		curlist = curlist->next;
	}
}

/* Check if first node of env need to be del */

void	check_first_node(char *key, t_lst **head)
{
	t_lst	*curlist;

	curlist = *head;
	if (curlist)
	{
		if (!(ft_strcmp(curlist->key, key)))
		{
			ft_strdel(&(curlist->key));
			ft_strdel(&(curlist->value));
			*head = curlist->next;
			curlist->next = NULL;
			free(curlist);
		}
	}
}

/* Del one node of the env linked list */

void	del_a_node(char *key, t_lst **head)
{
	t_lst	*curlist;
	t_lst	*ptrlist;

	curlist = *head;
	ptrlist = curlist->next;
	check_first_node(key, head);
	while (curlist)
	{
		if (ptrlist)
		{
			if (!(ft_strcmp(ptrlist->key, key)))
			{
				ft_strdel(&(ptrlist->key));
				ft_strdel(&(ptrlist->value));
				curlist->next = ptrlist->next;
				ptrlist->next = NULL;
				free(ptrlist);
				return ;
			}
		}
		curlist = curlist->next;
		if (curlist)
			ptrlist = curlist->next;
	}
}
