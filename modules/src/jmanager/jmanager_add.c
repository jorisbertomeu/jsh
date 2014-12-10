#include <jsh.h>
#include <module.h>

int	jmanager_add(t_jsh *jsh, char **argv)
{
  if (argv[2] == NULL)
    {
      printf("jManager Add - Missing parameter package name\n");
      return (MODULE_KO);
    }
  printf("Searching package \"%s\" ...\n", argv[2]);
  printf("\033[33mSorry, package \"%s\" not found\033[0m\n", argv[2]); 
  return (MODULE_OK);
}
