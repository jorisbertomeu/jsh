#include <jsh.h>

int	search_auto_complete(t_jsh *jsh, char *str, int *i)
{
  if (search_autocomplete_alias(jsh, str, i))
    return(1);
  if (search_autocomplete_cmd(jsh, str, i))
    return(1);
  return (0);
}

int	cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *) p1, *(char * const *) p2);
}

void	free_tab(char **tab, int j)
{
  int	i = 0;

  while (i < j)
      free(tab[i++]);
  free(tab);
}


