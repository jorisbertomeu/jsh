#include <curl/curl.h>
#include <jsh.h>
#include <module.h>

int	social_profile(t_jsh *jsh, char **argv)
{
  if (jsh->social.mode == 0)
    {
      printf("You're not connected, please, connect you \"social connect\"\n");
      return (MODULE_KO);
    }
  printf("Connected as %s\n", jsh->social.pseudo);
  printf("\t* FSSP status : Available\n");
  printf("\t* FFSP status : Available\n");
  printf("\t* Waiting Mode status : Available\n");
  printf("To disconnect you, use \"social disconnect\"\n");
  return (MODULE_OK);
}
