#include <jsh.h>
#include <module.h>

int	j_version(t_jsh *jsh, char **argv)
{
  int	i = 0;

  printf("Version %s (%d) released on %s\n", jsh->version.ver_name, jsh->version.ver_num, jsh->version.ver_date);
  printf("jSh %d, an original project from Joris Bertomeu written by Joris Bertomeu\n", jsh->version.ver_num);
  return (MODULE_OK);
}