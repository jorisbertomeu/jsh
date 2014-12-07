#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#define VER_VERSION "0.01"
#define VER_DATE "06/12/2014"
#define VER_NAME "Kumcat"
#define ERR_FATAL 1

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
}		t_jsh;
