#include <jsh.h>
#include <module.h>

int	j_version(t_jsh *jsh, char **argv)
{
  int	i = 0;

  printf("Version echoing !\n");
  while (argv[i])
    {
      printf("<%d> %s\n", i, argv[i]);
      i++;
    }
  return (MODULE_OK);
}
