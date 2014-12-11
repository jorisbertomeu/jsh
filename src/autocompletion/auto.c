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

int	search_auto_complete(t_jsh *jsh, char *str, int *i)
{
  if (search_autocomplete_alias(jsh, str, i))
    return(1);
  if (search_autocomplete_cmd(jsh, str, i))
    return(1);
  return (0);
}

int	cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *) p1, *(char * const *) p2);
}

void	free_tab(char **tab, int j)
{
  int	i = 0;

  while (i < j)
      free(tab[i++]);
  free(tab);
}


