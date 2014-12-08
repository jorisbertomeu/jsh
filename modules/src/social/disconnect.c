#include <curl/curl.h>
#include <jsh.h>
#include <module.h>

int	social_disconnect(t_jsh *jsh, char **argv)
{
  if (jsh->social.mode == 0)
    {
      printf("You're not connected !\n");
      return (MODULE_KO);
    }
  jsh->social.mode = 0;
  free(jsh->social.pseudo);
  printf("Connected as %s and you have been disconnected\n", jsh->social.pseudo);
  return (MODULE_OK);
}
