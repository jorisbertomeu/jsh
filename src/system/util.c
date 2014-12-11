/* 
** jSh - The social Shell
** Copyright (C) 2014 Joris Bertomeu
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
