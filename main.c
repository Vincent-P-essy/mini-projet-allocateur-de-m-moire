#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "my_malloc.h"

int main(int argc, char* argv[]){
  int i;
  int* tab;

  srand(time(NULL));
  
  for (i=0 ; i<1500 ; i++){
    tab = my_malloc(rand() % 1000);
    if (tab == NULL)
      fprintf(stderr, "Echec allocation\n");
    else
      fprintf(stderr, "Adr : %lu\n", tab);
  }
  printf("C'est fait !\n");  
  return 0;
}
