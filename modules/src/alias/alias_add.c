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
