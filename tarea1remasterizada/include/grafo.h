/*
  Módulo de definición de `Grafo'.

  `Grafo' representa a los grafos no dirigidos con aristas etiquetados.

  Los vértices se identifican con naturales entre 1 y un cierto número `n'
  establecido al crearlo. 

  En las funciones que tienen un parámetro `v' que es un identificador de
  vértice se asume la precondición implícita `1 <= v <= n'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _GRAFO_H
#define _GRAFO_H

#include "utils.h"
#include "lista_pares.h"

struct rep_grafo; // representación de `grafo', definida en `grafo.cpp'.
typedef rep_grafo *Grafo;

/* Devuelve un grafo vacío (sin aristas ni vértices) que tiene `n' vértices. */
Grafo crear_grafo(nat n);

/* Devuelve la cantidad de vértices de `g'. */
nat cantidad_vertices(Grafo g);

/* Agrega una arista desde `v1' hacia `v2' con etiqueta `valor'.
   Si ya había una ariste desde `v1' hacia `v2' no se hace nada. */
void agregar_arista(nat v1, nat v2, int valor, Grafo g);

/* Devuelve `true' si y sólo si hay una arista desde `v1' hacia `v2'. */
bool existe_arista(nat v1, nat v2, Grafo g);

/* Devuelve la cantidad de aristas de `g'. */
nat cantidad_aristas(Grafo g);

/* Devuelve una lista con los aristas que inciden en `v'.
   La lista devuelta comparte memoria con `g'. */
Lista_pares adyacentes(nat v, Grafo g);

/* Libera la memoria asignada a `g'. */
void destruir_grafo(Grafo &g);

#endif
