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

void    loading()
{
  int   i = 0;
  char  tmp[512];

  printf("Starting jSh ...\t\t<100%%>\n");
  while (i <= 100)
    {
      sprintf(tmp, "Loading variable Shell ...\t<%d%%>\r", i);
      write(1, tmp, strlen(tmp));
      usleep(5000);
      i++;
    }
  printf("\n");
}
