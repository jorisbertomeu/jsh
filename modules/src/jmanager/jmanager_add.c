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

int	jmanager_add(t_jsh *jsh, char **argv)
{
  if (argv[2] == NULL)
    {
      printf("jManager Add - Missing parameter package name\n");
      return (MODULE_KO);
    }
  printf("Searching package \"%s\" ...\n", argv[2]);
  printf("\033[33mSorry, package \"%s\" not found\033[0m\n", argv[2]); 
  return (MODULE_OK);
}
