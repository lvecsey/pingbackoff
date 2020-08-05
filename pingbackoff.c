/*
    Ping a remote site with a backoff policy and exit upon failure.
    Copyright (C) 2020  Lester Vecsey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

int main(int argc, char *argv[]) {

  FILE *fp;

  char cmd_str[80];

  char *hostname;

  int retval;

  char *line;

  size_t len;

  int exit_status;

  uint64_t counter;

  unsigned int seconds;

  hostname = argc>1 ? argv[1] : NULL;

  if (hostname == NULL) {
    printf("%s: Please specify hostname to ping.\n", __FUNCTION__);
    return -1;
  }
  
  sprintf(cmd_str, "ping -c 1 -W 5 %s", hostname);

  counter = 0;

  seconds = 1;
  
  for (;;) {

    printf("[%lu] Sleeping for %u seconds.\n", counter, seconds);

    sleep(seconds);

    line = NULL;
    len = 0;
    
    fp = popen(cmd_str, "r");
    if (fp==NULL) {
      perror("fopen");
      return -1;
    }

    while ((retval = getline(&line,&len,fp)) != -1) {
      if (len > 0) {
	printf("Line: %s", line);
      }
    }

    free(line);
      
    exit_status = pclose(fp);
    if (exit_status == -1) {
      perror("pclose");
      return -1;
    }

    switch(exit_status) {
    case 0:
      seconds <<= 1;
      break;

    case 1:
      printf("Failed the ping.\n");
      return -1;

    case 256:
      printf("Got case 256.\n");
      return -1;
      
    default:
      printf("ping returned exit_status %d\n", exit_status);
      break;
    }

    counter++;
    
  }
    
  return 0;

}
    


  
