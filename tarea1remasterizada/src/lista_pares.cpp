/*
  Módulo de implementación de `lista_pares'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista_pares.h"
#include "../include/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct rep_lista_pares {
  Par_nat_int elem;
  rep_lista_pares *sig;
};

Lista_pares crear_lista_pares() { return NULL; }

void insertar_par(Par_nat_int elem, Lista_pares &lst) {
  rep_lista_pares *nuevo = new rep_lista_pares;
  nuevo->elem = elem;
  nuevo->sig = lst;
  lst = nuevo;
}

void remover_par(nat id, Lista_pares &lst) {
  if ((lst != NULL) && (id == lst->elem.id)) {
    rep_lista_pares *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  } else if (lst != NULL) {
    rep_lista_pares *cursor = lst;
    while ((cursor->sig != NULL) && (id != cursor->sig->elem.id)) {
      cursor = cursor->sig;
    }
    if (cursor->sig != NULL) {
      rep_lista_pares *aborrar = cursor->sig;
      cursor->sig = cursor->sig->sig;
      delete aborrar;
    } // else no está elem en lst, no se hace nada
  } // else lst == NULL, no se hace nada
}

Lista_pares copia_lista_pares(Lista_pares lst) {
  Lista_pares res;
  if (lst == NULL)
    res = NULL;
  else {
    res = new rep_lista_pares;
    rep_lista_pares * ultimo = res;
    ultimo->elem = lst->elem;
    while (lst->sig != NULL) {
      lst = lst->sig;
      ultimo->sig = new rep_lista_pares;
      ultimo = ultimo->sig;
      ultimo->elem = lst->elem;
    }
    ultimo->sig = NULL;
  }
  return res;
}

bool es_vacia_lista_pares(Lista_pares lst) { return (lst == NULL); }

bool pertenece_a_lista_pares(nat id, Lista_pares lst) {
  while ((lst != NULL) && (id != lst->elem.id)) {
    lst = lst->sig;
  }
  return (lst != NULL);
}

Par_nat_int primer_par(Lista_pares lst) {
  assert(!es_vacia_lista_pares(lst));
  return lst->elem;
}

Lista_pares resto_pares(Lista_pares lst) {
  assert(!es_vacia_lista_pares(lst));
  return lst->sig;
}

void destruir_lista_pares(Lista_pares &lst) {
  while (lst != NULL) {
    rep_lista_pares *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}
