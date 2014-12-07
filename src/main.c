#include <jsh.h>

int	parseArgs(int ac, char **argv)
{
  int	i = 0;

  while (i < ac)
    {
      if (!strncmp(argv[i], "-version", 8))
	{
	  printf("Version %s released on %s named %s\n", VER_VERSION, VER_DATE, VER_NAME);
	  return (1);
	}
      i++;
    }
  return (0);
}

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

void	dump_jsh(t_jsh *jsh)
{
  if (jsh != NULL)
    {
      free(jsh->name);
      free(jsh->prompt);
      dlclose(jsh->modules_handle);
    }
}

void	error(int code, t_jsh *jsh, char *msg)
{
  fprintf(stderr, "%s\n", msg);
  if (code == ERR_FATAL)
    {
      dump_jsh(jsh);
      exit(0);
    }
}

char	**parse_args(char *str)
{
  int	i = 0, j = 0, k = 0;
  char	**tab;
  char	*tmp;

  if (strlen(str) <= 0)
    return (NULL);
  tmp = malloc(4096 * sizeof(char));
  memset(tmp, 0, 4096);
  tab = calloc(1, sizeof(char*));
  while (str[k])
    {
      tab = realloc(tab, (i + 2) * sizeof(char*));
      j = 0;
      memset(tmp, 0, 4096);
      while (str[k] != ' ' && str[k])
	{
	  tmp[j] = str[k];
	  j++;
	  k++;
	}
      tab[i] = malloc((strlen(tmp) + 1) * sizeof(char));
      memset(tab[i], 0, strlen(tmp) + 1);
      strcpy(tab[i], tmp);
      k++;
      i++;
    }
  free(tmp);
  tab[i] = NULL;
  return (tab);
}

int	file_exists(char *path)
{
  FILE	*fd;

  if (!(fd = fopen(path, "r")))
    return (0);
  fclose(fd);
  return (1);
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
  if (!(line = my_getenv(jsh->env, "PATH=")))
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

int	execute_alias(t_jsh *jsh, char **argv, char *cmd)
{
  int	i = 0;
  char	*tmp;

  while (jsh->alias[i][0])
    {
      if (!strncmp(jsh->alias[i][0], argv[0], strlen(argv[0])))
	{
	  printf("Malloc de %d\n", (strlen(jsh->alias[i][1]) + strlen(argv[0]) + 4));
	  tmp = malloc((strlen(jsh->alias[i][1]) + strlen(argv[0]) + 4) * sizeof(char));
	  memset(tmp, 0, (strlen(jsh->alias[i][1]) + strlen(argv[0])) + 4);
	  //strcpy(tmp, jsh->alias[i][1]);
	  sprintf(tmp, "%s %s", jsh->alias[i][1], &cmd[strlen(jsh->alias[i][0]) + 1]);
	  //printf("TMP => %s\n", tmp);
	  parse_cmd(jsh, tmp);
	  free(tmp);
	  return (1);
	}
      i++;
    }
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

int	init_memory_alloc(t_jsh *jsh)
{
  if (!(jsh->alias = malloc(1 * sizeof(char**))))
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
  return (1);
}

char	*rm_bc(char *str)
{
  int	i = 0;
  char	*buff = malloc((strlen(str) + 1) * sizeof(char));

  memset(buff, 0, strlen(str) + 1);
  while (str[i] && str[i] != '\n')
    {
      buff[i] = str[i];
      i++;
    }
  return (buff);
}

void	parse_alias(t_jsh *jsh)
{
  FILE	*fd;
  char	*buff;
  int	i = 0, j = 0;

  fd = fopen("./jsh_alias", "r");
  if (fd == NULL)
    return;
  if (!(buff = malloc(4096 * sizeof(char))))
    return;
  memset(buff, 0, 4096);
  while (fgets(buff, 4096, fd))
    {
      i = 0;
      while (buff[i] && buff[i] != ':')
	i++;
      if (!(jsh->alias = realloc(jsh->alias, (j + 1) * sizeof(char*))))
	return;      
      if (!(jsh->alias[j] = malloc(2 * sizeof(char*))))
	return;
      if (!(jsh->alias[j][0] = malloc((i + 1) * sizeof(char))))
	return;
      if (!(jsh->alias[j][1] = malloc((strlen(buff) - i + 1) * sizeof(char))))
	return;
      memset(jsh->alias[j][0], 0, i + 1);
      memset(jsh->alias[j][1], 0, strlen(buff) - i + 1);
      strncpy(jsh->alias[j][0], rm_bc(buff), i);
      strcpy(jsh->alias[j][1], rm_bc(&buff[i + 1]));
      printf("Alias %s => %s\n", jsh->alias[j][0], jsh->alias[j][1]);
      j++;
      memset(buff, 0, 4096);
    }
  if (!(jsh->alias = realloc(jsh->alias, (j + 1) * sizeof(char*))))
    return;      
  if (!(jsh->alias[j] = malloc(2 * sizeof(char*))))
    return;
  if (!(jsh->alias[j][0] = malloc(1 * sizeof(char))))
    return;
  if (!(jsh->alias[j][1] = malloc(1 * sizeof(char))))
    return;
  jsh->alias[j][0] = 0;
  jsh->alias[j][1] = 0;
}

int	init_config(t_jsh *jsh)
{
  strcpy(jsh->name, "Joris Bertomeu");
  strcpy(jsh->prompt, "%s:%s> ");
  sprintf(jsh->prompt, "%s@%s> ", my_getenv(jsh->env, "USERNAME"), my_getenv(jsh->env, "PWD")); 
  jsh->version.ver_num = atoi(VER_VERSION);
  sprintf(jsh->version.ver_name, "%s", VER_NAME);
  sprintf(jsh->version.ver_date, "%s", VER_DATE);
  parse_alias(jsh);
  return (1);
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

void    loading()
{
  int   i = 0;
  char  tmp[512];

  printf("Starting jSh ... 100% Loaded\n");
  while (i <= 100)
    {
      sprintf(tmp, "Loading variable Shell .. <%d%%>\r", i);
      write(1, tmp, strlen(tmp));
      usleep(5000);
      i++;
    }
  printf("\n");
}

int	main(int ac, char *argv[], char **env)
{
  t_jsh	jsh;

  if (parseArgs(ac, argv))
    return (0);
  if (!init(&jsh, env))
    error(ERR_FATAL, &jsh, "Shell memory allocation failed, exiting ...");
  loading();
  launchShell(&jsh);
  dump_jsh(&jsh);
  return (0);
}
