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

char	*get_in_env(t_jsh *jsh, char *field)
{
  int	i = 0;
  char	tmp[strlen(field) + 1];

  memset(tmp, 0, strlen(field) + 1);
  sprintf(tmp, "%s=", field);
  while (jsh->env[i])
    {
      if (!strncmp(jsh->env[i], tmp, strlen(tmp)))
	return (&(jsh->env[i])[strlen(tmp)]);
      i++;
    }
  return (NULL);
}

int	j_cd(t_jsh *jsh, char **argv)
{
  char	buff[4096];
  char	*old;

  memset(buff, 0, 4096);
  if (argv[1] != NULL && !strncmp(argv[1], "-", 1))
    {
      if (!(old = get_in_env(jsh, "OLDPWD")))
	{
	  printf("\"OLDPWD\" undefined into environment\n");
	  return (MODULE_KO);
	}
      chdir(old);
    }
  else
    chdir(argv[1]);
  getcwd(buff, sizeof(buff));
  set_in_env(jsh, "OLDPWD", get_in_env(jsh, "PWD"));
  set_in_env(jsh, "PWD", buff);
  return (MODULE_OK);
}
