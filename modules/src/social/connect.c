#include <curl/curl.h>
#include <jsh.h>
#include <module.h>

int	g_back = 0;

int	function_pt(void *ptr, size_t size, size_t nmemb, void *stream){
  g_back = atoi(ptr);
  return (1);
}

int		http_post(char *url, char *params)
{
  CURL		*curl;
  CURLcode	res;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
      res = curl_easy_perform(curl);
      if (res != CURLE_OK)
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
      curl_easy_cleanup(curl);
    }
  curl_global_cleanup();
  return 0;
}

int	social_connect(t_jsh *jsh, char **argv)
{
  char	buff[4096];
  char	trame[4096];
  char	*password;

  memset(buff, 0, 4096);
  printf("SOCIAL MODULE V1\n");
  printf("\t* This module allow you to use especially social jSh's functions.\n");
  printf("\t* To use this mode, you have to connect you\n");
  write(1, "Username : ", 11);
  read(0, buff, 4096);
  buff[strlen(buff) - 1] = 0;
  password = getpass("Password : ");
  if (!password)
    {
      fprintf(stderr, "Error about memory allocation !\n");
      return (MODULE_KO);
    }
  sprintf(trame, "username=%s&password=%s", buff, password);
  write("Connecting ...\r", 15);
  http_post("http://jobertomeu.fr/jsh/jconnect.php", trame);
  if (g_back == 0)
    {
      fprintf(stderr, "Error while connection !\n");
      return (MODULE_KO);
    }
  if (jsh->social.mode == 1)
    free(jsh->social.pseudo);
  jsh->social.mode = 1;
  jsh->social.pseudo = malloc((strlen(buff) + 1) * sizeof(char));
  memset(jsh->social.pseudo, 0, strlen(buff) + 1);
  strcpy(jsh->social.pseudo, buff);
  printf("Connected successfully as %s\n", jsh->social.pseudo);
  free(password);
  return (MODULE_OK);
}
