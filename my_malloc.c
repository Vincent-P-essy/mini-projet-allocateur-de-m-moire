#include <stdio.h>

#include "my_malloc.h"






typedef struct bloc{
  size_t size;

  int free;
  struct bloc *suiv;
  struct bloc *prec;

}bloc;
#define POOL_SIZE 1000000000

#define EN_TETE sizeof(bloc)
static char _mem_pool[POOL_SIZE]; 


static bloc *list=NULL;
static int demarre=0;
static bloc *last_free=NULL;

static void cree_memoire(){
  list=(bloc*) _mem_pool;
  list->size=POOL_SIZE-EN_TETE;
  list->free=1;
  list->suiv=list->prec=NULL;
  demarre=1;
  last_free=list;
  
}



static void fragment(bloc *b,size_t new_size){
  if (b->size >= new_size + EN_TETE + 1){ 
    bloc *nouv=(bloc*)((char*)b + EN_TETE + new_size);
    nouv->size=b->size - new_size - EN_TETE;
    nouv->free=1;
    nouv->suiv=b->suiv;
    nouv->prec=b;
    if (nouv->suiv){
      nouv->suiv->prec=nouv;
    }
    b->size=new_size;
    b->suiv=nouv;
    
  }

}

void* my_malloc(size_t size){
  if (!size){
    return NULL;
  }
  if (!demarre){
    cree_memoire();

  }
  bloc *start;
  if (last_free){
    start=last_free;
  }else{
    start=list;
  }
  bloc *tmp=start;

  do{
    if (tmp->free && tmp->size >= size){
      if (tmp->size >= size + EN_TETE +1){
        fragment(tmp,size);
      }
      tmp->free=0;
      last_free=tmp->suiv ? tmp->suiv :list;
      return (void*)((char*)tmp + EN_TETE);
    }
    if (tmp->suiv){
      tmp=tmp->suiv;
    }else{
      tmp=list;
    }
  }while (tmp != start);
  return NULL;

}


void my_free(void* pouet){
  if (!pouet){
    return ;
  }

  bloc *nouv=(bloc*)((char*)pouet - EN_TETE);
  nouv->free=1;

  if (nouv->suiv && nouv->suiv->free){
    nouv->size += EN_TETE + nouv->suiv->size;
    nouv->suiv=nouv->suiv->suiv;
  
    if (nouv->suiv){
      nouv->suiv->prec=nouv;
    }
  }
  if (nouv->prec && nouv->prec->free){
    nouv->prec->size += EN_TETE + nouv->size;
    nouv->prec->suiv=nouv->suiv;
    if (nouv->suiv){
      nouv->suiv->prec=nouv->prec;
    }
    nouv=nouv->prec;
  }
  last_free=nouv;


  

}

