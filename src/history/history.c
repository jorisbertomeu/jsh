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

void	clear_prompt(int *i)
{
  char	clean[*i + 1];

  memset(clean, '\b', *i + 1);
  write(0, clean, *i);
  memset(clean, ' ', *i + 1);
  write(0, clean, *i);
  memset(clean, '\b', *i + 1);
  write(0, clean, *i);
  *i = 0;
}

void	up_history(t_jsh *jsh, char *str, int *i)
{
  if (jsh->history[jsh->history_position - 1] && jsh->history_position - 1 >= 0)
    {
      clear_prompt(i);
      *i = strlen(jsh->history[jsh->history_position - 1]);
      write(0, jsh->history[jsh->history_position - 1], *i + 1);
      strcpy(str, jsh->history[jsh->history_position - 1]);
    }
  jsh->history_position = (jsh->history_position <= 0) ? 0 : jsh->history_position - 1;
}

void	add_history(t_jsh *jsh, char *cmd)
{
  jsh->history = realloc(jsh->history, (jsh->history_max + 2) * sizeof(char*));
  jsh->history[jsh->history_max] = malloc((strlen(cmd) + 1) * sizeof(char));
  memset(jsh->history[jsh->history_max], 0, strlen(cmd) + 1);
  strcpy(jsh->history[jsh->history_max], cmd);
  jsh->history[jsh->history_max + 1] = NULL;
  jsh->history_max++;
}

void	down_history(t_jsh *jsh, char *str, int *i)
{
  if (jsh->history[jsh->history_position] && jsh->history_position + 1 < jsh->history_max)
    {
      clear_prompt(i);
      *i = strlen(jsh->history[jsh->history_position + 1]);
      write(0, jsh->history[jsh->history_position + 1], *i);
      strcpy(str, jsh->history[jsh->history_position + 1]);
    }
  else
    clear_prompt(i);
  jsh->history_position = (jsh->history_position >= jsh->history_max) ? jsh->history_max : jsh->history_position + 1;
}
