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

int	parseArgs(int ac, char **argv)
{
  int	i = 0;

  while (i < ac)
    {
      if (!strncmp(argv[i], "-version", 8))
	{
	  printf("Version %s released on %s named %s\n", VER_VERSION, VER_DATE, VER_NAME);
	  return (1);
	}
      i++;
    }
  return (0);
}

char	**parse_args(char *str)
{
  int	i = 0, j = 0, k = 0;
  char	**tab;
  char	*tmp;
  char	separator;

  if (strlen(str) <= 0)
    return (NULL);
  if (!(tmp = malloc(4096 * sizeof(char))))
    return (NULL);
  memset(tmp, 0, 4096);
  tab = calloc(1, sizeof(char*));
  while (str[k])
    {
      tab = realloc(tab, (i + 2) * sizeof(char*));
      j = 0;
      separator = ' ';
      memset(tmp, 0, 4096);
      while (str[k] == ' ')
	k++;
      while (str[k] != separator && str[k])
	{
	  if (j == 0 && str[k] == '\"')
	    separator = '\"';
	  else
	    tmp[j++] = str[k];
	  k++;
	}
      tab[i] = malloc((strlen(tmp) + 1) * sizeof(char));
      memset(tab[i], 0, strlen(tmp) + 1);
      strcpy(tab[i], tmp);
      k++;
      i++;
    }
  free(tmp);
  tab[i] = NULL;
  return (tab);
}
