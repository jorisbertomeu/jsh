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

#include <module.h>
#include <jsh.h>

int j_alias(t_jsh *jsh, char **argv)
{
  if (!argv[1])
    return (alias_list(jsh, argv));
  else if (argv[1] && argv[2])
    return (alias_add(jsh, argv));
  else
    {
      printf("Alias version 0.1 Written by Joris Bertomeu released on December, 7th, 2014\n");
      printf("Usage : alias <Alias> <Command>\n\tAllow to list aliases by typping without arguments\n");
    }
  return (MODULE_OK);
}
