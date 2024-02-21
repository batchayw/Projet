/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include <sys/types.h>
#include "mem.h"
#include "mem_internals.h"

unsigned long * buffer;

unsigned long tab[5];


unsigned long knuth_mmix_one_round(unsigned long in)
{
    return in * 6364136223846793005UL % 1442695040888963407UL;
}

void *mark_memarea_and_get_user_ptr(void *ptr, unsigned long size, MemKind k)
{
    
    // calcul du nombre magic 
    /* Valeur du nombre magique*/
    unsigned long magic = knuth_mmix_one_round((unsigned long)ptr);

    //on attribue les deux derniers bits de magic pour choisir le type allocation
    magic = (magic & 0b11UL)|k;  

    /*On caste la valeur de ptr pour l'avoir sur 8bits*/
    unsigned long *new_p = (unsigned long*) ptr;

    //On donne les 8 premiers bits a tab[0]
    printf("Valeur magic est : %lu\n",magic);
    //new_p = &size;
    tab[0] = size;

    //Ensuite on avance d'un bit pour donner la valeur magique
    // *(new_p + 1) = magic;
    tab[1] = magic;

    // zone demander pas utilisateur
    // *(new_p + 2) = size;
    tab[2] = sizeof(unsigned long);

    // marquage des 16 derniers otects pour donner la valeur magic
    tab[3] = magic;

    //*(unsigned long *)(new_p+ 16 + size) = magic;

    //size de la fin
    //*(unsigned long *)(new_p+ 16 + size + sizeof(magic)) = size;
    tab[4] = sizeof(unsigned long);

    // faisons pointer notre pointeur sur tab
    new_p = tab;

    /* ecrire votre code ici */

    return new_p + 2;
}

Alloc mark_check_and_get_alloc(void *ptr)
{
    /* ecrire votre code ici */
    Alloc a = {};

    //On caste ptr pour le decalge sur 8bits
   unsigned long *new_p = (unsigned long*) ptr;

    //on positionne le pointeur 16o avant ptr et on donne la valeur des 8 prmiers octects a.size
    a.size = (unsigned long)(new_p[-2]);
    printf("Val : %lu\n",a.size);

    // on positionne le pointeur 8o avant ptr et on donne la valeur des 8 premiers octets a magic debut
    unsigned long magic_debut = new_p[-1];
    printf("Magic debut : %lu\n",magic_debut);

    //recuperation du Memkind
    a.kind = magic_debut;

    // recuperation du pointeur;
    a.ptr = ptr;
    
    //magic de la fin de tab
    unsigned long magic_fin = new_p[1];
    printf("Magic Fin : %lu\n",magic_fin);


    //magic du debut
    unsigned long size_fin = new_p[2];
    printf("Size fin : %lu\n",size_fin);


    //Verifcation si la valeur magique du debut est egal a celui de la fin
    assert(magic_debut == magic_fin);
  
    //Verifcation si le size du debut est egal a celui de la fin, );
    assert(a.size == size_fin);
 
    return a;
}


unsigned long
mem_realloc_small() {
    assert(arena.chunkpool == 0);
    unsigned long size = (FIRST_ALLOC_SMALL << arena.small_next_exponant);
    arena.chunkpool = mmap(0,
			   size,
			   PROT_READ | PROT_WRITE | PROT_EXEC,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   -1,
			   0);
    if (arena.chunkpool == MAP_FAILED)
	handle_fatalError("small realloc");
    arena.small_next_exponant++;
    return size;
}

unsigned long
mem_realloc_medium() {
    uint32_t indice = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant;
    assert(arena.TZL[indice] == 0);
    unsigned long size = (FIRST_ALLOC_MEDIUM << arena.medium_next_exponant);
    assert( size == (1 << indice));
    arena.TZL[indice] = mmap(0,
			     size*2, // twice the size to allign
			     PROT_READ | PROT_WRITE | PROT_EXEC,
			     MAP_PRIVATE | MAP_ANONYMOUS,
			     -1,
			     0);
    if (arena.TZL[indice] == MAP_FAILED)
	handle_fatalError("medium realloc");
    // align allocation to a multiple of the size
    // for buddy algo
    arena.TZL[indice] += (size - (((intptr_t)arena.TZL[indice]) % size));
    arena.medium_next_exponant++;
    return size; // lie on allocation size, but never free
}


//used for test in buddy algo
unsigned int
nb_TZL_entries() {
    int nb = 0;
    
    for(int i=0; i < TZL_SIZE; i++)
	if ( arena.TZL[i] )
	    nb ++;

    return nb;
}




// int main(int argc, char * argv[] ){
    
//    // buffer = "";

//     buffer = mark_memarea_and_get_user_ptr(buffer,sizeof(unsigned long), 2);

//     printf("Valeur retourner :  %lu\n", *(buffer));

//     mark_check_and_get_alloc((unsigned long*)buffer);

// }
