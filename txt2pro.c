#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
                  
#define CRITTER_SIZE 103
int critter[CRITTER_SIZE];

int main(int argc, char* argv[])
{
  char buffer[128];
  int32_t temp;

  memset(buffer, '\0', sizeof(buffer));
  strcpy(buffer, argv[1]);
  
  char * ext_pro = ".pro";
  char * ext_txt = ".txt";
  
  strcat(buffer, ext_txt);
  
  FILE * input = fopen(buffer, "r");

  for (size_t i = 0; i < CRITTER_SIZE; i++)
  {
    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, table_critter[i]);
    strcat(buffer, " %d\n");
    
    fscanf(input, buffer, &temp);
    critter[i] = NTOHL(temp);
  }

  memset(buffer, '\0', sizeof(buffer));
  strcpy(buffer, argv[1]);
  strcat(buffer, ext_pro);
  
  FILE * output = fopen(buffer, "wb");

  
  fwrite(&critter, sizeof(critter), 1, output);
  
  fclose(input);
  fclose(output);

}
