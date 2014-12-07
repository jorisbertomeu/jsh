#include <jsh.h>

void	parse_alias(t_jsh *jsh)
{
  FILE	*fd;
  char	*buff;
  int	i = 0, j = 0;

  fd = fopen("./jsh_alias", "r");
  if (fd == NULL)
    return;
  if (!(buff = malloc(4096 * sizeof(char))))
    return;
  memset(buff, 0, 4096);
  while (fgets(buff, 4096, fd))
    {
      i = 0;
      while (buff[i] && buff[i] != ':')
	i++;
      if (!(jsh->alias = realloc(jsh->alias, (j + 1) * sizeof(char*))))
	return;      
      if (!(jsh->alias[j] = malloc(2 * sizeof(char*))))
	return;
      if (!(jsh->alias[j][0] = malloc((i + 1) * sizeof(char))))
	return;
      if (!(jsh->alias[j][1] = malloc((strlen(buff) - i + 1) * sizeof(char))))
	return;
      memset(jsh->alias[j][0], 0, i + 1);
      memset(jsh->alias[j][1], 0, strlen(buff) - i + 1);
      strncpy(jsh->alias[j][0], rm_bc(buff), i);
      strcpy(jsh->alias[j][1], rm_bc(&buff[i + 1]));
      printf("Alias %s => %s\n", jsh->alias[j][0], jsh->alias[j][1]);
      j++;
      memset(buff, 0, 4096);
    }
  if (!(jsh->alias = realloc(jsh->alias, (j + 1) * sizeof(char*))))
    return;      
  if (!(jsh->alias[j] = malloc(2 * sizeof(char*))))
    return;
  if (!(jsh->alias[j][0] = malloc(1 * sizeof(char))))
    return;
  if (!(jsh->alias[j][1] = malloc(1 * sizeof(char))))
    return;
  jsh->alias[j][0] = 0;
  jsh->alias[j][1] = 0;
}
