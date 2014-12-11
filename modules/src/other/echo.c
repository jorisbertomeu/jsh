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

int	j_echo(t_jsh *jsh, char **argv)
{
  int	i = 0, cr = 1;

  while (argv[i])
    {
      if (!strncmp(argv[i], "-n", 2))
	cr = 0;
      i++;
    }
  printf("%s%c", argv[i - 1], (cr) ? '\n' : 0);
  return (MODULE_OK);
}
