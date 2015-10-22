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

int	j_fg(t_jsh *jsh, char **argv)
{
  int	pid, status;

  if (jsh->job_control.status == 0)
    printf("No suspended task found\n");
  else
    {
      jsh->job_control.status = 0;
      if (kill(jsh->job_control.pid, SIGCONT) == -1)
	{
	  printf("Unable to restore suspended task\n");
	  return (MODULE_KO);
	}
    }
  return (MODULE_OK);
}
