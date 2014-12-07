#include <jsh.h>

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
    wait(&status);
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

void	launchShell(t_jsh *jsh)
{
  char	*buffer;

  if (!(buffer = malloc(4096 * sizeof(*buffer))))
    error(ERR_FATAL, jsh, "Shell buffer allocation failed, exiting ...");
  while (1)
    {
      sprintf(jsh->prompt, "%s@%s> ", my_getenv(jsh->env, "USERNAME"), my_getenv(jsh->env, "PWD")); 
      memset(buffer, 0, 4096);
      write(1, jsh->prompt, strlen(jsh->prompt));
      read(0, buffer, 4096);
      buffer[strlen(buffer) - 1] = 0;
      if (!parse_cmd(jsh, buffer))
	break;
    }
  free(buffer);
}
