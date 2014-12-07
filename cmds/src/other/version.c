#include <jsh.h>
#include <module.h>

int	j_version(t_jsh *jsh, char **argv)
{
  int	i = 0;

  printf("Version 0.1 released on December, 7th, 2014\n");
  printf("jSh 0.1, an original project from Joris Bertomeu written by Joris Bertomeu\n");
  return (MODULE_OK);
}
