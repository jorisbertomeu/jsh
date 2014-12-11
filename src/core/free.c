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

void	free_alias(t_jsh *jsh)
{
  int	i = 0;

  while (jsh->alias[i][0])
    {
      free(jsh->alias[i][0]);
      free(jsh->alias[i][1]);
      free(jsh->alias[i]);
      i++;
    }
  free(jsh->alias[i][0]);
  free(jsh->alias[i][1]);
  free(jsh->alias[i]);
  free(jsh->alias);
}

void	free_env(t_jsh *jsh)
{
  int	i = 0;

  while (jsh->env[i])
    free(jsh->env[i++]);
  free(jsh->env);
}

void	free_config(t_jsh *jsh)
{
  if (!jsh->config.alias_path)
    free(jsh->config.alias_path);
  if (!jsh->config.history_path)
    free(jsh->config.history_path);
  if (!jsh->config.log_path)
    free(jsh->config.log_path);
}

void	free_version(t_jsh *jsh)
{
  free(jsh->version.ver_name);
  free(jsh->version.ver_date);
}

void	dump_jsh(t_jsh *jsh)
{
  if (jsh != NULL)
    {
      free(jsh->name);
      free(jsh->prompt);
      dlclose(jsh->modules_handle);
      free_alias(jsh);
      free_env(jsh);
      //free_config(jsh);
      free_version(jsh);
      if (jsh->social.mode == 1)
	free(jsh->social.pseudo);
    }
}
