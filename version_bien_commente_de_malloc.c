#include <stdio.h>

#include "my_malloc.h"






typedef struct bloc{
  size_t size;

  int free;//indicateur statut 1 si libre , 0 si occupé
  struct bloc *suiv;
  struct bloc *prec;

}bloc;
#define POOL_SIZE 1000000000 /* 1 Giga */

#define EN_TETE sizeof(bloc)//taille en octets de l'en tete
static char _mem_pool[POOL_SIZE]; /* static pool of memory */

static bloc *list=NULL;//contiendra l'adresse du premier bloc 
static int demarre=0;
static bloc *last_free=NULL;//memorise le dernier bloc libre 

static void cree_memoire(){
  list=(bloc*) _mem_pool;//on cree un pool de memoire avec le nb d'octets que nous a passe le prof
  list->size=POOL_SIZE-EN_TETE;
  list->free=1;
  list->suiv=list->prec=NULL;
  demarre=1;
  last_free=list;
//le pool est initialisé en creant un unique grand bloc couvrant tout le pool moins l'espace pour l'en tete 
}

//Si le bloc trouvé est trop grand , on va le découper proprement en deux parties 
//la premiere partie aura la taille demandée , la deuxieme (s'il y en a une)aura le reste et restera libre

static void fragment(bloc *b,size_t new_size){
  if (b->size >= new_size + EN_TETE + 1){ //on verifie que la taille actuelle de notre bloc est superieur a la taille demandée pour l'allocation plus celle de l'en tete qu'on devra forcement utilisé
    bloc *nouv=(bloc*)((char*)b + EN_TETE + new_size);//on fait une coercition,on calcule l'adresse du nouveau bloc , on deplace l'adresse de l'ancien bloc de EN_TETE + la taille demande
    nouv->size=b->size - new_size - EN_TETE;//la taille du nouveau bloc c'est la taille de l'ancien moins la taille souhaité moins la taille de l'en tete
    nouv->free=1;//Le nouveau bloc est evidemment libre 
    nouv->suiv=b->suiv;//on copie la suite de l'ancien bloc a la suite du nouveau bloc
    nouv->prec=b;//le bloc precedent est le bloc courant
    if (nouv->suiv){
      nouv->suiv->prec=nouv;//si le bloc precedent avait une suite alors le pointeur precedent de cette suite pointe sur le nouveau bloc
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

  //on fusionne avec le bloc suivant si c'est libre 
  if (nouv->suiv && nouv->suiv->free){
    nouv->size += EN_TETE + nouv->suiv->size;
    nouv->suiv=nouv->suiv->suiv;
  
    if (nouv->suiv)
      nouv->suiv->prec=nouv;
  }
  //on fusionne avec le bloc precedent si c'est libre 
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


  



