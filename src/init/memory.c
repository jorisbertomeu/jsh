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

int	init_memory_alloc(t_jsh *jsh)
{
  if (!(jsh->alias = malloc(1 * sizeof(char**))))
    return (0);
  if (!(jsh->history = malloc(2 * sizeof(char*))))
    return (0);
  if (!(jsh->name = malloc(128 * sizeof(char))))
    return (0);
  memset(jsh->name, 0, 128);
  if (!(jsh->prompt = malloc(128 * sizeof(char))))
    return (0);
  memset(jsh->prompt, 0, 128);
  if (!(jsh->env = malloc(1 * sizeof(char*))))
    return (0);
  if (!(jsh->version.ver_name = malloc(128 * sizeof(char))))
    return (0);
  memset(jsh->version.ver_name, 0, 128);
  if (!(jsh->version.ver_date = malloc(128 * sizeof(char))))
    return (0);
  memset(jsh->version.ver_date, 0, 128);
  if (!(jsh->social.pseudo = malloc(128 * sizeof(char))))
    return (0);
  memset(jsh->social.pseudo, 0, 128);
  return (1);
}

int	init_config(t_jsh *jsh)
{
  strcpy(jsh->name, "Joris Bertomeu");
  strcpy(jsh->prompt, "%s:%s> ");
  sprintf(jsh->prompt, "%s@%s> ", my_getenv(jsh->env, "USERNAME"), my_getenv(jsh->env, "PWD")); 
  jsh->version.ver_num = atoi(VER_VERSION);
  sprintf(jsh->version.ver_name, "%s", VER_NAME);
  sprintf(jsh->version.ver_date, "%s", VER_DATE);
  jsh->social.mode = 0;
  parse_alias(jsh);
  parse_history(jsh);
  return (1);
}

int	init(t_jsh *jsh, char **env)
{
  if (!init_memory_alloc(jsh))
    return (0);
  if (!(jsh->modules_handle = dlopen("libjsh.so", RTLD_LAZY)))
    return (0);
  if (!set_env(jsh, env))
    return (0);
  if (!init_config(jsh))
    return (0);
  return (1);
}
