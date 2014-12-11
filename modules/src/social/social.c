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
