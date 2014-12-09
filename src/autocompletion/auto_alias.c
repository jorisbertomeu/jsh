#include <jsh.h>

int	search_autocomplete_alias(t_jsh *jsh, char *str, int *i)
{
  int	j = 0;

  while (jsh->alias[j][0])
    {
      if (!strncmp(str, jsh->alias[j][0], *i))
	{
	  write(1, &(jsh->alias[j][0])[*i], strlen(&(jsh->alias[j][0])[*i]));
	  *i = strlen(jsh->alias[j][0]);
	  strcpy(str, jsh->alias[j][0]);
	  return(1);
	}
      j++;
    }
  return (0);
}
