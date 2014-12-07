#include <jsh.h>

void    loading()
{
  int   i = 0;
  char  tmp[512];

  printf("Starting jSh ... 100%% Loaded\n");
  while (i <= 100)
    {
      sprintf(tmp, "Loading variable Shell .. <%d%%>\r", i);
      write(1, tmp, strlen(tmp));
      usleep(5000);
      i++;
    }
  printf("\n");
}
