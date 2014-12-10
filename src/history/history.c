#include <jsh.h>

void	up_history(t_jsh *jsh, char *str, int *i)
{
  char	clean[*i + 1];

  memset(clean, '\b', *i + 1);
  if (jsh->history[jsh->history_position] && jsh->history_position != -1)
    {
      write(1, clean, *i);
      *i = strlen(jsh->history[jsh->history_position]);
      write(1, jsh->history[jsh->history_position], *i + 1);
      strcpy(str, jsh->history[jsh->history_position]);
    }
  jsh->history_position = (jsh->history_position <= 0) ? 0 : jsh->history_position - 1;
}

void	down_history(t_jsh *jsh, char *str, int *i)
{
  char	clean[*i + 1];

  memset(clean, '\b', *i + 1);
  if (jsh->history[jsh->history_position] && jsh->history_position != jsh->history_max)
    {
      write(1, clean, *i);
      *i = strlen(jsh->history[jsh->history_position]);
      write(1, jsh->history[jsh->history_position], *i);
      strcpy(str, jsh->history[jsh->history_position]);
    }
  jsh->history_position = (jsh->history_position >= jsh->history_max) ? jsh->history_max : jsh->history_position + 1;
}
