/*
  Módulo de implementación de `Lista'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/utils.h"

#include <stdlib.h>
#include <assert.h>

struct rep_lista {
  nat elem;
  rep_lista *sig;
};

Lista crear_lista() {
  Lista res = new rep_lista; // celda falsa
  res->sig = NULL;
  return res;
}

Lista copia_lista(Lista lst) {
  Lista res = new rep_lista;
  Lista ultimo = res;
  while (lst->sig != NULL) {
    lst = lst->sig;
    ultimo->sig = new rep_lista;
    ultimo = ultimo->sig;
    ultimo->elem = lst->elem;
  }
  ultimo->sig = NULL;
  return res;
}

void insertar(nat elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->elem)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig == NULL) || (elem < cursor->sig->elem)) {
    rep_lista *nuevo = new rep_lista;
    nuevo->elem = elem;
    nuevo->sig = cursor->sig;
    cursor->sig = nuevo;
  } // else ya está elem en lst, no se hace nada
}

void remover(nat elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->elem)) {
    cursor = cursor->sig;
  }
  if (cursor->sig != NULL) {
    rep_lista *aborrar = cursor->sig;
    cursor->sig = cursor->sig->sig;
    delete aborrar;
  } // else no está elem en lst, no se hace nada
}


bool es_vacia_lista(Lista lst) { return (lst->sig == NULL); }

bool pertenece_a_lista(nat elem, Lista lst) {
  while ((lst != NULL) && (elem > lst->elem)) {
    lst = lst->sig;
  }
  return (lst != NULL);
}

nat primero(Lista lst) {
  assert(!es_vacia_lista(lst));
  return lst->sig->elem;
}

Lista resto(Lista lst) {
  assert(!es_vacia_lista(lst));
  return lst->sig;
}

void destruir_lista(Lista &lst) {
  while (lst != NULL) {
    rep_lista *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}

