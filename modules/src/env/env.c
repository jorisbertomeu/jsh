#include <jsh.h>
#include <module.h>

int	j_env(t_jsh *jsh, char **argv)
{
  int	i = 0;

  while (jsh->env[i])
    {
      printf("%s\n", jsh->env[i]);
      i++;
    }
  return (MODULE_OK);
}
