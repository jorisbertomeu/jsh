#include <curl/curl.h>
#include <jsh.h>
#include <module.h>

int	j_social(t_jsh *jsh, char **argv)
{
  if (!argv[1])
    {
      printf("Social Module V1.0 for jSh written by Joris Bertomeu\n");
      printf("Usage : social [connect] [disconnect] [profile] [wait] [request] [file]\n");
      return (MODULE_KO);
    }
  if (!strncmp(argv[1], "profile", 7))
    return (social_profile(jsh, argv));
  else if (!strncmp(argv[1], "connect", 7))
    return (social_connect(jsh, argv));
  else if (!strncmp(argv[1], "disconnect", 10))
    return (social_disconnect(jsh, argv));
  else
    {
      printf("Invalid argument, type \"social\" for more informations\n");
      return (MODULE_KO);
    }
  return (MODULE_OK);
}
