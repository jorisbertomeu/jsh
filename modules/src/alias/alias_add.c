#include <jsh.h>
#include <module.h>

int	alias_add(t_jsh *jsh, char **argv)
{
  int	i = 0;
  
  while (jsh->alias[i][0])
    i++;
  jsh->alias = realloc(jsh->alias, (i + 2) * sizeof(char**));
  jsh->alias[i] = malloc(2 * sizeof(char*));

  jsh->alias[i][0] = malloc((strlen(argv[1]) + 1) * sizeof(char));
  memset(jsh->alias[i][0], 0, strlen(argv[1]) + 1);
  strcpy(jsh->alias[i][0], argv[1]);

  jsh->alias[i][1] = malloc((strlen(argv[2]) + 1) * sizeof(char));
  memset(jsh->alias[i][1], 0, strlen(argv[2]) + 1);
  strcpy(jsh->alias[i][1], argv[2]);

  jsh->alias[i + 1] = malloc(2 * sizeof(char*));
  jsh->alias[i + 1][0] = malloc(sizeof(char));
  jsh->alias[i + 1][0] = 0;
  jsh->alias[i + 1][1] = malloc(sizeof(char));
  jsh->alias[i + 1][1] = 0;
  return (MODULE_OK);
}
