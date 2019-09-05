/*50884288*/

#include <stdio.h>
#include "include/utils.h"
#include "include/grafo.h"
#include "include/lista_pares.h"
#include "include/lista.h"

struct level{
    nat id;
    Lista elements;
    level *next;
};

typedef level *bfsLevels;

int main(){
    nat n, m, e1, e2;
    char juicio;
    scanf("%d", &n);
    Grafo mariposas = crear_grafo(n);
    // Aqui darle calor a n
    scanf("%d", &m);
    // Aqui darle calor a m
    for(nat i = 0; i < m; i++){
        scanf("%d %d %c", &e1, &e2, &juicio);
        agregar_arista(e1, e2, int(juicio), mariposas);
        // Aqui darle calor a e1, e2 y juicio, juira cucha
    }

    //bool resultado;

    //resultado = algo jejejejejeje

    printf("%s", consistenteMaximal(mariposas)?"Consitente":"No consistente"); //Esta linea consiste en decir si es consistente o no es consistente, porque sino, de que consistiria la tarea verdad?, es una inconsistencia maximal que esta tarea no consista en preguntar acerca de la consitencia de las mariposas. Espero que sus vidas sean consistentes y que el señor consistente los consista
    destruir_grafo(mariposas); //A.K.A. matar mariposas :(
}

bool consistenteMaximal(Grafo G) { // Quién dice que perder lógica no deja secuelas?
    bool discovered[cantidad_vertices(G)];
    bool label[cantidad_vertices(G)];
    for(int i = 0; i < cantidad_vertices(G); i++) {
        discovered[i] = false;
    }
    bfsLevels levels = new level;
    levels -> id = 0; // No es necesario, se borrará en futuras versiones (es el numero del nivel)
    levels -> elements = crear_lista();
    insertar(0, levels->elements);
    while(!es_vacia_lista(levels -> elements)){
        // Basicamente crear nuevo nodo de bfs levels con los nodos que son incidentes a v en el grafo (usar pila para ir haciendo pop de cada nodo y poder irlos agregando)
    }
    
}

void bfs(nat node, Grafo G, bool *discovered){
    discovered[node] = true;

}

// HACER FUNCIONES PARA MANIPULAR BFSLEVELS, DESTRUIR MOVERSE ETC.
