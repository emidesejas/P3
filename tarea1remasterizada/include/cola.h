/*
  Módulo de definición de `Cola'.

  `Cola' es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `nat'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "utils.h"

struct rep_cola; // representación de `Cola', definida en `cola.cpp'.
typedef rep_cola *Cola;

/*  Devuelve una cola vacía (sin elementos). */
Cola crear_cola();

/* Encola `elem' en `c'. */
void encolar(nat elem, Cola &c);

/* Remueve de `c' el elemento que está en el frente.
   Si es_vacia_cola(c) no hace nada. */
void desencolar(Cola &c);

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola(Cola c);

/* Devuelve el elemento que está en el frente de `c'.
   Precondición: ! es_vacia_cola(c). */
nat frente(Cola c);

/*  Libera la memoria asignada a `c'. */
void destruir_cola(Cola &c);

#endif
