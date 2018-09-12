#include "minishell.h"

void	free_double_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
	{
		free(tab[count]);
		tab[count] = 0;
		count++;
	}
	free(tab);
	tab = 0;
}
