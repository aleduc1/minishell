/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:09:02 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:33:51 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_list(char **scd_cut, t_lst **start)
{
	t_lst	*node;

	node = create_node(scd_cut);
	add_node(start, node);
}

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
		if (!(one_cut[count] = (char*)ft_memalloc(sizeof(char) \
						* (ft_strlen(env[count]) + 1))))
			return (NULL);
		one_cut[count] = ft_strcpy(one_cut[count], env[count]);
		count++;
	}
	one_cut[count] = 0;
	return (one_cut);
}

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
		scd_cut = ft_strsplit(one_cut[count], '=');
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
