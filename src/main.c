#include <jsh.h>

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
