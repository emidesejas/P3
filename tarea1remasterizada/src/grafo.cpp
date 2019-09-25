/*
  Módulo de implementación de `Grafo'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/lista_pares.h"
#include "../include/grafo.h"

#include <assert.h>

typedef struct vertice_t {
  Lista_pares adyacentes;
  // otros datos
} * Vertice;

struct rep_grafo {
  vertice_t *vertices; // arreglo 
  nat n;               // cantidad de vértices
  nat m;               // cantidad de aristas
};

Grafo crear_grafo(nat n) {
  Grafo g = new rep_grafo;
  g->n = n;
  g->m = 0;
  g->vertices = new vertice_t[n + 1]; // se va a ignorar la celda 0
  for (nat i = 1; i <= n; i++)
    g->vertices[i].adyacentes = crear_lista_pares();
  return g;
}

nat cantidad_vertices(Grafo g) { return g->n; }

void agregar_arista(nat v1, nat v2, int valor, Grafo g) {
  assert(1 <= v1); assert(1 <= v2); assert(v1 <= g->n); assert(v2 <= g->n); 
  if (!pertenece_a_lista_pares(v2, g->vertices[v1].adyacentes)) {
    g->m++;
    Par_nat_int arista;
    arista.valor = valor;
    arista.id = v2;
    insertar_par(arista, g->vertices[v1].adyacentes);
    arista.id = v1;
    insertar_par(arista, g->vertices[v2].adyacentes);
  }
}

bool existe_arista(nat v1, nat v2, Grafo g) {
  assert(1 <= v1); assert(1 <= v2); assert(v1 <= g->n); assert(v2 <= g->n); 
  return pertenece_a_lista_pares(v2, g->vertices[v1].adyacentes);
}

nat cantidad_aristas(Grafo g) { return g->m; }

Lista_pares adyacentes(nat v, Grafo g) {
  assert(1 <= v); assert(v <= g->n);;
  return g->vertices[v].adyacentes;
}

void destruir_grafo(Grafo &g) {
  for (nat i = 1; i <= g->n; i++)
    destruir_lista_pares(g->vertices[i].adyacentes);
  delete[] g->vertices;
  delete g;
}
