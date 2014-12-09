#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <termios.h>
#include <sys/types.h>
#include <dirent.h>
#define VER_VERSION "0.01"
#define VER_DATE "06/12/2014"
#define VER_NAME "Kumcat"
#define ERR_FATAL 1

typedef	struct	s_social
{
  int		mode;
  char		*pseudo;
  char		*state;
}		t_social;

typedef	struct	s_version
{
  int		ver_num;
  char		*ver_name;
  char		*ver_date;
}		t_version;

typedef struct	s_config
{
  char		*alias_path;
  char		*history_path;
  char		*log_path;
}		t_config;

typedef	struct	s_jsh
{
  char		*name;
  char		*prompt;
  void		*modules_handle;
  char		**env;
  t_version	version;
  char		***alias;
  t_config	config;
  t_social	social;
}		t_jsh;

void	dump_jsh(t_jsh *jsh);
void	error(int code, t_jsh *jsh, char *msg);
int	execute_command(t_jsh *jsh, char *file, char **argv);
int	execute_true(t_jsh *jsh, char **argv);
int	parse_cmd(t_jsh *jsh, char *cmd);
int	execute_alias(t_jsh *jsh, char **argv, char *cmd);
void	launchShell(t_jsh *jsh);
int	parseArgs(int ac, char **argv);
char	**parse_args(char *str);
char	*my_getenv(char **env, char *str);
int	set_env(t_jsh *jsh, char **env);
void    loading();
void	parse_alias(t_jsh *jsh);
int	init_memory_alloc(t_jsh *jsh);
int	init_config(t_jsh *jsh);
int	init(t_jsh *jsh, char **env);
int	file_exists(char *path);
char	*rm_bc(char *str);
int	cmpstringp(const void *p1, const void *p2);
int	search_autocomplete_alias(t_jsh *jsh, char *str, int *i);
int	search_autocomplete_cmd(t_jsh *jsh, char *str, int *k);
