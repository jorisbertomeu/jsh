/* 
** jSh - The social Shell
** Copyright (C) 2014 Joris Bertomeu
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <jsh.h>
#include <module.h>
#include <nxjson.h>

char	list[4096];

int	jmanager_list_recover(void *ptr, size_t size, size_t nmemb, void *stream)
{
  strcpy(list, ptr);
  return (1);
}

int		jmanager_list(t_jsh *jsh, char **argv)
{
  nx_json	*json;
  nx_json	*packages;
  int		i = 0;

  printf("Fetching available packages ...\n");
  memset(list, 0, 4096);
  http_post("http://jobertomeu.fr/jsh/jmanager_list.php", "", jmanager_list_recover);
  json = nx_json_parse(list, 0);
  if (!json)
    {
      printf("Error while receiving data\n");
      return (MODULE_KO);
    }
  packages = nx_json_get(json, "packages");
  while (i < packages->length)
    {
      nx_json	*item = nx_json_item(packages, i);
      printf("\033[1m%s\033[22m - %s by %s\n", 
	     nx_json_get(item, "nom")->text_value,
	     nx_json_get(item, "description")->text_value,
	     nx_json_get(item, "author")->text_value);
      i++;
    }
  return (MODULE_OK);
}
