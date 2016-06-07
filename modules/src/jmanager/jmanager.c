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

int	j_jmanager(t_jsh *jsh, char **argv)
{
  if (argv[1] != NULL)
    {
      if (!strncmp(argv[1], "add", 3))
	return (jmanager_add(jsh, argv));
      else if (!strncmp(argv[1], "list", 3))
	return (jmanager_list(jsh, argv));
      else {
	printf("jManager - Command \"%s\" not found ..\n", argv[1]);
      }
    }
  else
    printf("jManager version 0.1 released on December, 12th, 2014\nUsage : jmanager [add <package name>] [search <package name>] [remove <package name>] [update] [list]\n");
  return (MODULE_OK);
}
