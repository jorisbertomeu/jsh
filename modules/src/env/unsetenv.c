#include <jsh.h>
#include <module.h>

int	unset_in_env(t_jsh *jsh, char *field)
{
  int	i = 0;
  char	tmp[strlen(field) + 1];
  int	flag = 0;

  memset(tmp, 0, strlen(field) + 1);
  sprintf(tmp, "%s=", field);
  while (jsh->env[i])
    {
      if (!strncmp(jsh->env[i], tmp, strlen(tmp)) && flag == 0)
	{
	  flag = 1;
	  free(jsh->env[i]);
	}
      else if (flag == 1)
	{
	  jsh->env[i - 1] = malloc((strlen(jsh->env[i]) + 1) * sizeof(char));
	  memset(jsh->env[i - 1], 0, strlen(jsh->env[i]) + 1);
	  strcpy(jsh->env[i - 1], jsh->env[i]);
	  free(jsh->env[i]);
	}
      i++;
    }
  jsh->env = realloc(jsh->env, (i + 1) * sizeof(char*));
  jsh->env[i - 1] = NULL;
  return (flag);
}

int	j_unsetenv(t_jsh *jsh, char **argv)
{
  if (argv[1] != NULL)
    {
      if (!unset_in_env(jsh, argv[1]))
	{
	  printf("Unable to find \"%s\" into environment\n", argv[1]);
	  return (MODULE_KO);
	}
    }
  else
    {
      printf("Usage : unsetenv [VARIABLE]\n");
      printf("Written by Joris Bertomeu for jSh on December, 6th, 2014\n");
      printf("Description : Remove variable from environment\n");
      return (MODULE_KO);
    }
  return (MODULE_OK);
}
