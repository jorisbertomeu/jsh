#include <jsh.h>

char	**read_dir(char *tmp, char **tab, int *l, char *str)
{
  struct dirent *lecture;
  DIR		*rep;

  rep = opendir(tmp);
  if (rep)
    {
      while ((lecture = readdir(rep)))
	{
	  if (!strncmp(str, lecture->d_name, strlen(str)))
	    {
	      tab = realloc(tab, (*l + 1) * sizeof(char*));
	      tab[*l] = malloc((strlen(lecture->d_name) + 1) * sizeof(char));
	      memset(tab[*l], 0, strlen(lecture->d_name) + 1);
	      strcpy(tab[*l], lecture->d_name);
	      *l += 1;
	    }
	}
      closedir(rep);
      qsort(&tab[0], *l, sizeof(char *), cmpstringp);
    }
  return (tab);
}

int	identical_start(char **tab, int l)
{
  int	i = 1, j = 0;
  int	result = 4096;

  while (i < l)
    {
      j = 0;
      while (tab[i][j])
	{
	  if (!(tab[i - 1][j] && tab[i][j] == tab[i - 1][j]))
	    break;
	  j++;
	}
      result = (result > j) ? j : result;
      i++;
    }
  return (result);
}

char		**fill_tab(char *str, int *l, char *line)
{
  char		**tab;
  int		i = 0, j;
  char		*tmp;

  *l = 0;
  if (!(tmp = malloc(4096 * sizeof(char))))
    return (NULL);
  if (!(tab = malloc(1 * sizeof(char*))))
    return (NULL);
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
      tab = read_dir(tmp, tab, l, str);
      i++;
    }
  return (tab);
}

int		search_autocomplete_cmd(t_jsh *jsh, char *str, int *k)
{
  char		*line;
  int		i = 5, j = 0, l = 0;
  char		**tab;

  if (!(line = (char*) my_getenv(jsh->env, "PATH=")))
    return (0);
  tab = fill_tab(str, &l, line);
  if (!tab)
    return (0);
  i = 0;
  if (l == 1)
    {
      write(1, &(tab[i])[*k], strlen(&(tab[i])[*k]));
      *k = strlen(tab[i]);
      strcpy(str, tab[i]);
    }
  else
    {
      i = 0;
      printf("\n");
      while (i < l)
	printf("%s\t", tab[i++]);
      printf("\n");
      show_prompt(jsh);
      *k = identical_start(tab, l);
      write(1, tab[0], *k);
      strncpy(str, tab[0], *k);
    }
  free_tab(tab, l);
}
