/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <assert.h>
#include <stdio.h>
#include "mem.h"
#include "mem_internals.h"

unsigned long *ptr;
unsigned long size;
void *
emalloc_small(unsigned long size)
{
    /* ecrire votre code ici */
     
    
    if(arena.chunkpool != NULL){

        // fonction de marquage qui retourné la zone demandé pas utilisateur
      ptr = mark_memarea_and_get_user_ptr(arena.chunkpool, CHUNKSIZE, SMALL_KIND);
     
    }else{
        // reallocation de la memoire cas il y'a aucun element dans la liste
        size = mem_realloc_small();
        ptr = mark_memarea_and_get_user_ptr(arena.chunkpool, size, SMALL_KIND);   
    }

    return (void *)ptr;
}

void efree_small(Alloc a) {
    /* ecrire votre code ici */
    arena.chunkpool = &a.size;
}
