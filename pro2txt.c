#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
                  
#define CRITTER_SIZE 103
int critter[CRITTER_SIZE];

int main(int argc, char* argv[])
{
  char buffer[128];

  char * ext_pro = ".pro";
  char * ext_txt = ".txt";
  
  memset(buffer, '\0', sizeof(buffer));
  strcpy(buffer, argv[1]);
  strcat(buffer, ext_pro);

  FILE * input = fopen(buffer, "rb");
  
  memset(buffer, '\0', sizeof(buffer));
  strcpy(buffer, argv[1]);
  strcat(buffer, ext_txt);

  FILE * output = fopen(buffer, "w");
  
  fread(&critter, sizeof(critter), 1, input);

  for (size_t i = 0; i < CRITTER_SIZE; i++)
  {
    critter[i] = HTONL(critter[i]);
    
    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, table_critter[i]);
    strcat(buffer, " %d\n");
  
    fprintf(output, buffer, critter[i]);
  }

  fclose(input);
  fclose(output);

}
