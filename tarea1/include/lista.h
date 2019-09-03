/*
  Módulo de definición de `Lista'.

  `Lista' es una estructura lineal de elementos de tipo `nat' ordenada de 
   manera  creciente, sin elementos repetidos.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "utils.h"

struct rep_lista; // representación de `Lista`, definida en `lista.cpp`.
typedef rep_lista *Lista;

/* Devuelve la lista vacía (sin elementos). */
Lista crear_lista();

/* Devuelve una copia de `lst'.
   La lista devuelta no comparte memoria con `lst'. */
Lista copia_lista(Lista lst);

/* Inserta `elem' en `lst' manteniendo el orden.
   Si ya estaba `elem' en `lst' no hace nada. */
void insertar(nat elem, Lista &lst);

/* Remueve `elem' de `lst'.
   Si no estaba `elem' en `lst' no hace nada.*/
void remover(nat elem, Lista &lst);

/* Devuelve `true' si y sólo si `lst` es vacía (no tiene elementos). */
bool es_vacia_lista(Lista lst);

/* Devuelve `true' si y sólo si `elem' pertenece a `lst'. */
bool pertenece_a_lista(nat elem, Lista lst);

/* Devuelve el primer elemento de `lst'.
   Precondición: ! es_vacia_lista(lst). */
nat primero(Lista lst);

/* Devuelve el resto de `lst'.
   Precondición: ! es_vacia_lista(lst). */
Lista resto(Lista lst);

/* Libera la memoria asignada a `lst'. */
void destruir_lista(Lista &lst);

#endif
