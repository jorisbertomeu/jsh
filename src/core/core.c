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
typedef	void(*sighandler_t)(int);
t_jsh	*g_jsh;

void	error(int code, t_jsh *jsh, char *msg)
{
  fprintf(stderr, "%s\n", msg);
  if (code == ERR_FATAL)
    {
      dump_jsh(jsh);
      exit(0);
    }
}

int	execute_command(t_jsh *jsh, char *file, char **argv)
{
  int	pid, status;

  if ((pid = fork()) == -1)
    return (0);
  else if (pid == 0)
    {
      if (!execve(file, argv, jsh->env))
	return (0);
    }
  else
    {
      waitpid(pid, &status, WUNTRACED | WCONTINUED);
      jsh->job_control.pid = pid;
    }
  return (1);
}

int	execute_true(t_jsh *jsh, char **argv)
{
  char	*line;
  char	*tmp;
  int	i = 5, j = 0;

  if (file_exists(argv[0]))
    {
      if (!execute_command(jsh, argv[0], argv))
	printf("Error while executing \"%s\"\n", argv[0]);
      return (1);
    }
  if (!(line = (char*) my_getenv(jsh->env, "PATH=")))
    return (0);
  if (!(tmp = malloc(4096 * sizeof(char))))
    return (0);
  while (i < strlen(line))
    {
      j = 0;
      memset(tmp, 0, 4096);
      while (line[i] != ':' && line[i])
	{
	  tmp[j] = line[i];
	  j++;
	  i++;
	}
      tmp[j] = 0;
      sprintf(tmp, "%s/%s", tmp, argv[0]);
      if (file_exists(tmp))
	{
	  if (!execute_command(jsh, tmp, argv))
	    printf("Error while executing \"%s\"\n", argv[0]);
	  free(tmp);
	  return (1);
	}
      i++;
    }
  free(tmp);
  return (0);
}

int	parse_cmd(t_jsh *jsh, char *cmd)
{
  int	(*command)(t_jsh*, char**) = NULL;
  char	**args;
  int	j = 0, i = 0;
  char	*module;

  if (!strncmp(cmd, "exit", 4))
    return (0);
  if (!(args = parse_args(cmd)))
    return (1);
  if (!execute_alias(jsh, args, cmd))
    {
      module = malloc((strlen(args[0]) + 3) * sizeof(char));
      memset(module, 0, strlen(args[0]) + 3);
      sprintf(module, "j_%s", args[0]);
      if (!(*(void **)(&command) = dlsym(jsh->modules_handle, module)))
	{
	  if (!execute_true(jsh, args))
	    printf("Commande \"%s\" not found\n", args[0]);
	}
      else
	(*command)(jsh, args);
      free(module);
    }
  while (i < j)
    free(args[i++]);
  add_history(jsh, cmd);
  i = 0;
  while (args[i])
    free(args[i++]);
  free(args);
  return (1);
}

int	execute_alias(t_jsh *jsh, char **argv, char *cmd)
{
  int	i = 0;
  char	*tmp;

  while (jsh->alias[i][0])
    {
      if (!strncmp(jsh->alias[i][0], argv[0], strlen(argv[0])))
	{
	  tmp = malloc((strlen(jsh->alias[i][1]) + strlen(cmd) + 4) * sizeof(char));
	  memset(tmp, 0, (strlen(jsh->alias[i][1]) + strlen(cmd)) + 4);
	  strcpy(tmp, jsh->alias[i][1]);
	  strcat(tmp, &cmd[strlen(jsh->alias[i][0])]);
	  parse_cmd(jsh, tmp);
	  free(tmp);
	  return (1);
	}
      i++;
    }
  return (0);
}

void	show_prompt(t_jsh *jsh)
{
  sprintf(jsh->prompt, "%s@%s> ",
	  (my_getenv(jsh->env, "USERNAME")) ? my_getenv(jsh->env, "USERNAME") : 
	  (my_getenv(jsh->env, "USER")) ? my_getenv(jsh->env, "USER") : "Unknown",
	  my_getenv(jsh->env, "PWD")); 
  write(1, jsh->prompt, strlen(jsh->prompt));
}

char	*readStdIn(t_jsh *jsh)
{
  char *r;
  int i;
  struct termios old,new;
  char c[3];

  tcgetattr(0,&old);
  new = old;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &new);
  i = 0;
  r = malloc(81 * sizeof(char));
  memset(r, 0, 81);
  jsh->history_position = jsh->history_max;
  while (read(0, &c, 3) && c[0] != '\n' && i < 80)
    { 
      if (c[0] == 27)
	{
	  if (c[2] == 65) //Fleche haut
	    up_history(jsh, r, &i);
	  else if (c[2] == 66) //Fleche bas
	    down_history(jsh, r, &i);
	}
      else if (c[0] == 9)
	search_auto_complete(jsh, r, &i);
      else if (c[0] == 127)
	{
	  if (i > 0)
	    {
	      r[i--] = 0;
	      write(0, "\b\b", 1);
	      write(0, "  ", 1);
	      write(0, "\b\b", 1);
	    }
	} 
      else
	{
	  r[i++] = c[0];
	  write(0, &c[0], 1);
	}
    } 
  r[i] = 0;
  tcsetattr(0, TCSANOW, &old);
  return (r);
}

void	signal_manager(t_jsh *jsh)
{
  int	i = 0, j = 0;

  while (i < NSIG)
    {
      j = 0;
      while (jsh->signals[j])
	{
	  if (jsh->signals[j]->sig_id == i)
	    signal(i, (sighandler_t) jsh->signals[j]->ptr_func);
	  j++;
	}
      i++;
    }
}

void	launchShell(t_jsh *jsh)
{
  char	*buffer;

  g_jsh = jsh;
  signal_manager(jsh);
  while (1)
    {
      
      show_prompt(jsh);
      buffer = readStdIn(jsh);
      printf("\n");
      if (!parse_cmd(jsh, buffer))
	{
	  free(buffer);
	  break;
	}
      free(buffer);
    }
}
