/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:09:02 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/25 20:26:15 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ajouter le double tableau dans la liste */

void	put_in_list(char **scd_cut, t_lst **start)
{
	t_lst	*node;

	node = create_node(scd_cut);
/*	ft_putendl(node->key);
	ft_putendl(node->value);
	ft_putendl("");*/
	add_node(start, node);
}

/* Decouper chaque ligne de l'env dans un double tableau malloc */

char	**ft_first_cut(char **env)
{
	char	**one_cut;
	int		count;

	count = 0;
	while (env[count])
		count++;
	if (!(one_cut = (char **)ft_memalloc(sizeof(char *) * (count + 1))))
		return (NULL);
	count = 0;
	while (env[count])
	{
		if (!(one_cut[count] = (char*)ft_memalloc(sizeof(char) * (ft_strlen(env[count]) + 1))))
			return (NULL);
		one_cut[count] = ft_strcpy(one_cut[count], env[count]);
		count++;
	}
	one_cut[count] = 0;
	return (one_cut);
}

/* Copier l'environnement system pour mettre dans une liste chainee */

void	env_cpy(char **environ, t_lst **env)
{
	int		count;
	char	**one_cut;
	char	**scd_cut;
	t_lst	*tmp;

	count = 0;
	one_cut = ft_first_cut(environ);
	while (one_cut[count])
	{
//		printf("|%s|\n", one_cut[count]);
		scd_cut = ft_strsplit(one_cut[count], '=');
//		printf("scd_cut[0] |%s|\n", scd_cut[0]);
		if (count == 0)
			tmp = create_node(scd_cut);
		else
			put_in_list(scd_cut, &tmp);
		free_double_tab(scd_cut);
		count++;
	}
	free_double_tab(one_cut);
	*env = tmp;
}
