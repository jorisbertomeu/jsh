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
