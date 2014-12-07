#include <jsh.h>

void	parse_alias(t_jsh *jsh)
{
  FILE	*fd;
  char	*buff;
  char	*tmp;
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
      tmp = rm_bc(buff);
      strncpy(jsh->alias[j][0], tmp, i);
      free(tmp);
      tmp = rm_bc(&buff[i + 1]);
      strcpy(jsh->alias[j][1], tmp);
      free(tmp);
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
  printf("Alloc pour j = %d\n", j);
  jsh->alias[j][0] = 0;
  jsh->alias[j][1] = 0;
  free(buff);
}
