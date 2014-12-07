#include <jsh.h>

int	file_exists(char *path)
{
  FILE	*fd;

  if (!(fd = fopen(path, "r")))
    return (0);
  fclose(fd);
  return (1);
}

char	*rm_bc(char *str)
{
  int	i = 0;
  char	*buff = malloc((strlen(str) + 1) * sizeof(char));

  memset(buff, 0, strlen(str) + 1);
  while (str[i] && str[i] != '\n')
    {
      buff[i] = str[i];
      i++;
    }
  return (buff);
}
