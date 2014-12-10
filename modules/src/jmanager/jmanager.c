#include <jsh.h>
#include <module.h>

int	j_jmanager(t_jsh *jsh, char **argv)
{
  if (argv[1] != NULL)
    {
      if (!strncmp(argv[1], "add", 3))
	return (jmanager_add(jsh, argv));
      else if (!strncmp(argv[1], "list", 3))
	return (jmanager_list(jsh, argv));
    }
  else
    printf("jManager version 0.1 released on December, 12th, 2014\nUsage : jmanager [add <package name>] [search <package name>] [remove <package name>] [update] [list]\n");
  return (MODULE_OK);
}
