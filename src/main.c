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

int	main(int ac, char *argv[], char **env)
{
  t_jsh	jsh;

  if (parseArgs(ac, argv))
    return (0);
  if (!init(&jsh, env))
    error(ERR_FATAL, &jsh, "Shell memory allocation failed, exiting ...");
  loading();
  launchShell(&jsh);
  dump_jsh(&jsh);
  return (0);
}
