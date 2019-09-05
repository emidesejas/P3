/*50884288*/

#include <stdio.h>
#include "include/utils.h"
#include "include/grafo.h"
#include "include/lista_pares.h"
#include "include/lista.h"
#include "include/cola.h"

struct butterfly{
    nat id;
    butterfly *prev;
    butterfly *next;
};

typedef butterfly *ButterfliesList;

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
    ButterfliesList Butterflies[cantidad_vertices(G)];
    ButterfliesList auxList = new butterfly();
    auxList -> id = 0;
    auxList -> next = NULL;
    auxList -> prev = NULL;
    discovered[0] = false;

    Butterflies[0] = auxList;
    ButterfliesList cursor = auxList;
    for(int i = 1; i < cantidad_vertices(G); i++) {
        discovered[i] = false;
        cursor -> next = new butterfly();
        cursor -> next -> prev = cursor;
        cursor = cursor -> next;
        cursor -> id = i;
        Butterflies[i] = cursor;
    }
    cursor -> next = NULL;

    //JMMM DUDOSO TODO ESTO ^^^^^^^


    //bfsLevels levels = new level;
    //levels -> id = 0; // No es necesario, se borrará en futuras versiones (es el numero del nivel)
    //levels -> elements = crear_cola();
    //encolar(0, levels -> elements);
    Cola elements = crear_cola();
    encolar(0, elements);
    killButterfly(0, Butterflies, auxList);
    while(!es_vacia_cola(elements)){
        Lista_pares incidents = adyacentes(frente(elements), G);
        discovered[frente(elements)] = true;



        // Basicamente crear nuevo nodo de bfs levels con los nodos que son incidentes a v en el grafo (usar pila para ir haciendo pop de cada nodo y poder irlos agregando)

    }
    
}

void bfs(nat node, Grafo G, bool *discovered){
    discovered[node] = true;

}

void killButterfly(nat id, ButterfliesList *Array, ButterfliesList List){ //Se me fue de las manos esto pero sino no me aseguro el O(1)
    if(Array[id] != NULL){
        if(Array[id] -> prev != NULL){
            Array[id] -> prev -> next = Array[id] -> next;
        } else {
            List = Array[id] -> next;
        }
        if(Array[id] -> next != NULL){
            Array[id] -> next -> prev = Array[id] -> prev;
        }
        delete Array[id];
        Array[id] = NULL;
    }
}
// HACER FUNCIONES PARA MANIPULAR BFSLEVELS, DESTRUIR MOVERSE ETC.
