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

char	*my_getenv(char **env, char *str)
{
  int	i = 0;

  while (env[i])
    {
      if (!strncmp(env[i], str, strlen(str)))
	return (&env[i][strlen(str) + 1]);
      i++;
    }
  return (NULL);
}

int	set_env(t_jsh *jsh, char **env)
{
  int	i = 0;
  
  while (env[i])
    {
      if (!(jsh->env = realloc(jsh->env, (i + 1) * sizeof(char*))))
	return (0);
      if (!(jsh->env[i] = malloc((strlen(env[i]) + 1) * sizeof(char))))
	return (0);
      if (!(memset(jsh->env[i], 0, strlen(env[i]) + 1)))
	return (0);
      if (!(strcpy(jsh->env[i], env[i])))
	return (0);
      i++;
    }
  if (!(jsh->env = realloc(jsh->env, (i + 1) * sizeof(char*))))
    return (0);  
  jsh->env[i] = NULL;
  return (1);
}
