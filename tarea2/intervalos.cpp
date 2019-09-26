/*50884288*/

#include "intervalos.h"



/* Chequea si i,j son compatibles*/
bool compatibles(intervalo_t i, intervalo_t j) {
    return i.fin <= j.inicio || j.fin <= i.inicio;
}

nat max_cantidad_rec(intervalo_t *intervalos, nat n, nat inicio, nat fin){
    nat izqMin = max_cantidad_rec(intervalos, n/2, inicio, fin);
    nat derMin = max_cantidad_rec(intervalos, n/2, inicio, fin);
    
}

bool *max_cantidad(intervalo_t *intervalos, nat n) {
    
}

Bueno para buscar el minimo asumo que hay que usar divide and conquer pero estoy pensando
la recursion deberia tener algun parametro pa decirle que vaya matando a los no compatibles y que marque como true al que finalice primero que sea compatible