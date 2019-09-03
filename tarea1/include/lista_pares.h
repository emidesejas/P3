/*
  Módulo de definición de `Lista_pares'.

  `Lista_pares' es una estructura lineal de elementos de tipo `Par_nat_int'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_PARES_H
#define _LISTA_PARES_H

#include "utils.h"

// representación de `Lista_pares`, definida en `lista_pares.cpp`.
struct rep_lista_pares; 
typedef rep_lista_pares *Lista_pares;

/* Devuelve la lista vacía (sin elementos). */
Lista_pares crear_lista_pares();

/* Devuelve una copia de `lst'.
   La lista devuelta no comparte memoria con `lst'. */
Lista_pares copia_lista_pares(Lista_pares lst);

/* Inserta `elem' al inicio de `lst'. */
void insertar_par(Par_nat_int elem, Lista_pares &lst);

/* Remueve de `lst' el par cuya primer componente es `id' .
   Si `idx' no es primer componente en `lst' no hace nada.*/
void remover_par(nat id, Lista_pares &lst);

/* Devuelve `true' si y sólo si `lst` es vacía (no tiene elementos). */
bool es_vacia_lista_pares(Lista_pares lst);

/* Devuelve `true' si y sólo si `id' es primer componente de algún par de 
   `lst'. */
bool pertenece_a_lista_pares(nat id, Lista_pares lst);

/* Devuelve el primer elemento de `lst'.
   Precondición: ! es_vacia_lista(lst). */
Par_nat_int primer_par(Lista_pares lst);

/* Devuelve el resto de `lst'.
   Precondición: ! es_vacia_lista(lst). */
Lista_pares resto_pares(Lista_pares lst);

/* Libera la memoria asignada a `lst'. */
void destruir_lista_pares(Lista_pares &lst);

#endif
