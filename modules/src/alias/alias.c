#include <module.h>
#include <jsh.h>

int j_alias(t_jsh *jsh, char **argv)
{
  if (!argv[1])
    return (alias_list(jsh, argv));
  else if (argv[1] && argv[2])
    return (alias_add(jsh, argv));
  else
    {
      printf("Alias version 0.1 Written by Joris Bertomeu released on December, 7th, 2014\n");
      printf("Usage : alias <Alias> <Command>\n\tAllow to list aliases by typping without arguments\n");
    }
  return (MODULE_OK);
}
