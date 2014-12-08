#include <curl/curl.h>
#include <jsh.h>
#include <module.h>

int	social_connect(t_jsh *jsh, char **argv);

int	j_social(t_jsh *jsh, char **argv)
{
  if (!argv[1])
    {
      printf("SOCIAL MODULE V1\n");
      printf("Usage : social [connect] [disconnect] [profile] [wait] [request]\n");
      return (MODULE_KO);
    }
  if (!strncmp(argv[1], "connect", 7))
    return (social_connect(jsh, argv));
  if (!strncmp(argv[1], "profile", 7))
    return (social_profile(jsh, argv));
  else
    {
      printf("Invalid argument, type \"social\" for more informations\n");
      return (MODULE_KO);
    }
  return (MODULE_OK);
}
