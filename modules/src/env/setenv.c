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

char	*set_in_env(t_jsh *jsh, char *field, char *str)
{
  int	i = 0;
  char	tmp[strlen(field) + 1];

  memset(tmp, 0, strlen(field) + 1);
  sprintf(tmp, "%s=", field);
  while (jsh->env[i])
    {
      if (!strncmp(jsh->env[i], tmp, strlen(tmp)))
	{
	  free(jsh->env[i]);
	  jsh->env[i] = malloc((strlen(str) + 1 + strlen(tmp)) * sizeof(char));
	  memset(jsh->env[i], 0, strlen(str) + strlen(tmp) + 1);
	  sprintf(jsh->env[i], "%s%s", tmp, str); 
	  return (jsh->env[i]);
	}
      i++;
    }
  jsh->env = realloc(jsh->env, (i + 2) * sizeof(char*));
  jsh->env[i] = malloc((strlen(str) + 1 + strlen(tmp)) * sizeof(char));
  memset(jsh->env[i], 0, strlen(str) + strlen(tmp) + 1);
  sprintf(jsh->env[i], "%s%s", tmp, str); 
  jsh->env[i + 1] = NULL;
  return (NULL);
}

int	j_setenv(t_jsh *jsh, char **argv)
{
  if (!strncmp(argv[1], "-v", 2) || !strncmp(argv[1], "-version", 8) ||
      !strncmp(argv[1], "-h", 2) || !strncmp(argv[1], "-help", 5))
    {
      printf("Usage : setenv [VARIABLE] [VALUE]\n");
      printf("Written by Joris Bertomeu for jSh on December, 6th, 2014\n");
      printf("Description : Add or modify environment variable, variable will be updated if it exists\n");
      return (MODULE_OK);
    }
  if (argv[1] != NULL && argv[2] != NULL)
    set_in_env(jsh, argv[1], argv[2]);
  else
    printf("Usage : setenv [VARIABLE] [VALUE]\n");
  return (MODULE_OK);
}
