/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/23 23:04:00 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		correct_path(t_env *env_s)
{
	if (access(env_s->tab[0], X_OK) == 0)
		return (1);
	return (0);
}

void	handle_path_bin(t_env *env_s)
{
	int		count;
	char	*line;

	count = ft_strlen(env_s->tab[0]);
	line = NULL;
	if (ft_strchr(env_s->tab[0], '/'))
	{
		while (count != -1)
		{
			if (env_s->tab[0][count] == '/')
			{
				count++;
				break ;
			}
			count--;
		}
		line = ft_strsub(env_s->tab[0], count, (ft_strlen(env_s->tab[0]) - count + 1));
	}
	else
		line = ft_strdup(env_s->tab[0]);
	free(env_s->tab[0]);
	env_s->tab[0] = ft_strdup(line);
	free(line);
}

/*	 Search bin in $PATH To fork and exec on it	*/

void	ft_search_bin(t_env *env_s, t_lst **head)
{
	char	*envpath;
	char	cwd[4096];
	char	**paths;
	int		counts;
	int		code;

	paths = NULL;
	code = 0;
	counts = 0;
	if (lst_check_name("PATH", head))
	{
		envpath = get_value_of_key(head, "PATH");
		paths = ft_strsplit(envpath, ':');
		free(envpath);
		if (correct_path(env_s))
			handle_path_bin(env_s);
		while (paths[counts])
		{
			if (dir_functs(paths[counts], env_s) == 1)
				break ;
			counts++;
		}
		if (paths[counts])
			code = ft_fork_exec(paths[counts], env_s, head);
		else
		{
			if (dir_functs(getcwd(cwd, 4096), env_s) == 1)
				code = ft_fork_exec(cwd, env_s, head);
		}
		free_double_tab(paths);
	}
	if (code == 0)
	{
		ft_putstr("minishell: command not found");
		if (env_s->tab[0])
		{
			ft_putstr(": ");
			ft_putendl(env_s->tab[0]);
		}
	}
}

void	read_fct(t_env *env_s, t_lst **head)
{
	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &env_s->line))
		{
			if (env_s->line[0])
			{
				while (dollars(env_s, head))
					;
				ft_lexer(env_s) == 0 ? ft_parser(env_s, head) : 0;
				if (env_s->bin == 0)
				{
					if ((env_s->tab[0]))
						ft_search_bin(env_s, head);
				}
				if (env_s->tab)
					free_double_tab(env_s->tab);
			}
		}
		if (env_s->line)
			free(env_s->line);
	}
}
