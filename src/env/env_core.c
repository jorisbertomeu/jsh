#include <jsh.h>

char	*my_getenv(char **env, char *str)
{
  int	i = 0;

  while (env[i])
    {
      if (!strncmp(env[i], str, strlen(str)))
	return (&env[i][strlen(str) + 1]);
      i++;
    }
  return (NULL);
}

int	set_env(t_jsh *jsh, char **env)
{
  int	i = 0;
  
  while (env[i])
    {
      if (!(jsh->env = realloc(jsh->env, (i + 1) * sizeof(char*))))
	return (0);
      if (!(jsh->env[i] = malloc((strlen(env[i]) + 1) * sizeof(char))))
	return (0);
      if (!(memset(jsh->env[i], 0, strlen(env[i]) + 1)))
	return (0);
      if (!(strcpy(jsh->env[i], env[i])))
	return (0);
      i++;
    }
  if (!(jsh->env = realloc(jsh->env, (i + 1) * sizeof(char*))))
    return (0);  
  jsh->env[i] = NULL;
  return (1);
}
