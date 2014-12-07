#include <jsh.h>
#include <module.h>

int	j_echo(t_jsh *jsh, char **argv)
{
  int	i = 0, cr = 1;

  while (argv[i])
    {
      if (!strncmp(argv[i], "-n", 2))
	cr = 0;
      i++;
    }
  printf("%s%c", argv[i - 1], (cr) ? '\n' : 0);
  return (MODULE_OK);
}
