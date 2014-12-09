#include <module.h>
#include <jsh.h>

int alias_list(t_jsh *jsh, char **argv)
{
  int	i = 0;

  while (jsh->alias[i][0])
    {
      printf("%s\t\t%s\n", jsh->alias[i][0], jsh->alias[i][1]);
      i++;
    }
  return (MODULE_OK);
}
