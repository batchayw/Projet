/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

int indiceTZL;
unsigned long sizeMedium;
int tailleLibre;

unsigned long newPtr;
unsigned long newSize;
unsigned long Adrbuddy;


unsigned int puiss2(unsigned long size) {
    unsigned int p=0;
    size = size -1; // allocation start in 0
    while(size) {  // get the largest bit
	p++;
	size >>= 1;
    }
    if (size > (1 << p))
	p++;
    return p;
}


void *
emalloc_medium(unsigned long size)
{
    assert(size < LARGEALLOC);
    assert(size > SMALLALLOC);
    /* ecrire votre code ici */

    // recuperation de l'indice du bloc
    indiceTZL = puiss2(size);

    if(arena.TZL[indiceTZL] != NULL)
    {   
        // ajouter la taille dans la table des zone libre
        arena.TZL[indiceTZL] = &size;
    }
    else
    {
        // decoupons recussivement une taille plus grosse jusqu'a la taille approprié
        for (int i=indiceTZL+1; i<=TZL_SIZE; i++) {
            if(arena.TZL[i] != NULL)
            {
                tailleLibre = (int)pow(2, i);
                while (tailleLibre != size) {
                    tailleLibre = tailleLibre /2;
                }
                arena.TZL[i] = &size;
            }
            else 
            {
                // s'il y'a pas de taille disponible faisons une rellocation de memoire
                sizeMedium = mem_realloc_medium();
                arena.TZL[FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant] = &sizeMedium;
            }
        }

    }

    return (void *) arena.chunkpool;
}


void efree_medium(Alloc a) {
    /* ecrire votre code ici */

    // recuperation de l'adresse du bloc pointeur
    newPtr = (unsigned long)a.ptr;

    // taille du bloc pointé
    newSize = (unsigned long)a.size;

    if(a.ptr != NULL)
    {
        // recuperation de l'adresse du compagnon (buddy)
        Adrbuddy = newPtr ^ newSize;

        // impossible supprimer si l'adresse du compagnon est superieure a la taille
    if (Adrbuddy > TZL_SIZE)
       {
          printf("Suppression impossible.\n");

       }
       // suppression d buddy dans la liste
    else  
       {
        for (int i = Adrbuddy - 1; i < TZL_SIZE - 1; i++)
            arena.TZL[i] = arena.TZL[i+1];
       }
    }

// si le pointeur est Null aucun bloc est utilisé
    else 
    {
        printf("Aucun bloc ne peut être libéré cas il y a aucun element");
    }
}


// int main(){
//     int a = puiss2(124);
    

//     printf("La valeur est : %d\n",a);
// }